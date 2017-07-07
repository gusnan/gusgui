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
#include <iostream>
#include <sstream>
#include <fstream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "Button.h"

#include "GuiEventHandler.h"
#include "GuiHandler.h"

#include "GuiData.h"

#include "GuiDraw.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
Button::Button(const Rect &rect, std::string name, Bitmap *icon, bool invisible) : GuiObject(rect),
	m_Down(false), m_Pressed(false), m_Icon(icon), m_TextBitmap(0), m_Invisible(invisible),
	m_Text(""), m_SourceRect(Rect()), m_ActivateOnDown(false), 
	m_ButtonPressEvent(), m_ButtonReleaseEvent(), m_MoveOnDown(false)
{
	//SetInvisible(invisible);
	
	setName(name);

	m_Active = true;
	m_MouseOver = false;

	/*
	m_TextBitmap=0;

	m_Invisible=invisible;
	*/

	//m_HasEvent=false;

#ifndef _NO_FRAME_BUFFER_
	m_FrameBufferStandard = 0;
	m_FrameBufferPressed = 0;
	m_FrameBufferHover = 0;
#endif

	if (!m_Invisible) {
		//m_Rect=Rect(rect.position,GuiData::buttonNormal->GetSize());
		m_Rect = rect; //Rect(rect.position,GuiData::buttonNormal->GetSize());

	} else {
	}

	m_Icon = icon;

	m_SourceRect = Rect(-1, -1, -1, -1);

	//m_TextBitmap=0;

	/*
	m_ActivateOnDown=false;
	m_MouseOver=false;
	m_Pressed=false;
	*/

	m_MoveOnDown = false;

	m_ButtonPressEvent = NULL;
	m_ButtonReleaseEvent = NULL;

}

/**
 *
 */
Button::Button(const Rect &sourceRect, std::string name, const Rect &rect, Bitmap *icon, bool invisible) : GuiObject(rect),
	m_Down(false), m_Pressed(false), m_Icon(icon), m_TextBitmap(0), m_Invisible(invisible),
	m_Text(""), m_SourceRect(), m_ActivateOnDown(false), m_ButtonPressEvent(),
	m_ButtonReleaseEvent(), m_MoveOnDown(false)
{
	//SetInvisible(invisible);
	
	setName(name);

	m_Down = false;
	m_Pressed = false;
	m_Active = true;

	m_Icon = icon;

	m_TextBitmap = 0;

	m_Invisible = invisible;

#ifndef _NO_FRAME_BUFFER_
	m_FrameBufferStandard = 0;
	m_FrameBufferPressed = 0;
	m_FrameBufferHover = 0;
#endif

	//m_HasEvent=false;

	if (!m_Invisible) {
		m_Rect = rect;

	} else {
	}

	m_SourceRect = sourceRect;

	m_Icon = icon;

	//m_TextBitmap=0;

	m_ActivateOnDown = false;
	m_MouseOver = false;
	m_Pressed = false;

	m_MoveOnDown = false;

	m_ButtonPressEvent = NULL;
	m_ButtonReleaseEvent = NULL;

}

/**
 *
 */
Button::Button(const Button& source) : GuiObject(source),
	m_Down(false), m_Pressed(false), m_Icon(), m_TextBitmap(0), m_Invisible(false),
	m_Text(""), m_SourceRect(), m_ActivateOnDown(false), m_ButtonPressEvent(),
	m_ButtonReleaseEvent(), m_MoveOnDown(false)
{
	m_Down = source.m_Down;
	m_Pressed = source.m_Pressed;
	m_Active = source.m_Active;

	m_Icon = source.m_Icon;

	m_TextBitmap = source.m_TextBitmap->makeCopy();

	m_Invisible = source.m_Invisible;

#ifndef _NO_FRAME_BUFFER_
	m_FrameBufferStandard = 0;
	m_FrameBufferPressed = 0;
	m_FrameBufferHover = 0;
#endif

	//m_HasEvent=false;

	if (!m_Invisible) {
		m_Rect = source.m_Rect;

	} else {
	}

	m_SourceRect = source.m_SourceRect;

	m_Icon = source.m_Icon->makeCopy();

	//m_TextBitmap=0;

	m_ActivateOnDown = source.m_ActivateOnDown;
	m_MouseOver = source.m_MouseOver;
	m_Pressed = source.m_Pressed;

	m_MoveOnDown = source.m_MoveOnDown;

	m_ButtonPressEvent = source.m_ButtonPressEvent;
	m_ButtonReleaseEvent = source.m_ButtonReleaseEvent;
}

