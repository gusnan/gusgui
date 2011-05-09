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
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "Button.h"

#include "GuiHandler.h"

#include "GuiData.h"

#include "GuiDraw.h"

/**
 *
 */
namespace GuiLib
{

/**
 *
 */
Button::Button(Rect rect,GLBitmap *icon,bool invisible) : GuiObject(rect),
	m_Down(false), m_Pressed(false), m_Icon(icon), m_TextBitmap(0), m_Invisible(invisible),
	m_Text(""), m_SourceRect(Rect()), m_ActivateOnDown(false), m_ButtonEvent(), m_MoveOnDown(false)
{
	//SetInvisible(invisible);
	
	m_Active=true;
	m_MouseOver=false;
	
	/*
	m_TextBitmap=0;
	
	m_Invisible=invisible;
	*/
	
	//m_HasEvent=false;

#ifndef _NO_FRAME_BUFFER_
	m_FrameBufferStandard=0;
	m_FrameBufferPressed=0;
	m_FrameBufferHover=0;
#endif
	
	if (!m_Invisible) {
		//m_Rect=Rect(rect.position,GuiData::buttonNormal->GetSize());
		m_Rect=rect; //Rect(rect.position,GuiData::buttonNormal->GetSize());
		
	} else {
	}
	
	m_Icon=icon;
	
	m_SourceRect=Rect(-1,-1,-1,-1);
	
	//m_TextBitmap=0;
		
	/*
	m_ActivateOnDown=false;
	m_MouseOver=false;
	m_Pressed=false;
	*/
	
	m_MoveOnDown=false;
	
	m_ButtonEvent=NULL;
	
}

/**
 *
 */
Button::Button(Rect sourceRect,Rect rect,GLBitmap *icon,bool invisible) : GuiObject(rect),
	m_Down(false), m_Pressed(false), m_Icon(icon), m_TextBitmap(0), m_Invisible(invisible),
	m_Text(""), m_SourceRect(), m_ActivateOnDown(false), m_ButtonEvent(), m_MoveOnDown(false)
{
	//SetInvisible(invisible);
	
	m_Down=false;
	m_Pressed=false;
	m_Active=true;
	
	m_Icon=icon;
	
	m_TextBitmap=0;
	
	m_Invisible=invisible;

#ifndef _NO_FRAME_BUFFER_
	m_FrameBufferStandard=0;
	m_FrameBufferPressed=0;
	m_FrameBufferHover=0;
#endif
	
	//m_HasEvent=false;
	
	if (!m_Invisible) {
		m_Rect=rect; 
		
	} else {
	}
	
	m_SourceRect=sourceRect;
	
	m_Icon=icon;
	
	//m_TextBitmap=0;
		
	m_ActivateOnDown=false;
	m_MouseOver=false;
	m_Pressed=false;
	
	m_MoveOnDown=false;
		
	m_ButtonEvent=NULL;
	
}

/**
 *
 */
Button::Button(const Button& source) : GuiObject(source),
	m_Down(false), m_Pressed(false), m_Icon(), m_TextBitmap(0), m_Invisible(false),
	m_Text(""), m_SourceRect(), m_ActivateOnDown(false), m_ButtonEvent(), m_MoveOnDown(false)
{
	m_Down=source.m_Down;
	m_Pressed=source.m_Pressed;
	m_Active=source.m_Active;
	
	m_Icon=source.m_Icon;
	
	m_TextBitmap=source.m_TextBitmap->makeCopy();
	
	m_Invisible=source.m_Invisible;

#ifndef _NO_FRAME_BUFFER_
	m_FrameBufferStandard=0;
	m_FrameBufferPressed=0;
	m_FrameBufferHover=0;
#endif
	
	//m_HasEvent=false;
	
	if (!m_Invisible) {
		m_Rect=source.m_Rect; 
		
	} else {
	}
	
	m_SourceRect=source.m_SourceRect;
	
	m_Icon=source.m_Icon->makeCopy();
	
	//m_TextBitmap=0;
		
	m_ActivateOnDown=source.m_ActivateOnDown;
	m_MouseOver=source.m_MouseOver;
	m_Pressed=source.m_Pressed;
	
	m_MoveOnDown=source.m_MoveOnDown;
		
	m_ButtonEvent=source.m_ButtonEvent;	
}

/**
 *
 */
Button& Button::operator=(const Button& source)
{
	if (this!=&source) {
		m_Down=source.m_Down;
		m_Pressed=source.m_Pressed;
		m_Active=source.m_Active;
		
		m_Icon=source.m_Icon;
		
		m_TextBitmap=source.m_TextBitmap->makeCopy();
		
		m_Invisible=source.m_Invisible;

	#ifndef _NO_FRAME_BUFFER_
		m_FrameBufferStandard=0;
		m_FrameBufferPressed=0;
		m_FrameBufferHover=0;
	#endif
		
		//m_HasEvent=false;
		
		if (!m_Invisible) {
			m_Rect=source.m_Rect; 
			
		} else {
		}
		
		m_SourceRect=source.m_SourceRect;
		
		m_Icon=source.m_Icon->makeCopy();
		
		//m_TextBitmap=0;
			
		m_ActivateOnDown=source.m_ActivateOnDown;
		m_MouseOver=source.m_MouseOver;
		m_Pressed=source.m_Pressed;
		
		m_MoveOnDown=source.m_MoveOnDown;
			
		m_ButtonEvent=source.m_ButtonEvent;	
	}
	
	return *this;
}

/**
 *
 */
Button::~Button()
{
	if (m_TextBitmap) {
		delete m_TextBitmap;
		m_TextBitmap=NULL;
	}
	
#ifndef _NO_FRAME_BUFFER_
	
	if (m_FrameBufferPressed) {
		delete m_FrameBufferPressed;
		m_FrameBufferPressed=NULL;
	}
	if (m_FrameBufferHover) {
		delete m_FrameBufferHover;
		m_FrameBufferHover=NULL;
	}
	if (m_FrameBufferStandard) {
		delete m_FrameBufferHover;
		m_FrameBufferHover=NULL;
	}
#endif
	
}

Button *Button::makeCopy()
{
	return new Button(*this);
}

/**
 *
 */
void Button::draw(const Vector2d& pos,float alpha)
{
	Vector2d newpos=getRect().position+pos;
	
	Rect newrect=Rect(newpos,getRect().size);
	
	Vector2d size=Vector2d(108,22); //GuiData::buttonNormal->GetSize();
	
	//Vector2d shadePos(2,2);
	
	//if (m_FrameBufferStandard!=0) {
	
	if (m_Down) {
		//if (m_FrameBufferPressed) m_FrameBufferPressed->Blit(newrect.position,alpha);
		
		if (m_TextBitmap) {
			//GuiData::buttonPressed->Blit(newpos,alpha);
			GuiData::guiData->blit(Rect(0,85,108,22),newpos,alpha);
		
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			m_TextBitmap->blitCenterColor(Rect(newrect.position+Vector2d(1+2,-1+2),size),colorBlack,alpha);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			m_TextBitmap->blitCenter(Rect(newrect.position+Vector2d(1,-1),size),alpha);			
		}
		
	} else {
		if (m_MouseOver) {
			//if (m_FrameBufferHover) m_FrameBufferHover->Blit(newrect.position,alpha);
			
			if (m_TextBitmap) {
				//GuiData::buttonHover->Blit(newpos,alpha);
				GuiData::guiData->blit(Rect(0,107,108,22),newpos,alpha);
				
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				m_TextBitmap->blitCenterColor(newrect+Vector2d(2,2),colorBlack,alpha);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);
				m_TextBitmap->blitCenter(newrect,alpha);				
			}
			
		} else {
			//if (m_FrameBufferStandard) m_FrameBufferStandard->Blit(newrect.position,alpha);
			//if (!m_Invisible) 
			
			if (m_TextBitmap) {
				//GuiData::buttonNormal->Blit(newpos,alpha);
				GuiData::guiData->blit(Rect(0,63,108,22),newpos,alpha);
				
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				m_TextBitmap->blitCenterColor(newrect+Vector2d(2,2),colorBlack,alpha);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);
				m_TextBitmap->blitCenter(newrect,alpha);
			}
		}
	}
		
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	
	if (m_Icon) {
		
		Vector2d newPos=newrect.position;
		
		if (m_Down) {
			if (m_MoveOnDown) {
				newPos+=Vector2d(1,1);
			}
		}
		
		if (m_SourceRect.position.x!=-1) {
			m_Icon->blit(m_SourceRect,newPos,alpha);
		} else {
			m_Icon->blit(newPos,alpha);
		}
	}
	
}

