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
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;


#include "GuiObject.h"

#include "Button.h"
#include "DelayButton.h"

#include "GuiDraw.h"
#include "GuiData.h"
#include "GuiHandler.h"


/**
 *
 */
namespace GuiLib
{

/**
 *
 */
DelayButton::DelayButton(Rect rect,Rect sourceRect,Rect sourceRectPressed,GLBitmap *icon,Rect iconSourceRect) : Button(rect,icon),
	m_Delay(0.0f), m_Speed(1.0f), m_IconSourceRect(), m_SourceRectPressed()
{
	m_Delay=0.0f;
	
	//m_TextBitmap=0;
	
	/*
	m_FrameBufferStandard=GuiDraw::MakeStandardButton(rect.size,icon);
	m_FrameBufferPressed=GuiDraw::MakePressedButton(rect.size,icon);
	*/
	
	m_Speed=1.0f;
	
	m_IconSourceRect=iconSourceRect;
	
	m_SourceRect=sourceRect;
	m_SourceRectPressed=sourceRectPressed;
	
	m_MouseOver=false;
	
	//m_FrameBufferHover=m_FrameBufferStandard;
	
	/*
	m_BitmapStandard=GuiData::buttonNormal;
	m_BitmapHover=GuiData::buttonHover;
	m_BitmapPressed=GuiData::buttonPressed;
	*/
}

/**
 *
 */
DelayButton::~DelayButton()
{
	//REMOVE(m_TextBitmap);
}

/**
 *
 */
void DelayButton::draw(const Vector2d& pos,float alpha)
{
	Vector2d newpos=getRect().position+pos;
	
	Rect newrect=Rect(newpos,getRect().size);
	
	Vector2d shadePos(2,2);
		
		if (m_Delay!=0.0f) {
			//if (m_FrameBufferPressed) m_FrameBufferPressed->Blit(newrect.position,alpha);
			//GuiDraw::DrawPressedButton(newrect);
			GuiData::guiData->blit(m_SourceRect,newpos,alpha);
			
			m_Icon->blitCenter(m_IconSourceRect,newrect+Vector2d(2,2),alpha);

		} else {
			//GuiDraw::DrawStandardButton(newrect);
			GuiData::guiData->blit(m_SourceRectPressed,newpos,alpha);
			m_Icon->blitCenter(m_IconSourceRect,newrect,alpha);
		}
}


/**
 *
 */
void DelayButton::update()
{
	//std::cout << "DelayButton::Update" << std::endl;
	if (m_Delay>0.0f) {
		m_Delay-=(float)(Timer::instance()->getDeltaTime()*m_Speed);
	} else {
		m_Delay=0.0f;
	}
}

/**
 *
 */
bool DelayButton::getPressed() const
{
	bool result=false;
	
	if (m_Delay!=0.0f) result=true;
	
	return result;
}

/**
 *
 */
void DelayButton::setPressed()
{
	m_Delay=1.0f;
	
	//SDL_PushEvent(&m_ButtonEvent);
	m_ButtonEvent->pushEvent();
}

/**
 *
 */
void DelayButton::setSpeed(float speed)
{
	m_Speed=speed;
}

/**
 *
 */
bool DelayButton::handleKeyboardEvent(KeyEvent &event)
{
	return false;
}


/**
 *
 */
bool DelayButton::onLeftMouseButtonPressed(const Vector2d& pos)
{
	bool handled=false;
	
	if (m_MouseOver) {
		if (!getPressed()) {
			setPressed();
			handled=true;
		}
	}
	return handled;
}


/**
 *
 */
void DelayButton::onLeftMouseButtonReleased(const Vector2d& pos)
{
}


// end of namespace
// ----------------
};
