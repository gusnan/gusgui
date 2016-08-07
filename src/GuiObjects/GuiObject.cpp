/**
 *
 * This file is part of GusGui
 * Copyright 2008-2014 Andreas Rönnquist
 *
 * GusGui is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GusGui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GusGui.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
GuiObject::GuiObject() : m_Rect(), m_MouseOver(false), m_Active(true), m_Visible(true),
	m_PanelPosition(), m_Drag(false), m_DragOnlyWhenMouseOver(true), m_LastMousePosition()
{

}

/**
 *
 */
GuiObject::GuiObject(Rect rect) : m_Rect(rect), m_Active(true), m_Visible(true), m_MouseOver(false),
	m_PanelPosition(), m_Drag(false), m_DragOnlyWhenMouseOver(true), m_LastMousePosition()
{
}

/**
 *
 */
GuiObject::~GuiObject()
{
}

/**
 *
 */
Vector2d GuiObject::getPosition() const
{
	return m_Rect.position;
}

/**
 *
 */
Rect GuiObject::getRect() const
{
	return m_Rect;
}

/**
 *
 */
void GuiObject::setRect(const Rect& rect)
{
	m_Rect = rect;
}

/**
 *
 */
void GuiObject::setSize(const Vector2d& size)
{
	m_Rect.size = size;
}

/**
 *
 */
void GuiObject::setCenter(const Vector2d& pos)
{
	m_Rect.setCenter(pos);
}


/**
 *
 */
void GuiObject::setMouseOver(bool over)
{
	m_MouseOver = over;
}

/**
 *
 */
void GuiObject::setActive(bool active)
{
	m_Active = active;

	//if (m_Active) {
		onMouseMove(m_LastMousePosition);
	//}

	//if (!active) m_MouseOver=false;

}

/**
 *
 */
void GuiObject::setVisible(bool visible)
{
	m_Visible = visible;
}

/**
 *
 */
void GuiObject::switchVisible()
{
	m_Visible = !m_Visible;
}

/**
 *
 */
bool GuiObject::getVisible() const
{
	return m_Visible;
}

/**
 *
 */
bool GuiObject::getMouseOver() const
{
	return m_MouseOver;
}

/**
 *
 */
bool GuiObject::handleUserEvent(UserEvent &event)
{
	return false;
}

/**
 *
 */
bool GuiObject::handleKeyboardEvent(KeyEvent &event)
{
	return false;
}

/**
 *
 */
void GuiObject::gainFocus()
{

}

/**
 *
 */
void GuiObject::releaseFocus()
{
}

/**
 *
 */
bool GuiObject::onLeftMouseButtonPressed(const Vector2d& pos)
{
	m_Drag = true;
	return false;
}

/**
 *
 */
void GuiObject::onLeftMouseButtonReleased(const Vector2d& pos)
{
	m_Drag = false;
}

/**
 *
 */
bool GuiObject::onRightMouseButtonPressed(const Vector2d& pos)
{
	return false;
}

/**
 *
 */
void GuiObject::onRightMouseButtonReleased(const Vector2d& pos)
{

}

/**
 *
 */
void GuiObject::setPanelPosition(const Vector2d& pos)
{
	m_PanelPosition=pos;
}

/**
 *
 */
void GuiObject::onMouseMove(const Vector2d& pos)
{
	m_MouseOver = false;
	if (m_Active) {
		if (m_Rect.isPointOver(pos)) {
			m_MouseOver = true;
		} else {
			m_MouseOver = false;
		}
	}

	if (m_DragOnlyWhenMouseOver) {
		if (!m_MouseOver) m_Drag = false;
	}

	if (m_Drag) onDrag(pos);

	m_LastMousePosition = pos;
}

/**
 *
 */
void GuiObject::onMouseScrollUp(const Vector2d& pos)
{
}

/**
 *
 */
void GuiObject::onMouseScrollDown(const Vector2d& pos)
{
}

/**
 *
 */
void GuiObject::onDrag(const Vector2d& pos)
{
	if (m_MouseOver) {
		/*
		std::stringstream st;
		st << "GuiObject::Drag:" << pos.x << "," << pos.y;
		STLOG(st);
		*/
	}
}


/**
 *
 */
void GuiObject::setCenter(Rect sourceRect, int directions)
{
	//Rect screenRect = GraphicsHandler::getScreenRect();
	Vector2d sourceSize = sourceRect.size;

	int x = sourceSize.x / 2;
	int y = sourceSize.y / 2;

	Rect tempRect = getRect();

	Vector2d position = tempRect.position;
	Vector2d size = tempRect.size;

	int newXPos = x - (size.x / 2);
	int newYPos = y - (size.y / 2);

	Vector2d newposition;

	if ((directions & GUI_OBJECT_CENTER_BOTH) == GUI_OBJECT_CENTER_BOTH) {
		newposition = Vector2d(newXPos, newYPos);
	} else if ((directions & GUI_OBJECT_CENTER_HORISONTALLY) == GUI_OBJECT_CENTER_HORISONTALLY) {
		newposition = Vector2d(newXPos, position.y);
	} else if ((directions & GUI_OBJECT_CENTER_VERTICALLY) == GUI_OBJECT_CENTER_VERTICALLY) {
		newposition = Vector2d(position.x, newYPos);
	}

	setRect(Rect(newposition, size));
}


// end of namespace
// ----------------
}