/**
 *
 */
bool Button::getPressed()
{
	bool result=m_Pressed;
	m_Pressed=false;
	return result;
}

/**
 *
 */
bool Button::getDown()
{
	return m_Down;
}


/**
 *
 */
void Button::update()
{
	if (!m_Active) {
		m_MouseOver=false;
	}
}

/**
 *
 */
void Button::setGraphics(GLBitmap *button,GLBitmap *buttonPressed,GLBitmap *buttonHover)
{
	/*
	m_BitmapStandard=button;
	m_BitmapHover=buttonHover;
	m_BitmapPressed=buttonPressed;
	*/
	
	
	m_Rect.size=Vector2d(108,22); //GuiData::buttonNormal->GetSize();
	//GuiData::buttonNormal->GetSize();
	
}

/**
 *
 */
/*
void Button::SetTextBitmap(GLBitmap *textBitmap)
{
	Bitmap *tempText;
	Bitmap *buttonText;
		
	tempText=GuiHandler::guiFont->RenderText("Hej!",colorWhite);
	
	buttonText=new Bitmap(tempText->GetSize());

	m_TextBitmap=new GLBitmap(tempText);
	
	delete tempText;
}
*/

/**
 *
 */
void Button::setText(std::string file,int line,std::string text)
{
	/*m_Text=text;*/
	
	m_TextBitmap=GuiDraw::drawTextCentered(text/*m_Text*/);
	
	/*
	m_FrameBufferStandard=GuiDraw::MakeTextButtonStandard(text);
	*/
	///m_FrameBufferPressed=GuiDraw::MakeTextButtonPressed(text);
	//m_FrameBufferHover=GuiDraw::MakeTextButtonHover(text);
	
	//SetSize(m_FrameBufferStandard->GetSize());
	//SetSize(GuiData::buttonNormal->GetSize());
	
	setSize(Vector2d(108,22)); //GuiData::buttonNormal->GetSize();
}


