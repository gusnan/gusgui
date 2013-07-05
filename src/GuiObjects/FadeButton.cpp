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

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "Button.h"
#include "FadeButton.h"

#include "GuiEventHandler.h"
#include "GuiHandler.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
FadeButton::FadeButton(Rect rect) : Button(rect), m_Fade(0.0f), m_ShowHover(true)
{
	m_MouseOver=false;
}

/**
 *
 */
FadeButton::~FadeButton()
{
}

/**
 *
 */
void FadeButton::draw(const Vector2d& pos,float opacity)
{
	Rect newRect=getRect()+pos;
	
	if (m_Fade<0.1f) {
		if (m_MouseOver) {
			m_Fade=0.1f;
		}
		//
	}
	
	Color col=Color(1.0f,1.0f,1.0f,(float)m_Fade*opacity);
	
	Primitives::rectFill(newRect,col);
}

/**
 *
 */
void FadeButton::setPressed()
{
	m_Fade=1.0f;
	m_Pressed=true;
}

/**
 *
 */
void FadeButton::update()
{
	float m_Speed=4.0f;
	
	if (m_Fade>0.0f) {
		m_Fade-=(float)(Timer::getDeltaTime()*m_Speed);
	} else {
		m_Fade=0.0f;
	}
}

/**
 *
 */
void FadeButton::setShowHover(bool hover)
{
	m_ShowHover=hover;
}

/**
 *
 */
bool FadeButton::onLeftMouseButtonPressed(const Vector2d& pos)
{
	bool handled=false;
	if (m_Active) {
		if (m_MouseOver) {
			m_Down=true;
			
			setPressed();
			
			handled=true;
			
			if (m_ActivateOnDown) {
				m_Pressed=true;
				
				if (m_ButtonEvent) {
					m_ButtonEvent->pushEvent();
				}
			}
		}
	}
	
	return handled;
}

/**
 *
 */
void FadeButton::onLeftMouseButtonReleased(const Vector2d& pos)
{
	
}

/**
 *
 */
void FadeButton::onMouseMove(const Vector2d& pos)
{
	Button::onMouseMove(pos);
}

// end of namespace
// ----------------
};