/**
 *
 */
Button& Button::operator=(const Button& source)
{
	if (this!=&source) {
		m_Down = source.m_Down;
		m_Pressed = source.m_Pressed;
		m_Active = source.m_Active;

		m_Icon = source.m_Icon;

		m_TextBitmap = source.m_TextBitmap->makeCopy();

		m_Invisible = source.m_Invisible;

	#ifndef _NO_FRAME_BUFFER_
		m_FrameBufferStandard = 0;
		m_FrameBufferPressed = 0;
		m_FrameBufferHover = 0;
	#endif

		//m_HasEvent=false;

		if (!m_Invisible) {
			m_Rect = source.m_Rect;

		} else {
		}

		m_SourceRect = source.m_SourceRect;

		m_Icon = source.m_Icon->makeCopy();

		//m_TextBitmap=0;

		m_ActivateOnDown = source.m_ActivateOnDown;
		m_MouseOver = source.m_MouseOver;
		m_Pressed = source.m_Pressed;

		m_MoveOnDown = source.m_MoveOnDown;

		m_ButtonPressEvent = source.m_ButtonPressEvent;
		m_ButtonReleaseEvent = source.m_ButtonReleaseEvent;
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
		m_TextBitmap = NULL;
	}

#ifndef _NO_FRAME_BUFFER_

	if (m_FrameBufferPressed) {
		delete m_FrameBufferPressed;
		m_FrameBufferPressed = NULL;
	}
	if (m_FrameBufferHover) {
		delete m_FrameBufferHover;
		m_FrameBufferHover = NULL;
	}
	if (m_FrameBufferStandard) {
		delete m_FrameBufferHover;
		m_FrameBufferHover = NULL;
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
void Button::draw(const Vector2d& pos, float alpha)
{
	Vector2d newpos = getRect().position + pos;

	Rect newrect = Rect(newpos, getRect().size);

	Vector2d size = Vector2d(108, 22); //GuiData::buttonNormal->GetSize();

	//Vector2d shadePos(2,2);

	//if (m_FrameBufferStandard!=0) {

	if (m_Down) {
		//if (m_FrameBufferPressed) m_FrameBufferPressed->Blit(newrect.position,alpha);

		if (m_TextBitmap) {
			//GuiData::buttonPressed->Blit(newpos,alpha);
			GuiData::guiData->blit(Rect(0, 85, 108, 22), newpos, FlipNone, alpha);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			m_TextBitmap->blitCenterColor(Rect(newrect.position+Vector2d(1 + 2, -1 + 2), size), colorBlack, alpha);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			m_TextBitmap->blitCenter(Rect(newrect.position + Vector2d(1, -1), size), alpha);
		}

	} else {
		if (m_MouseOver) {
			//if (m_FrameBufferHover) m_FrameBufferHover->Blit(newrect.position,alpha);

			if (m_TextBitmap) {
				//GuiData::buttonHover->Blit(newpos,alpha);
				GuiData::guiData->blit(Rect(0, 107, 108, 22), newpos, FlipNone, alpha);

				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				m_TextBitmap->blitCenterColor(newrect + Vector2d(2, 2), colorBlack, alpha);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				m_TextBitmap->blitCenter(newrect, alpha);
			}

		} else {
			//if (m_FrameBufferStandard) m_FrameBufferStandard->Blit(newrect.position,alpha);
			//if (!m_Invisible)

			if (m_TextBitmap) {
				//GuiData::buttonNormal->Blit(newpos,alpha);
				GuiData::guiData->blit(Rect(0, 63, 108, 22), newpos, FlipNone, alpha);

				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				m_TextBitmap->blitCenterColor(newrect + Vector2d(2, 2), colorBlack, alpha);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				m_TextBitmap->blitCenter(newrect ,alpha);
			}
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	if (m_Icon) {

		Vector2d newPos = newrect.position;

		if (m_Down) {
			if (m_MoveOnDown) {
				newPos += Vector2d(1, 1);
			}
		}

		if (m_SourceRect.position.x != -1) {
			m_Icon->blit(m_SourceRect, newPos, FlipNone, alpha);
		} else {
			m_Icon->blit(newPos, alpha);
		}
	}

}

/**
 *
 */
bool Button::getPressed()
{
	bool result = m_Pressed;
	m_Pressed = false;
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
		m_MouseOver = false;
	}
}

/**
 *
 */
void Button::setGraphics(Bitmap *button, Bitmap *buttonPressed, Bitmap *buttonHover)
{
	/*
	m_BitmapStandard=button;
	m_BitmapHover=buttonHover;
	m_BitmapPressed=buttonPressed;
	*/


	m_Rect.size = Vector2d(108, 22); //GuiData::buttonNormal->GetSize();
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
void Button::setText(std::string file, int line, std::string text)
{
	/*m_Text=text;*/

	m_TextBitmap = GuiDraw::drawTextCentered(text/*m_Text*/);

	/*
	m_FrameBufferStandard=GuiDraw::MakeTextButtonStandard(text);
	*/
	///m_FrameBufferPressed=GuiDraw::MakeTextButtonPressed(text);
	//m_FrameBufferHover=GuiDraw::MakeTextButtonHover(text);

	//SetSize(m_FrameBufferStandard->GetSize());
	//SetSize(GuiData::buttonNormal->GetSize());

	setSize(Vector2d(108, 22)); //GuiData::buttonNormal->GetSize();
}


/**
 *	SetEvent
 *		Sets the event thats is executed when the button is pressed.
 */
void Button::setPressEvent(UserEvent *inEvent)
{
	m_ButtonPressEvent = inEvent;
	//m_HasEvent=true;
}


/**
 *
 */
void Button::setReleaseEvent(UserEvent *inEvent)
{
	m_ButtonReleaseEvent = inEvent;
}


/**
 *
 */
UserEvent *Button::getPressEvent()
{
	return m_ButtonPressEvent;
}


/**
 *
 */
UserEvent *Button::getReleaseEvent()
{
	return m_ButtonReleaseEvent;
}

/**
 *
 */
void Button::setActivateOnDown(bool onDown)
{
	m_ActivateOnDown = onDown;
}

/**
 *
 */
void Button::setMoveOnDown(bool move)
{
	m_MoveOnDown = move;
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

	bool handled = false;
	if (m_Active) {
		if (m_MouseOver) {
			m_Down = true;

			if (m_ActivateOnDown) {
				m_Pressed = true;
				pressed();
			}
			handled = true;
		}
	}
	return handled;
}

/**
 *
 */
bool Button::onLeftMouseButtonReleased(const Vector2d& pos)
{
	bool handled = false;
	GuiObject::onLeftMouseButtonReleased(pos);

	if (m_Down) {
		m_Down = false;
		if (m_Active) {
			if (m_MouseOver) {

				if (!m_ActivateOnDown) {
					m_Pressed = true;
					pressed();
				}
				released();
				handled = true;
			}
		}
	}
	
	return handled;
}

/**
 *
 */
void Button::onMouseMove(const Vector2d& pos)
{
	GuiObject::onMouseMove(pos);

	if (!m_MouseOver) {
		m_Down = false;
	}
}


/**
 *
 */
void Button::pressed()
{
	if (m_ButtonPressEvent) {
		m_ButtonPressEvent->pushEvent();
	}
}


/**
 *
 */
void Button::released()
{
	if (m_ButtonReleaseEvent) {
		m_ButtonReleaseEvent->pushEvent();
	}
}


/**
 *
 */
void Button::setMouseOver(bool over)
{
	m_MouseOver = over;

	if (!m_MouseOver) {
		m_Down = false;
	}


}

// end of namespace
// ----------------
}