/**
 *	SetEvent
 *		Sets the event thats is executed when the button is pressed.
 */
void Button::setEvent(UserEvent *event)
{
	m_ButtonEvent=event;
	//m_HasEvent=true;
}

/**
 *
 */
UserEvent *Button::getEvent()
{
	return m_ButtonEvent;
}

/**
 *
 */
void Button::setActivateOnDown(bool onDown)
{
	m_ActivateOnDown=onDown;
}

/**
 *
 */
void Button::setMoveOnDown(bool move)
{
	m_MoveOnDown=move;
}

/**
 *
 */
/*void Button::SetInvisible(bool invisible)
{
	m_Invisible=invisible;
}
*/

/**
 *
 */
bool Button::handleUserEvent(UserEvent &event)
{
	return false;
}

/**
 *
 */
bool Button::handleKeyboardEvent(KeyEvent &event)
{
	return false;
}

/**
 *
 */
bool Button::onLeftMouseButtonPressed(const Vector2d& pos)
{
	
	GuiObject::onLeftMouseButtonPressed(pos);
	
	bool handled=false;
	if (m_Active) {
		if (m_MouseOver) {
			m_Down=true;
			
			if (m_ActivateOnDown) {
				m_Pressed=true;
				if (m_ButtonEvent) {
					m_ButtonEvent->pushEvent();			
				}
			}
			//LOG("handled");
			handled=true;
		}
	}
	return handled;
}

/**
 *
 */
void Button::onLeftMouseButtonReleased(const Vector2d& pos)
{
	GuiObject::onLeftMouseButtonReleased(pos);
	
	if (m_Down) {
	m_Down=false;
	if (m_Active) {
		if (m_MouseOver) {

			if (!m_ActivateOnDown) {
				m_Pressed=true;
				if (m_ButtonEvent) {
					m_ButtonEvent->pushEvent();
 				}
			}
		}
	}
	}
}

/**
 *
 */
void Button::onMouseMove(const Vector2d& pos)
{
	GuiObject::onMouseMove(pos);
	
	if (!m_MouseOver) {
		m_Down=false;
	}
}


// end of namespace
// ----------------
}


