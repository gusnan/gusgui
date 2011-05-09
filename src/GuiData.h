/**
 * This file is part of Damnation of the Gods
 * Copyright 2008,2009 Andreas Rönnquist
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
#ifndef __HEADER_GUI_DATA_
#define __HEADER_GUI_DATA_

/**
 *
 */
namespace GuiLib
{

/**
 *
 */
namespace GuiData
{
	/*
	extern GLBitmap *menuBorder_TopLeft;
	extern GLBitmap *menuBorder_TopRight;
	extern GLBitmap *menuBorder_BottomLeft;
	extern GLBitmap *menuBorder_BottomRight;
	*/

	extern GLBitmap *menuBorder_Top;
	extern GLBitmap *menuBorder_Bottom;
	extern GLBitmap *menuBorder_Left;
	extern GLBitmap *menuBorder_Right;

	extern GLBitmap *menuBorder_Top_NoTrans;
	extern GLBitmap *menuBorder_Bottom_NoTrans;
	extern GLBitmap *menuBorder_Left_NoTrans;
	extern GLBitmap *menuBorder_Right_NoTrans;
	
	extern GLBitmap *menuBackground;
	
	//extern GLBitmap *buttonNormal,*buttonHover,*buttonPressed;
	
	//extern GLBitmap *checkBoxActivePressed,*checkBoxActive,*checkBoxPressed,*checkBox;
	extern GLBitmap *guiData;
	
	extern Font *guiFont;
	extern Font *guiSmallFont;
	extern Font *guiBigFont;
	
	void setGuiGraphics(std::vector<Bitmap*> guiBitmapList);
	void setGuiFont(Font *guiFont);
	void setGuiSmallFont(Font *smallFont);
	void setGuiBigFont(Font* bigFont);
	
	
	void freeGuiGraphics();
};

// end of namespace
// ----------------
}

#endif
