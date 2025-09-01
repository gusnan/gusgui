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

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <list>
#include <memory>

#include "GusGame/GusGame.h"
using namespace Gus;

using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiEventHandler.h"
#include "GlobalEventHandler.h"

#include "GuiObject.h"

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
GUSGAME_DLL GuiEventHandler::GuiEventHandler(/*std::vector<std::shared_ptr<GuiObject>> *guiList*/) : EventHandler()
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

   return handled;
}

/**
 *
 */
bool GUSGAME_DLL GuiEventHandler::onLeftMouseButtonReleased(const Vector2d& pos)
{
   bool result = false;

   return result;
}

/**
 *
 */
bool GUSGAME_DLL GuiEventHandler::onRightMouseButtonPressed(const Vector2d& pos)
{
   bool handled=false;

   return handled;
}

/**
 *
 */
bool GUSGAME_DLL GuiEventHandler::onRightMouseButtonReleased(const Vector2d& pos)
{
   bool result = false;

   return result;
}




/**
 *
 */
void GuiEventHandler::onMouseMove(const Vector2d& pos)
{
}


/**
 *
 */
void GUSGAME_DLL GuiEventHandler::onMouseScrollUp(const Vector2d& pos)
{

}

/**
 *
 */
void GUSGAME_DLL GuiEventHandler::onMouseScrollDown(const Vector2d& pos)
{

}



void GuiEventHandler::onDrag(const Vector2d& pos)
{

}


bool GUSGAME_DLL GuiEventHandler::handleUserEvent(UserEvent &userEvent)
{
   //return EventHandler::handleUserEvent(userEvent);
   return false;
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

bool GUSGAME_DLL GuiEventHandler::handleMouseButton(MouseButtonEvent &mouseButtonEvent)
//void GameEventHandler::HandleMouseButton(Uint8 type,SDL_MouseButtonEvent buttonEvent)
{
   return false;
}




/**
 *
 */
std::shared_ptr<GuiEventHandler> GuiEventHandler::makeCopy() const
{
   return std::shared_ptr<GuiEventHandler>(cloneImplementation());

}


/**
 *
 */
GuiEventHandler *GuiEventHandler::cloneImplementation() const
{
   return new GuiEventHandler(*this);
}


// end of namespace
// ----------------
};

