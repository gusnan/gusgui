/**
 * This file is part of Damnation of the Gods
 * Copyright 2008,2009,2010 Andreas Rönnquist
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
#ifndef __HEADER_GUI_DRAW_
#define __HEADER_GUI_DRAW_

/**
 *
 */
namespace GuiLib
{
	
/**
 *
 */
namespace GuiDraw
{
	void drawGuiRect(Rect rect,bool drawTransparentFrame,float opacity=1.0f);
	
#ifndef _NO_FRAME_BUFFER_
	FrameBuffer *makeTextButtonStandard(std::string text);
	FrameBuffer *makeTextButtonHover(std::string text);
	FrameBuffer *makeTextButtonPressed(std::string text);
	
	FrameBuffer *makeStandardButton(Vector2d size,GLBitmap *icon=0);
	FrameBuffer *makePressedButton(Vector2d size,GLBitmap *icon=0);
	
#endif
	void drawStandardButton(Rect rect,GLBitmap *icon=0);
	
	void drawPressedButton(Rect rect,GLBitmap *icon=0);
	
	void splitString(std::string instring,std::string& text,std::string& shortcut);
	
	//void MakeTextButton(FrameBuffer *standard,FrameBuffer *hover,FrameBuffer *pressed,std::string text);
	
	GLBitmap *drawTextCentered(std::string intext);
	
	void drawNiceTextSmall(Vector2d pos,std::string st,Color col,float opacity=1.0f);
	void drawNiceText(Vector2d pos,std::string st,Color col,float opacity=1.0f);
	
	void drawNiceTextSmallCenter(Vector2d pos,std::string st,Color col,float opacity=1.0f);
	void drawNiceTextCenter(Vector2d pos,std::string st,Color col,float opacity=1.0f);



};

// end of namespace
// ----------------
}

#endif /*__HEADER_GUI_DRAW_*/
