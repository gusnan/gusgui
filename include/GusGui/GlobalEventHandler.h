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
#ifndef __HEADER_GUSGUI_GLOBAL_EVENT_HANDLER_
#define __HEADER_GUSGUI_GLOBAL_EVENT_HANDLER_

#include "DynamicLink.h"

#include "GuiObject.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
class GlobalEventHandler : public GuiObject
{
public:
   GUSGAME_DLL GlobalEventHandler();

   //GUSGAME_DLL GuiEventHandler(std::vector<GuiObjectPtr> *guiList);
   GUSGAME_DLL GlobalEventHandler(const GlobalEventHandler &source);
   virtual GUSGAME_DLL ~GlobalEventHandler();


   virtual void draw(const Vector2d& pos, float alpha = 1.0f);
   virtual void update();


   virtual bool onLeftMouseButtonPressed(const Vector2d& pos);
   virtual bool GUSGAME_DLL onLeftMouseButtonReleased(const Vector2d& pos);

   virtual bool onRightMouseButtonPressed(const Vector2d& pos);
   virtual bool onRightMouseButtonReleased(const Vector2d& pos);

   void GUSGAME_DLL onMouseMove(const Vector2d& pos);

   void GUSGAME_DLL onMouseScrollUp(const Vector2d& pos);
   void GUSGAME_DLL onMouseScrollDown(const Vector2d& pos);

   void GUSGAME_DLL handleMouseLeaveScreen();

   virtual void GUSGAME_DLL handleMouseMotion(MouseMotionEvent &mouseMotion);
   virtual bool GUSGAME_DLL handleMouseButton(MouseButtonEvent &mouseButtonEvent);

   virtual bool GUSGAME_DLL handleUserEvent(UserEvent &userEvent) override;

   void GUSGAME_DLL handleActiveEvent(ActiveEvent &activeEvent);

   std::shared_ptr<GusGui::GlobalEventHandler> makeCopy() const;
   virtual GlobalEventHandler *cloneImplementation() const override;

protected:

   //std::vector<GuiObjectPtr> *m_GuiList;
};

// end of namespace
// ----------------
};

#endif /*__HEADER_GLOBAL_EVENT_HANDLER_*/
