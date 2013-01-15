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
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::LogLib;

#include "GuiData.h"

/**
 *
 */
namespace GusGui
{

GLBitmap *GuiData::menuBorder_Top=0;
GLBitmap *GuiData::menuBorder_Bottom=0;
GLBitmap *GuiData::menuBorder_Left=0;
GLBitmap *GuiData::menuBorder_Right=0;

GLBitmap *GuiData::menuBorder_Top_NoTrans=0;
GLBitmap *GuiData::menuBorder_Bottom_NoTrans=0;
GLBitmap *GuiData::menuBorder_Left_NoTrans=0;
GLBitmap *GuiData::menuBorder_Right_NoTrans=0;
	
GLBitmap *GuiData::menuBackground=0;
	
GLBitmap *GuiData::guiData=0;

Font *GuiData::guiFont=0;
Font *GuiData::guiSmallFont=0;
Font* GuiData::guiBigFont=0;

	
/**
 *	SetGuiGraphics
 *		Called from the Data namespace and the graphics that is set should be 
 *		released in the Data namespace also.
 */
void GuiData::setGuiGraphics(std::vector<SDLBitmap*> guiBitmapList)
{
	LOG("Set Gui Graphics...");
	
	menuBorder_Top=new GLBitmap(*guiBitmapList[0]);
	menuBorder_Bottom=new GLBitmap(*guiBitmapList[1]);
	menuBorder_Left=new GLBitmap(*guiBitmapList[2]);
	menuBorder_Right=new GLBitmap(*guiBitmapList[3]);
	
	menuBorder_Top_NoTrans=new GLBitmap(*guiBitmapList[4]);
	menuBorder_Bottom_NoTrans=new GLBitmap(*guiBitmapList[5]);
	menuBorder_Left_NoTrans=new GLBitmap(*guiBitmapList[6]);
	menuBorder_Right_NoTrans=new GLBitmap(*guiBitmapList[7]);
	
	menuBackground=new GLBitmap(*guiBitmapList[8]);
	
	guiData=new GLBitmap(*guiBitmapList[9]);
	
	menuBorder_Top->SEND_TO_GPU();
	menuBorder_Bottom->SEND_TO_GPU();
	menuBorder_Left->SEND_TO_GPU();
	menuBorder_Right->SEND_TO_GPU();
	
	menuBackground->SEND_TO_GPU_TYPE(TextureTypePattern);
	
	guiData->SEND_TO_GPU();
	
}

/**
 *
 */
void GuiData::freeGuiGraphics()
{
	LOG("Done GUI graphics...");
	
// #define  REMOVE(a) { if (a!=NULL) { delete a; a=NULL; } }
	
	REMOVE(menuBorder_Top);
	REMOVE(menuBorder_Bottom);
	REMOVE(menuBorder_Left);
	REMOVE(menuBorder_Right);
	
	REMOVE(menuBorder_Top_NoTrans);
	REMOVE(menuBorder_Bottom_NoTrans);
	REMOVE(menuBorder_Left_NoTrans);
	REMOVE(menuBorder_Right_NoTrans);
	
	REMOVE(menuBackground);
	
	REMOVE(guiData);
}

/**
 *
 */
void GuiData::setGuiFont(Font *font)
{
	guiFont=font;
}

/**
 *
 */
void GuiData::setGuiSmallFont(Font *smallFont)
{
	guiSmallFont=smallFont;
}

/**
 *
 */
void GuiData::setGuiBigFont(Font *bigFont)
{
	guiBigFont=bigFont;
}	
	
// end of namespace
// ----------------
}
