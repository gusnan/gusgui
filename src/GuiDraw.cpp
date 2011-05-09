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
#include <vector>
#include <list>
#include <string>
#include <sstream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::LogLib;
using namespace Gus::EventLib;

#include "GuiObjects/GuiObject.h"

#include "GuiData.h"
#include "GuiHandler.h"
#include "GuiDraw.h"

#define REMOVE(a) { if (a!=NULL) { delete a; a=NULL; } }
	
/**
 *
 */
namespace GuiLib
{

/**
 *
 */
void GuiDraw::drawGuiRect(Rect rect,bool drawTransparentFrame,float opacity)
{
	Vector2d pos=rect.position;
	Vector2d size=rect.size;
	
	int x=rect.position.x;
	int y=rect.position.y;
	
	int xs=rect.size.x;
	int ys=rect.size.y;
	
	int transAdd=0;

	GraphicsHandler *graphicsHandler=GraphicsHandler::instance();
	
	if (!drawTransparentFrame) transAdd+=16;
	
	//GuiData::menuBorder_TopLeft->Blit(pos+Vector2d(-8,-8),opacity);
	GuiData::guiData->blit(Rect(40+transAdd,0,8,8),pos+Vector2d(-8,-8),opacity);
	
	if (xs<=128) {
		graphicsHandler->setClipRect(Rect(pos.x,pos.y-8,xs,8));
		if (!drawTransparentFrame) {
			GuiData::menuBorder_Top_NoTrans->blit(pos+Vector2d(0,-8),opacity);
		} else {
			GuiData::menuBorder_Top->blit(pos+Vector2d(0,-8),opacity);
		}
		graphicsHandler->noClip();
		
	} else {
		GuiData::menuBorder_Top->drawPattern(Rect(pos+Vector2d(0,-8),Vector2d(xs,8)),opacity);
	}
	
	//GuiData::menuBorder_TopRight->Blit(pos+Vector2d(xs,-8),opacity);
	GuiData::guiData->blit(Rect(48+transAdd,0,8,8),pos+Vector2d(xs,-8),opacity);
	
	if (ys<120) {
		graphicsHandler->setClipRect(Rect(pos.x-8,pos.y,8,ys));
		if (!drawTransparentFrame) {
			GuiData::menuBorder_Left_NoTrans->blit(pos+Vector2d(-8,0),opacity);
		} else {
			GuiData::menuBorder_Left->blit(pos+Vector2d(-8,0),opacity);
		}
		//GuiData::menuBorder_Left->DrawPattern(Rect(pos.x,pos.y,5,ys));
		graphicsHandler->noClip();
	} else {
	
		GuiData::menuBorder_Left->drawPattern(Rect(pos+Vector2d(-8,0),Vector2d(8,ys)),opacity);
	}
	
	//GuiData::menuBorder_BottomLeft->Blit(pos+Vector2d(-8,ys),opacity);
	GuiData::guiData->blit(Rect(40+transAdd,8,8,8),pos+Vector2d(-8,ys),opacity);
	
	
	if (xs<=116) {
		GraphicsHandler::instance()->setClipRect(Rect(pos.x,y+ys,xs,8));
		if (!drawTransparentFrame) {
			GuiData::menuBorder_Bottom_NoTrans->blit(pos+Vector2d(0,ys),opacity);
		} else {
			GuiData::menuBorder_Bottom->blit(pos+Vector2d(0,ys),opacity);
		}
		graphicsHandler->noClip();
	} else {
	
		GuiData::menuBorder_Bottom->drawPattern(Rect(pos+Vector2d(0,ys),Vector2d(xs,8)),opacity);
	}
	
	if (ys<120) {
		graphicsHandler->setClipRect(Rect(x+xs,pos.y,8,ys));
		if (!drawTransparentFrame) {
			GuiData::menuBorder_Right_NoTrans->blit(pos+Vector2d(xs,0),opacity);
		} else {
			GuiData::menuBorder_Right->blit(pos+Vector2d(xs,0),opacity);
		}
		graphicsHandler->noClip();
	} else {
	
		GuiData::menuBorder_Right->drawPattern(Rect(pos+Vector2d(xs,0),Vector2d(8,ys)),opacity);
	}
	
	GuiData::guiData->blit(Rect(48+transAdd,8,8,8),Vector2d(x+xs,y+ys),opacity);

}


#ifndef _NO_FRAME_BUFFER_
/**
 *
 */
FrameBuffer *GuiDraw::makeTextButtonStandard(std::string text)
{
	FrameBuffer *result=0;
	
	GLBitmap *textBitmap=GuiDraw::DrawTextCentered(text);
	
	// Fix FrameBuffers instead.
	
	Vector2d size=GuiData::buttonNormal->GetSize();
	Rect fullRect(Vector2d(0,0),size);
	
	result=new FrameBuffer(size);
	result->SetRenderToThis();
	
	glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
	
	GLPrimitives::RectFill(fullRect,Color(0.0,0.0,0.0,0.0));
	GuiData::buttonNormal->Blit(Vector2d(0,0));

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	textBitmap->BlitCenterColor(fullRect+Vector2d(2,2),colorBlack,1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	textBitmap->BlitCenter(fullRect,1.0);
	
	
	result->DoneRendering();
	
	GLERROR
	
	REMOVE(textBitmap);
	
	

	return result;
}

/**
 *
 */
FrameBuffer *GuiDraw::makeTextButtonHover(std::string text)
{
	FrameBuffer *result=0;
	
	GLBitmap *textBitmap=GuiDraw::DrawTextCentered(text);
	
	// Fix FrameBuffers instead.
	
	Vector2d size=GuiData::buttonNormal->GetSize();
	Rect fullRect(Vector2d(0,0),size);
	
	result=new FrameBuffer(size);
	result->SetRenderToThis();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	GLPrimitives::RectFill(fullRect,Color(0.0,0.0,0.0,0.0));
	GuiData::buttonHover->Blit(Vector2d(0,0));

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	textBitmap->BlitCenterColor(fullRect+Vector2d(2,2),colorBlack,1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	textBitmap->BlitCenter(fullRect,1.0);
	
	result->DoneRendering();
		
	REMOVE(textBitmap);

	return result;
}

/**
 *
 */
FrameBuffer *GuiDraw::makeTextButtonPressed(std::string text)
{
	FrameBuffer *result=0;
	
	GLBitmap *textBitmap=GuiDraw::DrawTextCentered(text);
	
	// Fix FrameBuffers instead.
	
	Vector2d size=GuiData::buttonNormal->GetSize();
	Rect fullRect(Vector2d(0,0),size);
	
	result=new FrameBuffer(size);
	result->SetRenderToThis();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	GLPrimitives::RectFill(fullRect,Color(0.0,0.0,0.0,0.0));
	GuiData::buttonPressed->Blit(Vector2d(0,0));
		
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	textBitmap->BlitCenterColor(Rect(Vector2d(1,-1),size)+Vector2d(2,2),colorBlack,1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	textBitmap->BlitCenter(Rect(Vector2d(1,-1),size),1.0);
	
	result->DoneRendering();
		
	REMOVE(textBitmap);

	return result;
}
#endif


/**
 *
 */
void GuiDraw::splitString(std::string instring,std::string& text,std::string& shortcut)
{
	text=instring;
	shortcut="";
	
	int startPar=-1;
	
	int len=(int)instring.length();
	
	for (int co=0;co<len;co++) {
		if (instring[co]=='(') {
			startPar=co;
			//LOG("Contains Paranthesis...");
		}
	}
	
	int posEndPar=-1;
	
	for (int co=0;co<(int)instring.length();co++) {
		if (instring[co]==')') {
			posEndPar=co; 
		}
	}
	
	if (posEndPar!=-1) {
		if (startPar!=-1) {
			text=instring.substr(0,startPar);
			shortcut=instring.substr(startPar+1,len-(startPar+2));
		}
	}
}



/**
 *
 */
GLBitmap *GuiDraw::drawTextCentered(std::string intext)
{
	std::string text,shortcut;
	
	splitString(intext,text,shortcut);
	
	if (!GuiHandler::instance()->getShowKeyboardShortcuts()) shortcut="";
	
	std::string fullText;
	std::stringstream st;
	if (shortcut!="") {
		st << text << "(" << shortcut << ")";
	} else {
		st << text;
	}
	
	fullText=st.str();
	
	st.str("");
	
	// Calculate the size of the bitmap
	
	Vector2d size;
	size.y=GuiData::guiFont->getHeight();
	size.x=GuiData::guiFont->getStringWidth(text);
	
	if (shortcut!="") {
		size.x+=GuiData::guiFont->getStringWidth("()");
		size.x+=GuiData::guiSmallFont->getStringWidth(shortcut);
	}

	Bitmap *tempBackground=new Bitmap(size/*GuiData::guiFont->GetStringSize(fullText)*/);
	
	tempBackground->clearToColor(Color(0.0,0.0,0.0,0.0));

	int x=0;
	Bitmap *tempText=GuiData::guiFont->renderText(text,colorWhite);
	tempText->blit(tempBackground,Vector2d(0,0));
	
	if (shortcut!="") {
		
		x+=GuiData::guiFont->getStringSize(text).x;
		
		REMOVE(tempText);
		tempText=GuiData::guiFont->renderText("(",colorWhite);
		tempText->blit(tempBackground,Vector2d(x,0));
		
		x+=GuiData::guiFont->getStringSize("(").x;

		REMOVE(tempText);
		tempText=GuiData::guiSmallFont->renderText(shortcut,colorYellow);
		tempText->blit(tempBackground,Vector2d(x,0));

		x+=GuiData::guiSmallFont->getStringSize(shortcut).x;

		REMOVE(tempText);
		tempText=GuiData::guiFont->renderText(")",colorWhite);
		tempText->blit(tempBackground,Vector2d(x,0));
		
	}

	/*
	REMOVE(tempText);
	
	tempText=GuiHandler::guiFont->RenderText(text,colorWhite);
	tempText->Blit(tempBackground,Vector2d(0,0));
	*/
	GLBitmap *textBitmap=new GLBitmap(*tempBackground);
	textBitmap->SEND_TO_GPU();
		
	REMOVE(tempText);
	REMOVE(tempBackground);
	
	//m_Text=text;
	return textBitmap;
	
}

#ifndef _NO_FRAME_BUFFER_
/**
 *
 */
FrameBuffer *GuiDraw::makeStandardButton(Vector2d size,GLBitmap *icon)
{
	FrameBuffer *result=0;
	
	Rect fullRect(Vector2d(0,0),size);
	
	result=new FrameBuffer(size);
	result->SetRenderToThis();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DrawStandardButton(fullRect,icon);
	
	result->DoneRendering();

	return result;	
}
#endif

/**
 *
 */
void GuiDraw::drawStandardButton(Rect rect,GLBitmap *icon) 
{
	Vector2d size=rect.size;
	Vector2d pos=rect.position;
	GLPrimitives::rectFill(rect,makeColorInt(20,69,112));
	//GLPrimitives::RectFill(fullRect,Color(0.014f,0.041,0.26f,1.0));
	//GLPrimitives::RectFill(fullRect,Color(0.03f,0.129f,0.211f,1.0));
	//GLPrimitives::RectFill(fullRect,Color(0.0f,0.3f,1.0f,1.0));
	
	Rect newRect=Rect(pos+Vector2d(1,1),size-Vector2d(2,2));
	Rect thirdRect=Rect(pos+Vector2d(2,2),size-Vector2d(4,4));
	Rect fourthRect=Rect(pos+Vector2d(3,3),size-Vector2d(6,6));
	
	GLPrimitives::niceRect(rect,0.5f,0.4f);
	GLPrimitives::niceRect(newRect,0.35f,0.3f);
	GLPrimitives::niceRect(thirdRect,0.2f,0.2f);
	GLPrimitives::niceRect(fourthRect,0.1f,0.1f);
	
	Color col1=Color(0.0f,0.0f,0.0f,0.7f);
	Color col2=Color(1.0f,1.0f,1.0f,0.1f);

	GLPrimitives::shadeRect(Rect(pos/*Vector2d(0,0)*/,size/*-Vector2d(8,8)*/),col1,col2);
	
	if (icon) {
		
		icon->blitCenter(rect);
	}

}

#ifndef _NO_FRAME_BUFFER_
/**
 *
 */
FrameBuffer *GuiDraw::makePressedButton(Vector2d size,GLBitmap *icon)
{
	FrameBuffer *result=0;
	
	Rect fullRect(Vector2d(0,0),size);
	
	result=new FrameBuffer(size);
	result->SetRenderToThis();
	
	glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
	
	DrawPressedButton(fullRect,icon);
	
	result->DoneRendering();

	return result;	
}
#endif

/**
 *
 */
void GuiDraw::drawPressedButton(Rect rect,GLBitmap *icon)
{
	Vector2d pos=rect.position;
	Vector2d size=rect.size;
	
	// 10,33,54
	// 19,72,118
	GLPrimitives::rectFill(rect,makeColorInt(20,69,112));
	//GLPrimitives::RectFill(fullRect,Color(0.034f,0.211,0.56f,1.0));
	//GLPrimitives::RectFill(fullRect,Color(0.03f,0.129f,0.211f,1.0));
	//GLPrimitives::RectFill(fullRect,Color(0.0f,0.2f,0.7f,1.0));
	
	Rect newRect=Rect(pos+Vector2d(1,1),size-Vector2d(2,2));
	Rect thirdRect=Rect(pos+Vector2d(2,2),size-Vector2d(4,4));
	Rect fourthRect=Rect(pos+Vector2d(3,3),size-Vector2d(6,6));
	
	GLPrimitives::niceRect(rect,0.5f,0.4f,true);
	GLPrimitives::niceRect(newRect,0.35f,0.3f,true);
	GLPrimitives::niceRect(thirdRect,0.2f,0.2f,true);
	GLPrimitives::niceRect(fourthRect,0.1f,0.1f,true);
	
	Color col1=Color(0.0f,0.0f,0.0f,0.7f);
	Color col2=Color(1.0f,1.0f,1.0f,0.1f);

	GLPrimitives::shadeRect(Rect(pos,size/*-Vector2d(8,8)*/),col1,col2);
	
	if (icon) {
	
		int centerX=size.x/2;
		int centerY=size.y/2;
	
		Vector2d newPos=pos+Vector2d(centerX-icon->getSize().x/2+1,centerY-icon->getSize().y/2+1);
			
		icon->blit(newPos);
	}
}

/**
 *
 */
void GuiDraw::drawNiceTextSmall(Vector2d pos,std::string st,Color col,float opacity)
{
	Color black=Color(0.0f,0.0f,0.0f,(GLfloat)opacity);
	GuiData::guiSmallFont->draw(pos+Vector2d(2,2),st,black);
	
	Color textCol=col;
	
	textCol.m_Alpha=opacity;
	GuiData::guiSmallFont->draw(pos,st,textCol);
}

/**
 *
 */
void GuiDraw::drawNiceText(Vector2d pos,std::string st,Color col,float opacity)
{
	Color black=Color(0.0f,0.0f,0.0f,(GLfloat)opacity);
	GuiData::guiSmallFont->draw(pos+Vector2d(2,2),st,black);
	
	Color textCol=col;
	
	textCol.m_Alpha=opacity;
	GuiData::guiFont->draw(pos,st,textCol);
}

/**
 *
 */
void GuiDraw::drawNiceTextSmallCenter(Vector2d pos,std::string st,Color col,float opacity)
{
	int s=GuiData::guiFont->getStringWidth(st);
	
	drawNiceTextSmall(pos-Vector2d(s/2,0),st,col,opacity);
}

/**
 *
 */
void GuiDraw::drawNiceTextCenter(Vector2d pos,std::string st,Color col,float opacity)
{
	int s=GuiData::guiFont->getStringWidth(st);
	
	drawNiceText(pos-Vector2d(s/2,0),st,col,opacity);

}



// end of namespace
// ----------------
}
