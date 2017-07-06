/**
 *
 *	This file is part of GusGui.
 *	Copyright 2011-2014 Andreas Rönnquist
 *
 *	GusGui is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	GusGui is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with GusGui.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"
#include "Panel.h"

#include "GuiDraw.h"
#include "GuiData.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
Panel::Panel(Rect rect, std::string name, bool transparentFrame) : GuiObject(rect), m_GuiList(NULL), m_DrawFrame(false), m_DrawBackground(false), m_TransparentFrame(transparentFrame)
{
	m_GuiList = new std::vector<GuiObjectPtr>;
	setName(name);
}


/**
 *
 */
Panel::Panel() : m_GuiList(NULL)
{
}


/**
 *
 */
Panel::~Panel()
{
	if (m_GuiList) {

		std::vector<GuiObjectPtr>::iterator iter;
		for (iter = m_GuiList->begin(); iter != m_GuiList->end();) {

			//if (iter!=m_GuiList->end())  {
			GuiObjectPtr obj = (*iter);

			iter = m_GuiList->erase(iter);

			/*
			obj.reset();
			++iter;
			*/

		}


		/*
		for (int co=0;co<(int)m_GuiList->size();) {
			GuiObject *curr=(GuiObject*)(m_GuiList->at(co));
			REMOVE(curr);

			std::cout << "Co:" << co << std::endl;
			++co;
		}*/

	}

	if (m_GuiList != NULL) {
		delete m_GuiList;
		m_GuiList = NULL;
	}
}

/**
 *
 */
Panel::Panel(const Panel& source) : GuiObject(source), m_GuiList(0), m_DrawFrame(false), m_DrawBackground(false),m_TransparentFrame(true)
{
	m_GuiList = new std::vector<GuiObjectPtr>;

	m_GuiList->clear();

	std::vector<GuiObjectPtr>::iterator iter;

	for (iter = source.m_GuiList->begin(); iter != source.m_GuiList->end();) {

		GuiObjectPtr obj = (*iter);

		m_GuiList->push_back(obj);

		++iter;
	}
}

/**
 *
 */
Panel& Panel::operator=(const Panel& source)
{
	if (this!=&source) {
		m_GuiList=new std::vector<GuiObjectPtr>;

		m_GuiList->clear();

		std::vector<GuiObjectPtr>::iterator iter;

		for (iter = source.m_GuiList->begin(); iter != source.m_GuiList->end();) {

			GuiObjectPtr obj = (*iter);

			m_GuiList->push_back(obj);

			++iter;
		}
	}

	return *this;
}


/**
 *
 */
void Panel::addGuiObject(GuiObjectPtr guiObject)
{
	m_GuiList->push_back(guiObject);
}

/**
 *
 */
void Panel::draw(const Vector2d& pos,float alpha)
{

	//GLPrimitives::DrawRect(GetRect(),colorWhite);
	if (m_Visible) {

		if (m_DrawBackground) GuiData::menuBackground->drawPattern(getRect(), alpha);

		if (m_DrawFrame) GuiDraw::drawGuiRect(getRect(), m_TransparentFrame, alpha);

		for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter != m_GuiList->end();) {
			(*iter)->draw(getRect().position + pos, alpha);

			++iter;
		}
	}
}

/**
 *
 */
void Panel::update()
{
	for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
		(*iter)->update();
		++iter;
	}
}

/**
 *
 */
void Panel::setDrawFrame(bool drawFrame)
{
	m_DrawFrame=drawFrame;
}

/**
 *
 */
void Panel::setMouseOver(bool mouseOver)
{
	for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
		(*iter)->setMouseOver(mouseOver);
		++iter;
	}
}

/**
 *
 */
void Panel::setDrawBackground(bool drawBackground)
{
	m_DrawBackground=drawBackground;
}

/**
 *
 */
