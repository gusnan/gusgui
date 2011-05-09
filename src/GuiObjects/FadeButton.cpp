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
#include <sstream>
#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "Button.h"
#include "FadeButton.h"

#include "GuiHandler.h"

/**
 *
 */
namespace GuiLib
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
	
	GLPrimitives::rectFill(newRect,col);
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
		m_Fade-=(Timer::instance()->getDeltaTime()*m_Speed);
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
