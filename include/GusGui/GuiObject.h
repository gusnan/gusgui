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
#ifndef __HEADER_GUI_OBJECT_
#define __HEADER_GUI_OBJECT_

/**
 *
 */
namespace GusGui
{

const int GUI_OBJECT_CENTER_HORISONTALLY = 1;
const int GUI_OBJECT_CENTER_VERTICALLY = 2;
const int GUI_OBJECT_CENTER_BOTH = 3;

class GuiObject;

/**
 *
 */
class GuiObject
{
public:
   GuiObject();
   GuiObject(Rect rect);
   virtual ~GuiObject();

   bool operator==(GuiObject &inObject);

   std::shared_ptr<GuiObject> makeCopy() const;

   Vector2d getPosition() const;
   Rect getRect() const;
   void setRect(const Rect& rect);

   void setSize(const Vector2d& size);

   void setCenter(const Vector2d& pos);

   virtual void draw(const Vector2d& pos, float alpha = 1.0f) = 0;

   virtual void update() = 0;

   virtual void setActive(bool active = true);

   virtual void setMouseOver(bool over);
   bool getMouseOver() const;


   bool getVisible() const;
   virtual void setVisible(bool visible = true);
   virtual void switchVisible();

   virtual void setVisibleAndActive(bool active = true);


   //virtual bool HandleUserEvent(SDL_UserEvent event);
   virtual bool handleUserEvent(UserEvent &event);

   virtual bool handleKeyboardEvent(KeyEvent &event);

   virtual void gainFocus();
   virtual void releaseFocus();

   virtual bool onLeftMouseButtonPressed(const Vector2d& pos);
   virtual bool onLeftMouseButtonReleased(const Vector2d& pos);

   virtual bool onRightMouseButtonPressed(const Vector2d& pos);
   virtual bool onRightMouseButtonReleased(const Vector2d& pos);

   virtual void onMouseMove(const Vector2d& pos);

   virtual void onMouseScrollUp(const Vector2d& pos);
   virtual void onMouseScrollDown(const Vector2d& pos);

   virtual void onDrag(const Vector2d& pos);

   void setPanelPosition(const Vector2d& pos);

   void setCenter(Rect sourceRect, int directions);

   void setName(std::string inName);
   std::string getName();

   virtual void print();

protected:

   Rect m_Rect;

   bool m_MouseOver;

   bool m_Active;

   bool m_Visible;

   Gus::GraphicsLib::Vector2d m_PanelPosition;

   bool m_Drag;

   bool m_DragOnlyWhenMouseOver;

   Gus::GraphicsLib::Vector2d m_LastMousePosition;

   std::string m_Name;

private:
   virtual std::shared_ptr<GuiObject> cloneImplementation() const;
};

// end of namespace
// ----------------

}

#endif
