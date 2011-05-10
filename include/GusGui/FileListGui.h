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
#ifndef __HEADER_GUI_FILELIST_
#define __HEADER_GUI_FILELIST_

/**
 *
 */
namespace GusGui
{


/**
 * A filelist which is to be used for the load and save dialogs.
 */
class FileListGui : public GuiObject
{
public:
	FileListGui(Rect rect);
	virtual ~FileListGui();

	virtual void draw(const Vector2d &pos,float opacity=1.0f);

	virtual void update();
	
protected:
	
	// How many lines of text are visible?
	int m_VisibleLines;
	
};

// end of namespace
// ----------------
};

#endif /*__HEADER_GUI_FILELIST_*/