bool Panel::handleKeyboardEvent(KeyEvent &event)
{
	//LOG("Panel::HandleKeyboardEvent");
	bool result=false;

	if (m_GuiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
			if (!result) {
				result=(*iter)->handleKeyboardEvent(event);
				++iter;
			}
		}
	}

	return result;
}

/**
 *
 */
bool Panel::handleUserEvent(UserEvent &event)
{
	return GuiObject::handleUserEvent(event);
}


/**
 *
 */
bool Panel::onLeftMouseButtonPressed(const Vector2d& pos)
{
	bool handled=false;
	Vector2d panelPos = getPosition();

	if (m_Active) {

		GuiObject::onLeftMouseButtonPressed(pos);

		if (m_GuiList) {
			for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
				GuiObjectPtr current = (*iter);

				if (current && !handled) {
					handled = current->onLeftMouseButtonPressed(pos/*-panelPos*/);
				}
				++iter;
			}
		}
	}

	return handled;
}

/**
 *
 */
void Panel::onLeftMouseButtonReleased(const Vector2d& pos)
{
	Vector2d panelPos = getPosition();

	if (m_Active) {

		GuiObject::onLeftMouseButtonReleased(pos);

		if (m_GuiList) {
			for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
				GuiObjectPtr current = (*iter);

				if (current) {
					current->onLeftMouseButtonReleased(pos - panelPos);
				}
				++iter;
			}
		}
	}
}

/**
 *
 */
bool Panel::onRightMouseButtonPressed(const Vector2d& pos)
{
	bool handled=false;
	Vector2d panelPos = getPosition();

	GuiObject::onRightMouseButtonPressed(pos);

	if (m_Active) {

		if (m_GuiList) {
			for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
				GuiObjectPtr current = (*iter);

				if (current && !handled) {
					handled = current->onRightMouseButtonPressed(pos - panelPos);
				}
				++iter;
			}
		}
	}
	return handled;
}

/**
 *
 */
void Panel::onRightMouseButtonReleased(const Vector2d& pos)
{
	Vector2d panelPos = getPosition();

	GuiObject::onRightMouseButtonReleased(pos);

	if (m_Active) {

		if (m_GuiList) {
			for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
				GuiObjectPtr current = (*iter);

				if (current) {
					current->onRightMouseButtonReleased(pos - panelPos);
				}
				++iter;
			}
		}
	}
}

/**
 *
 */
void Panel::onMouseMove(const Vector2d& pos)
{
	Vector2d panelPos = getPosition();

	Vector2d tempPos = Vector2d(panelPos.x * GraphicsHandler::zoomX, panelPos.y * GraphicsHandler::zoomY);

	GuiObject::onMouseMove(pos);

	if (m_Active) {

		for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
			GuiObjectPtr current = (*iter);

			if (current) {
				current->onMouseMove(pos - tempPos);
			}
			++iter;
		}
	}

}

/**
 *
 */
void Panel::onMouseScrollUp()
{
}

/**
 *
 */
void Panel::onMouseScrollDown()
{
}

/**
 *
 */
void Panel::onDrag(const Vector2d& pos)
{
	GuiObject::onDrag(pos);

	if ((m_MouseOver) && (m_Drag)) {
		/*
		std::stringstream st;
		st << "Panel::OnDrag:" << pos.x << "," << pos.y;

		STLOG(st);
		*/
	}
}

/**
 *
 */
void Panel::setVisible(bool visible)
{
	for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
		GuiObjectPtr obj = (*iter);

		obj->setVisible(visible);

		++iter;
	}

	GuiObject::setVisible(visible);
}

/**
 *
 */
void Panel::setActive(bool active)
{

	for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
		GuiObjectPtr obj = (*iter);

		obj->setActive(active);

		++iter;
	}
	GuiObject::setActive(active);
}


void Panel::print()
{
	std::cout << getName() << std::endl;
	for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter!=m_GuiList->end();) {
		GuiObjectPtr obj = (*iter);

		obj->print();

		++iter;
	}
}


// end of namespace
// ----------------
}
