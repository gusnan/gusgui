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
#include <fstream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiData.h"

#include "GuiObject.h"

#include "FileListGui.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
FileListGui::FileListGui(Rect rect) : GuiObject(rect), m_VisibleLines(0)
{

	int fontHeight=GuiData::guiFont->getHeight(); // 13
	
	m_VisibleLines=((getRect().size.y)/fontHeight)-1;
	
}

/**
 *
 */
FileListGui::~FileListGui()
{
}

/**
 *
 */
void FileListGui::draw(const Vector2d &pos,float opacity)
{
	Rect newRect=getRect()+pos;
	Vector2d newPos=newRect.position;
	
	//GuiDraw::drawGuiRect(newRect,true,opacity);
	
	Primitives::rect(newRect,colorWhite);
	
	std::stringstream st;
	
	for (int co=0;co<m_VisibleLines;co++) {
		
		st.str("");
		st << "Kweriohsdfyyjpqj " << co;
				
		GuiData::guiFont->draw(newPos+Vector2d(2,2+14*co),st.str(),colorWhite);
	}
}

/**
 *
 */
void FileListGui::update()
{
}

// end of namespace
// ----------------
};
