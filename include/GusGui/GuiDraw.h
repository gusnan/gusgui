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
#ifndef __HEADER_GUI_DRAW_
#define __HEADER_GUI_DRAW_

#define _NO_FRAME_BUFFER_

/**
 *
 */
namespace GusGui
{
	
/**
 *
 */
namespace GuiDraw
{
	void drawGuiRect(Rect rect, bool drawTransparentFrame, float opacity=1.0f);
	
#ifndef _NO_FRAME_BUFFER_
	FrameBuffer *makeTextButtonStandard(std::string text);
	FrameBuffer *makeTextButtonHover(std::string text);
	FrameBuffer *makeTextButtonPressed(std::string text);
	
	FrameBuffer *makeStandardButton(Vector2d size, Bitmap *icon=0);
	FrameBuffer *makePressedButton(Vector2d size, Bitmap *icon=0);
	
#endif
	void drawStandardButton(Rect rect, Bitmap *icon=0);
	
	void drawPressedButton(Rect rect, Bitmap *icon=0);
	
	void splitString(std::string instring,std::string& text,std::string& shortcut);
	
	//void MakeTextButton(FrameBuffer *standard,FrameBuffer *hover,FrameBuffer *pressed,std::string text);
	
	Bitmap *drawTextCentered(std::string intext);
	
	void drawNiceTextSmall(Vector2d pos,std::string st,Color col,float opacity=1.0f);
	void drawNiceText(Vector2d pos,std::string st,Color col,float opacity=1.0f);
	
	void drawNiceTextSmallCenter(Vector2d pos,std::string st,Color col,float opacity=1.0f);
	void drawNiceTextCenter(Vector2d pos,std::string st,Color col,float opacity=1.0f);



};

// end of namespace
// ----------------
}

#endif /*__HEADER_GUI_DRAW_*/
