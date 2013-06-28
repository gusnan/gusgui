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

Bitmap *GuiData::menuBorder_Top=0;
Bitmap *GuiData::menuBorder_Bottom=0;
Bitmap *GuiData::menuBorder_Left=0;
Bitmap *GuiData::menuBorder_Right=0;

Bitmap *GuiData::menuBorder_Top_NoTrans=0;
Bitmap *GuiData::menuBorder_Bottom_NoTrans=0;
Bitmap *GuiData::menuBorder_Left_NoTrans=0;
Bitmap *GuiData::menuBorder_Right_NoTrans=0;
	
Bitmap *GuiData::menuBackground=0;
	
Bitmap *GuiData::guiData=0;

GraphicsLib::Font *GuiData::guiFont=0;
GraphicsLib::Font *GuiData::guiSmallFont=0;
GraphicsLib::Font* GuiData::guiBigFont=0;

	
/**
 *	SetGuiGraphics
 *		Called from the Data namespace and the graphics that is set should be 
 *		released in the Data namespace also.
 */
void GuiData::setGuiGraphics(std::vector<Bitmap*> guiBitmapList)
{
	LOG("Set Gui Graphics...");
	
	menuBorder_Top=guiBitmapList[0]->makeCopy();
	menuBorder_Bottom=guiBitmapList[1]->makeCopy();
	menuBorder_Left=guiBitmapList[2]->makeCopy();
	menuBorder_Right=guiBitmapList[3]->makeCopy();
	
	menuBorder_Top_NoTrans=guiBitmapList[4]->makeCopy();
	menuBorder_Bottom_NoTrans=guiBitmapList[5]->makeCopy();
	menuBorder_Left_NoTrans=guiBitmapList[6]->makeCopy();
	menuBorder_Right_NoTrans=guiBitmapList[7]->makeCopy();
	
	menuBackground=guiBitmapList[8]->makeCopy();
	
	guiData=guiBitmapList[9]->makeCopy();
	
	/*
	menuBorder_Top->SEND_TO_GPU();
	menuBorder_Bottom->SEND_TO_GPU();
	menuBorder_Left->SEND_TO_GPU();
	menuBorder_Right->SEND_TO_GPU();
	
	menuBackground->SEND_TO_GPU_TYPE(TextureTypePattern);
	
	guiData->SEND_TO_GPU();
	*/
	
}

/**
 *
 */
void GuiData::freeGuiGraphics()
{
	LOG("Done GUI graphics...");
#ifndef REMOVE
#define  REMOVE(a) { if (a!=NULL) { delete a; a=NULL; } }
#endif
	
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
void GuiData::setGuiFont(GraphicsLib::Font *font)
{
	guiFont=font;
}

/**
 *
 */
void GuiData::setGuiSmallFont(GraphicsLib::Font *smallFont)
{
	guiSmallFont=smallFont;
}

/**
 *
 */
void GuiData::setGuiBigFont(GraphicsLib::Font *bigFont)
{
	guiBigFont=bigFont;
}	
	
// end of namespace
// ----------------
}
