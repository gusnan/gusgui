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

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>
#include <memory>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiEventHandler.h"
#include "GlobalEventHandler.h"

#include "GuiObject.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
GuiObject::GuiObject() : GuiEventHandler(), m_Rect(), m_MouseOver(false), m_Active(true), m_Visible(true),
   m_PanelPosition(), m_Drag(false), m_DragOnlyWhenMouseOver(true), m_LastMousePosition()
{

}


/**
 *
 */
GuiObject::GuiObject(Rect rect) : GuiEventHandler(), m_Rect(rect), m_Active(true), m_Visible(true), m_MouseOver(false),
   m_PanelPosition(), m_Drag(false), m_DragOnlyWhenMouseOver(true), m_LastMousePosition()
{
}



/**
 *
 */
GuiObject::GuiObject(const GuiObject &source) : GuiEventHandler(),
         m_Rect(source.m_Rect), m_Active(source.m_Active), m_Visible(source.m_Visible), m_MouseOver(source.m_MouseOver),
   m_PanelPosition(source.m_PanelPosition), m_Drag(source.m_Drag), m_DragOnlyWhenMouseOver(source.m_DragOnlyWhenMouseOver), m_LastMousePosition(source.m_LastMousePosition)
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
bool GuiObject::operator==(GuiObject &source)
{
   bool result = true;

   if (m_Rect != source.m_Rect) result = false;
   if (m_Visible != source.m_Visible) result = false;
   if (m_Active != source.m_Active) result = false;

   return result;
}


/**
 *
 */
/*
std::shared_ptr<GuiObject> GuiObject::makeCopy() const
{
   return std::shared_ptr<GuiObject>(cloneImplementation());
}
*/


/**
 *
 */
/*
GuiObject *GuiObject::cloneImplementation() const
{
   //return std::shared_ptr< GuiObject >(new GuiObject(*this));
   return new GuiObject(*this);
}
*/


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

   /*
   if (m_Active) {
      onMouseMove(m_LastMousePosition);
   }
   */

   //if (!active) m_MouseOver=false;

}


/**
 *
 */
bool GuiObject::getActive()
{
   return m_Active;
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
void GuiObject::setVisibleAndActive(bool in)
{
   std::stringstream st;

   st << getName() << "; setactive: " << in ? "FALSE" : "TRUE";

   STLOG(st);

   m_Visible = in;
   m_Active = in;
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
/*
bool GuiObject::onLeftMouseButtonPressed(const Vector2d& pos)
{
   m_Drag = true;
   return false;
}
*/

/**
 *
 */
/*
bool GuiObject::onLeftMouseButtonReleased(const Vector2d& pos)
{
   m_Drag = false;
   return false;
}
*/

/**
 *
 */
 /*
bool GuiObject::onRightMouseButtonPressed(const Vector2d& pos)
{
   return false;
}
*/


/**
 *
 */
 /*
bool GuiObject::onRightMouseButtonReleased(const Vector2d& pos)
{
   return false;
}
*/




/**
 *
 */
void GUSGAME_DLL GuiObject::handleMouseMotion(MouseMotionEvent &mouseMotion)
{
   onMouseMove(mouseMotion.getPosition());
}



/**
 *
 */

bool GuiObject::handleMouseButton(MouseButtonEvent &mouseButtonEvent)
//void GameEventHandler::HandleMouseButton(Uint8 type,SDL_MouseButtonEvent buttonEvent)
{
   return false;
}



/**
 *
 */
void GuiObject::setPanelPosition(const Vector2d& pos)
{
   m_PanelPosition = pos;
}


/**
 *
 */
void GuiObject::onMouseMove(const Vector2d& pos)
{
   GuiEventHandler::onMouseMove(pos);

   m_MouseOver = false;
   if (m_Active) {
      if (m_Rect.isPointOverTranslated(pos, GraphicsHandler::instance().getZoomX(), GraphicsHandler::instance().getZoomY())) {
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
 /*
void GuiObject::onMouseScrollUp(const Vector2d& pos)
{
}
*/


/**
 *
 */
 /*
void GuiObject::onMouseScrollDown(const Vector2d& pos)
{
}
*/


/**
 *
 */
 /*
void GuiObject::onDrag(const Vector2d& pos)
{
   if (m_MouseOver) {
      //std::stringstream st;
      //st << "GuiObject::Drag:" << pos.x << "," << pos.y;
      //STLOG(st);

   }
}
*/


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


/**
 *
 */
void GuiObject::setName(std::string inName)
{
   m_Name = inName;
}


/**
 *
 */
std::string GuiObject::getName()
{
   return m_Name;
}


/**
 *
 */
void GuiObject::print()
{
   std::cout << getName() << " : " << getActive() << std::endl;
}


// end of namespace
// ----------------
}
