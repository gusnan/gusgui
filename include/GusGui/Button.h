/**
 * This file is part of Damnation of the Gods
 * Copyright 2008-2011 Andreas Rönnquist
 *
 * Damnation of the Gods is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as published 
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Damnation of the Gods is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Damnation of the Gods.  
 * If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __HEADER_BUTTON_
#define __HEADER_BUTTON_

/**
 *
 */
namespace GuiLib
{

/**
 *
 */
class Button : public GuiObject
{
public:
	Button(Rect rect,GLBitmap *icon=0,bool invisible=false);
	Button(Rect sourceRect,Rect rect,GLBitmap *icon=0,bool invisible=false);

	Button(const Button& source);

	Button& operator=(const Button& source);

	virtual ~Button();

	Button *makeCopy();

	void draw(const Vector2d& pos,float alpha=1.0);

	bool getPressed();
	bool getDown();

	virtual void update();

	void setGraphics(GLBitmap *button,GLBitmap *buttonPressed,GLBitmap *buttonHover);

	//void SetTextBitmap(GLBitmap *textBitmap);

	void setText(std::string file,int line,std::string text);

	void setEvent(UserEvent *event);
	UserEvent *getEvent();

	void setActivateOnDown(bool active=true);

	//void SetInvisible(bool invisible=true);
	
	//GLBitmap *DrawTextCentered(std::string text);
	
	void setMoveOnDown(bool move=true);
	
	bool handleUserEvent(UserEvent &event);
	virtual bool handleKeyboardEvent(KeyEvent &event);

	virtual bool onLeftMouseButtonPressed(const Vector2d& pos);
	virtual void onLeftMouseButtonReleased(const Vector2d& pos);
	
	virtual void onMouseMove(const Vector2d& pos);

protected:
	
	bool m_Down;
	bool m_Pressed;

	GLBitmap *m_Icon;

/*
	FrameBuffer *m_FrameBufferPressed;
	FrameBuffer *m_FrameBufferHover;
	FrameBuffer *m_FrameBufferStandard;
*/

	std::string m_Text;

	UserEvent *m_ButtonEvent;

	bool m_ActivateOnDown;

	bool m_Invisible;

	GLBitmap *m_TextBitmap;
	
	Rect m_SourceRect;
	
	bool m_MoveOnDown;
	
	//bool m_HasEvent;
	
};

// end of namespace
// ---------------
}

#endif /*__HEADER_BUTTON_*/
