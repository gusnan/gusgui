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
#include <list>
#include <string>
#include <sstream>
#include <fstream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "LoaderMeter.h"

#include "GuiDraw.h"

#include "GuiData.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
LoaderMeter::LoaderMeter(Rect rect,int maxValue) : GuiObject(rect), m_MaxValue(), m_Value(),
		m_FullWidth()
{
	m_MaxValue=maxValue;
	m_Value=0;
	
	rect.setCenter(GraphicsHandler::instance()->getScreenRect().getCenter());
	
	//GuiObject(rect);
	GuiObject::setRect(rect);
	
	m_FullWidth=rect.size.x;
}

/**
 *
 */
LoaderMeter::~LoaderMeter()
{
}

/**
 *
 */
void LoaderMeter::draw(const Vector2d &pos,float opacity)
{
	
	double percent=(double)(m_Value)/(double)(m_MaxValue);
	
	/*
	std::stringstream st;
	
	st << "Percent:" << percent;
	STLOG(st);
	*/
	
	int newsize=(int)((double)(percent)*(double)(m_FullWidth));
	
	if (m_Value%8==0) {
		
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
		
		Rect rect=getRect();
		
		GuiDraw::drawGuiRect(rect+pos,false);
		
		Rect newRect=rect;
		
		newRect.size.x=newsize;
		
		GLPrimitives::rectFill(newRect+pos,colorRed);
		
		Rect centerRect=rect+pos;
		
		GuiData::guiFont->drawCenter(centerRect.getCenter()+Vector2d(2,2),"Loading...",colorBlack);
		GuiData::guiFont->drawCenter(centerRect.getCenter(),"Loading...",colorWhite);
		
		SDL_GL_SwapBuffers();
	}
}

/**
 *
 */
void LoaderMeter::update()
{
}

/**
 *
 */
void LoaderMeter::increaseValue()
{
	m_Value++;
	
	/*
	std::stringstream st;
	
	st << m_Value;
	
	STLOG(st);
	*/
	
	draw(Vector2d(0,0),1.0f);
	
	
}

// end of namespace
// ----------------
};
