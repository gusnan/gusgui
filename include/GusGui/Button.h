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
	Button(const Rect &rect, Bitmap *icon = 0, bool invisible = false);
	Button(const Rect &sourceRect, const Rect &rect, Bitmap *icon = 0, bool invisible = false);

	Button(const Button& source);

	Button& operator=(const Button& source);

	virtual ~Button();

	Button *makeCopy();

	void draw(const Vector2d& pos, float alpha = 1.0);

	bool getPressed();
	bool getDown();

	virtual void update();

	virtual void setMouseOver(bool over);

	void setGraphics(Bitmap *button, Bitmap *buttonPressed, Bitmap *buttonHover);

	//void SetTextBitmap(GLBitmap *textBitmap);

	void setText(std::string file, int line, std::string text);

	void setPressEvent(UserEvent *event);
	UserEvent *getPressEvent();
	
	void setReleaseEvent(UserEvent *event);
	UserEvent *getReleaseEvent();

	void setActivateOnDown(bool active = true);

	//void SetInvisible(bool invisible=true);

	//GLBitmap *DrawTextCentered(std::string text);

	void setMoveOnDown(bool move = true);

	bool handleUserEvent(UserEvent &event);
	virtual bool handleKeyboardEvent(KeyEvent &event);

	virtual bool onLeftMouseButtonPressed(const Vector2d& pos);
	virtual void onLeftMouseButtonReleased(const Vector2d& pos);

	virtual void onMouseMove(const Vector2d& pos);

	virtual void pressed();

protected:

	bool m_Down;
	bool m_Pressed;

	Bitmap *m_Icon;

/*
	FrameBuffer *m_FrameBufferPressed;
	FrameBuffer *m_FrameBufferHover;
	FrameBuffer *m_FrameBufferStandard;
*/

	std::string m_Text;

	UserEvent *m_ButtonPressEvent;
	UserEvent *m_ButtonReleaseEvent;

	bool m_ActivateOnDown;

	bool m_Invisible;

	Bitmap *m_TextBitmap;

	Rect m_SourceRect;

	bool m_MoveOnDown;

	//bool m_HasEvent;

};

// end of namespace
// ---------------
}

#endif /*__HEADER_BUTTON_*/
