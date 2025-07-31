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
#ifndef __HEADER_PANEL_
#define __HEADER_PANEL_

/**
 *
 */
namespace GusGui
{

/**
 *
 */
class Panel : public GuiObject
{
public:
   Panel();

   Panel(Rect rect, std::string name, bool transFrame = true);
   Panel(const Panel& source);
   virtual ~Panel();

   Panel& operator=(const Panel& source);


   void addGuiObject(const std::shared_ptr<GuiObject> &guiObject);

   void draw(const Vector2d& pos, float alpha = 1.0f) override;

   void update() override;

   void setDrawFrame(bool drawFrame = true);
   void setDrawBackground(bool drawBackground = true);

   void setMouseOver(bool b) override;

   virtual bool handleUserEvent(UserEvent &event) override;
   virtual bool handleKeyboardEvent(KeyEvent &event) override;

   virtual bool onLeftMouseButtonPressed(const Vector2d& pos) override;
   virtual bool onLeftMouseButtonReleased(const Vector2d& pos) override;

   virtual bool onRightMouseButtonPressed(const Vector2d& pos) override;
   virtual bool onRightMouseButtonReleased(const Vector2d& pos) override;

   virtual void onMouseMove(const Vector2d& pos) override;

   virtual void onMouseScrollUp();
   virtual void onMouseScrollDown();

   virtual void onDrag(const Vector2d& pos) override;

   virtual void setVisible(bool visible = true) override;

   virtual void setActive(bool active = true) override;

   virtual void setVisibleAndActive(bool active = true) override;
   
   void print() override;

protected:

   std::vector<std::shared_ptr<GuiObject>> *m_GuiList;

   bool m_DrawFrame;
   bool m_TransparentFrame;
   bool m_DrawBackground;

};

// end of namespace
// ----------------
}

#endif /*__HEADER_PANEL_*/
