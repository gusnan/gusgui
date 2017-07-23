/**
 *
 *	This file is part of GusGui.
 *	Copyright 2011 Andreas Rönnquist
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

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <list>

#include "GusGame/GusGame.h"
using namespace Gus;

using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "GuiEventHandler.h"

#include "GuiHandler.h"

namespace GusGui
{

/**
 *
 */
	/*
GUSGAME_DLL GuiEventHandler::GuiEventHandler()
{
}
*/

/**
 *
 */
GUSGAME_DLL GuiEventHandler::GuiEventHandler(/*std::vector<GuiObjectPtr> *guiList*/) : EventHandler()
{
}

/**
 *
 */
GUSGAME_DLL GuiEventHandler::~GuiEventHandler()
{
	LOG("Gui EventHandler destructor");
}


/**
 *
 */
GuiEventHandler::GuiEventHandler(const GuiEventHandler &source)
{

}

/**
 *
 */
bool GUSGAME_DLL GuiEventHandler::onLeftMouseButtonPressed(const Vector2d& pos)
{
	bool handled=false;

	std::vector<GuiObjectPtr> *guiList = GuiHandler::instance()->m_GuiList; //getGuiList();

	if (guiList) {

		for (std::vector<GuiObjectPtr>::iterator iter = guiList->begin(); iter != guiList->end();) {
			GuiObjectPtr current = (*iter);

			if ((current != boost::shared_ptr<GuiObject>()) && !handled) {
				handled = current->onLeftMouseButtonPressed(pos);
			}
			++iter;
		}
	}

	return handled;
}

/**
 *
 */
bool GUSGAME_DLL GuiEventHandler::onLeftMouseButtonReleased(const Vector2d& pos)
{
	bool result = false;

	std::vector<GuiObjectPtr> *guiList = GuiHandler::instance()->m_GuiList; //getGuiList();

	if (guiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = guiList->begin(); iter != guiList->end();) {
			GuiObjectPtr current = (*iter);

			if ((current)  && (!result)) {
				result = current->onLeftMouseButtonReleased(pos);
			}
			++iter;
		}
	}
	return result;
}

/**
 *
 */
bool GUSGAME_DLL GuiEventHandler::onRightMouseButtonPressed(const Vector2d& pos)
{
	bool handled=false;

	std::vector<GuiObjectPtr> *guiList = GuiHandler::instance()->m_GuiList; //getGuiList();
	if (guiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = guiList->begin(); iter != guiList->end();) {
			GuiObjectPtr current = (*iter);

			if (current && !handled) {
				handled = current->onRightMouseButtonPressed(pos);
			}
			++iter;
		}
	}
	return handled;
}

/**
 *
 */
bool GUSGAME_DLL GuiEventHandler::onRightMouseButtonReleased(const Vector2d& pos)
{
	bool result = false;
	std::vector<GuiObjectPtr> *guiList = GuiHandler::instance()->m_GuiList; //getGuiList();

	if (guiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = guiList->begin(); iter != guiList->end();) {
			GuiObjectPtr current = (*iter);

			if (current) {
				result = current->onRightMouseButtonReleased(pos);
			}
			++iter;
		}
	}
	return result;
}



/**
 *
 */
void GUSGAME_DLL GuiEventHandler::onMouseMove(const Vector2d& pos)
{

	std::vector<GuiObjectPtr> *guiList = GuiHandler::instance()->m_GuiList; //getGuiList();

	if (guiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = guiList->begin(); iter != guiList->end();) {
			GuiObjectPtr object = (*iter);

			if (object) {
				object->onMouseMove(pos);
			}

			++iter;
		}
	}
}

/**
 *
 */
void GUSGAME_DLL GuiEventHandler::onMouseScrollUp(const Vector2d& pos)
{

	std::vector<GuiObjectPtr> *guiList = GuiHandler::instance()->m_GuiList; //getGuiList();

	if (guiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = guiList->begin(); iter != guiList->end();) {
			GuiObjectPtr object = (*iter);

			if (object) {
				object->onMouseScrollUp(pos);
			}

			++iter;
		}
	}
}

/**
 *
 */
void GUSGAME_DLL GuiEventHandler::onMouseScrollDown(const Vector2d& pos)
{

	std::vector<GuiObjectPtr> *guiList = GuiHandler::instance()->m_GuiList; //getGuiList();

	if (guiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = guiList->begin(); iter != guiList->end();) {
			GuiObjectPtr object = (*iter);

			if (object) {
				object->onMouseScrollDown(pos);
			}

			++iter;
		}
	}
}


/**
 *
 */
void GUSGAME_DLL GuiEventHandler::handleMouseMotion(MouseMotionEvent &mouseMotion)
{
	onMouseMove(mouseMotion.getPosition());
}


/**
 *
 */
void GUSGAME_DLL GuiEventHandler::handleActiveEvent(ActiveEvent &activeEvent)
{
	if (activeEvent.getWindowState() == WindowStateMouseFocusLost) {
		// printf("MouseFocusLost\n");

		handleMouseLeaveScreen();
	}
}

/**
 *
 */
void GUSGAME_DLL GuiEventHandler::handleMouseLeaveScreen()
{
	std::vector<GuiObjectPtr> *guiList = GuiHandler::instance()->m_GuiList; //getGuiList();

	if (guiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = guiList->begin(); iter != guiList->end();) {
			GuiObjectPtr object = (*iter);

			if (object) {
				object->onMouseMove(Vector2d(-1, -1));
				object->setMouseOver(false);
			}

			++iter;
		}
	}
}

/**
 *
 */
bool GUSGAME_DLL GuiEventHandler::handleMouseButton(MouseButtonEvent &mouseButtonEvent)
//void GameEventHandler::HandleMouseButton(Uint8 type,SDL_MouseButtonEvent buttonEvent)
{

	bool handled = false;
	//Data::mouse->SetButton(0);

	//Mouse *mouse=Data::instance()->mouse;

	//if (mouse->GetButton()==0) mouse->SetWaitForZero(false);

	Vector2d mousePos = mouseButtonEvent.getPosition();

	if (mouseButtonEvent.getStatus() == MouseButtonStatusPressed/*SDL_MOUSEBUTTONDOWN*/) {

		switch(mouseButtonEvent.getButton()) {
		case 1:
			{
				//mouse->setButton(1);
				handled = onLeftMouseButtonPressed(mousePos);

			}
			break;
		case 3:
			{
				//mouse->setButton(2);
				handled = onRightMouseButtonPressed(mousePos);
			}
			break;

		case 4:
			{
				//EventData::eventMouseScrollUp->PushEvent();
				onMouseScrollUp(mousePos);
			}
			break;
		case 5:
			{
				//EventData::eventMouseScrollDown->PushEvent();
				onMouseScrollDown(mousePos);

			}
			break;

		default:
			break;
		}

	} else if (mouseButtonEvent.getStatus() == MouseButtonStatusReleased) {
		switch(mouseButtonEvent.getButton()) {
		case 1:
			{
				//mouse->setButton(0);

				handled = onLeftMouseButtonReleased(mousePos);

			}
			break;
		case 3:
			{
				//mouse->setButton(0);
				handled = onRightMouseButtonReleased(mousePos);

			}
			break;

		case 4:
		case 5:
		{
			//mouse->SetButton(0);
			//mouse->SetMouseScroll(MouseNoScroll);

			break;
		}

		default:
			break;
		}
	}

	return handled;
}


bool GUSGAME_DLL GuiEventHandler::handleUserEvent(UserEvent &userEvent)
{
	return EventHandler::handleUserEvent(userEvent);
}


// end of namespace
// ----------------
};

