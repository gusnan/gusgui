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
#ifndef __HEADER_BUTTON_
#define __HEADER_BUTTON_

/**
 *
 */
namespace GusGui
{

/**
 *
 */
class Button : public GuiObject
{
public:
   Button(const Rect &rect, std::string name, std::shared_ptr<Bitmap> icon = nullptr, bool invisible = false);
   Button(const Rect &sourceRect, std::string name, const Rect &rect, std::shared_ptr<Bitmap> icon = nullptr, bool invisible = false);

   Button(const Button& source);

   Button& operator=(const Button& source);

   virtual ~Button();

   std::shared_ptr<Button> makeCopy() const;

   void draw(const Vector2d& pos, float alpha = 1.0) override;

   bool getPressed();
   bool getDown();

   virtual void update() override;

   virtual void setMouseOver(bool over) override;

   void setGraphics(Bitmap *button, Bitmap *buttonPressed, Bitmap *buttonHover);

   //void SetTextBitmap(GLBitmap *textBitmap);

   void setText(std::string file, int line, std::string text);

   void setPressEvent(std::shared_ptr<UserEvent> event);
   std::shared_ptr<UserEvent> getPressEvent();

   void setReleaseEvent(std::shared_ptr<UserEvent> event);
   std::shared_ptr<UserEvent> getReleaseEvent();

   void setGainedFocusEvent(std::shared_ptr<UserEvent> event);
   std::shared_ptr<UserEvent> getGainedFocusEvent();

   void setLostFocusEvent(std::shared_ptr<UserEvent> event);
   std::shared_ptr<UserEvent> getLostFocusEvent();

   void setActivateOnDown(bool active = true);

   //void SetInvisible(bool invisible=true);

   //GLBitmap *DrawTextCentered(std::string text);

   void setMoveOnDown(bool move = true);

   bool handleUserEvent(UserEvent &event) override;
   virtual bool handleKeyboardEvent(KeyEvent &event) override;

   virtual bool onLeftMouseButtonPressed(const Vector2d& pos) override;
   virtual bool onLeftMouseButtonReleased(const Vector2d& pos) override;

   virtual void onMouseMove(const Vector2d& pos) override;

   virtual void pressed();
   virtual void released();

protected:

   bool m_Down;
   bool m_Pressed;

   std::shared_ptr<Bitmap> m_Icon;

/*
   FrameBuffer *m_FrameBufferPressed;
   FrameBuffer *m_FrameBufferHover;
   FrameBuffer *m_FrameBufferStandard;
*/

   std::string m_Text;

   std::shared_ptr<UserEvent> m_ButtonPressEvent;
   std::shared_ptr<UserEvent> m_ButtonReleaseEvent;

   std::shared_ptr<UserEvent> m_ButtonLostFocusEvent;
   std::shared_ptr<UserEvent> m_ButtonGainedFocusEvent;

   bool m_ActivateOnDown;

   bool m_Invisible;

   std::shared_ptr<Bitmap> m_TextBitmap;

   Rect m_SourceRect;

   bool m_MoveOnDown;

   // std::string m_Name;

   //bool m_HasEvent;

private:
   virtual Button *cloneImplementation() const;

};

// end of namespace
// ---------------
}

#endif /*__HEADER_BUTTON_*/
