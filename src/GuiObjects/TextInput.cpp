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
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "GuiHandler.h"
#include "GuiData.h"
#include "GuiDraw.h"

#include "TextMarker.h"
#include "TextInput.h"

//#define PROMPT_ADD 10

/**
 *
 */
namespace GuiLib
{
	
const float TextInput::c_FlashDelay=0.3f;
	
int promptWidth=10;
	
const std::string promptString=">";
	
/*
Uint32 TextInput::ticks=0;
Uint32 TextInput::oldTicks=0;
*/
	
//bool TextInput::doubleHelper=false;

/**
 *
 */
TextInput::TextInput(const Rect &rect,std::string initText) : GuiObject(Rect(0,0,100,22)),
	m_Text(initText), m_Timer(0.0f), m_MarkStart(), m_MarkEnd(), m_CursorVisible(true), m_CursorPosition(),
	m_WaitForRelease(false), m_DoubleClickTicks(0), m_OldDoubleClickTicks(0), m_Shift(false), m_OldShift(false),
	m_DrawFrame(false), m_AllowNumbers(true), m_AllowSeparators(true), m_DrawPrompt(false), m_StoredInputLines(),
	m_CurrentStoredInputLine(0)
{
	m_Text=initText;
	
	Rect newRect=rect;
	
	Vector2d newSize(newRect.size.x,GuiData::guiSmallFont->getHeight()+7);
		
	
	newRect.size=newSize;
	
	setRect(newRect);
	
	promptWidth=GuiData::guiSmallFont->getDrawWidth(promptString);
	
	/*
	m_CursorPosition.pos=initText.length();
	
	m_CursorPosition.posPixels=GuiData::guiFont->GetStringWidth(initText);
	*/

	m_CursorPosition.setText(initText);	
	m_CursorPosition.setPosition((int)initText.length());
	
	
	m_CursorVisible=true;
	
	// No marking from the start.
	m_MarkStart.setText(initText);
	m_MarkStart.setPosition(-1);
	/*
	m_MarkStart.pos=2;
	m_MarkStart.posPixels=GuiData::guiFont->GetStringWidth(initText.substr(0,2));
	*/
	m_MarkEnd.setText(initText);
	m_MarkEnd.setPosition(-1);
	
	m_WaitForRelease=false;
	
	m_Timer=0.0f;
	
	m_OldDoubleClickTicks=0; 
	
	m_StoredInputLines=new std::vector<std::string>;
	//m_StoredInputLines->push_back("");
	
	m_CurrentStoredInputLine=0;

}

/**
 *
 */
TextInput::TextInput(const TextInput& source) : GuiObject(source),
	m_Text(""), m_Timer(0.0f), m_MarkStart(), m_MarkEnd(), m_CursorVisible(true), m_CursorPosition(),
	m_WaitForRelease(false), m_DoubleClickTicks(0), m_OldDoubleClickTicks(0), m_Shift(false), m_OldShift(false),
	m_DrawFrame(false), m_AllowNumbers(true), m_AllowSeparators(true), m_DrawPrompt(false), m_StoredInputLines(),
	m_CurrentStoredInputLine(0)
{
	m_Text=source.m_Text;
	
	Rect newRect=source.m_Rect;
	
	Vector2d newSize(newRect.size.x,GuiData::guiSmallFont->getHeight()+7);
		
	
	newRect.size=newSize;
	
	setRect(newRect);
	
	promptWidth=GuiData::guiSmallFont->getDrawWidth(promptString);
	
	/*
	m_CursorPosition.pos=initText.length();
	
	m_CursorPosition.posPixels=GuiData::guiFont->GetStringWidth(initText);
	*/

	/*
	m_CursorPosition.SetText(source.m_CursorPosition.GetText());	
	m_CursorPosition.SetPosition((int)source.m_CursorPosition.GetText().length());
	*/
	
	m_CursorPosition=source.m_CursorPosition;
	
	
	m_CursorVisible=source.m_CursorVisible;
	
	// No marking from the start.
	/*
	m_MarkStart.SetText(initText);
	m_MarkStart.SetPosition(-1);
	*/
	
	m_MarkStart=source.m_MarkStart;
	/*
	m_MarkStart.pos=2;
	m_MarkStart.posPixels=GuiData::guiFont->GetStringWidth(initText.substr(0,2));
	*/
	
	/*
	m_MarkEnd.SetText(source.m_MarkEnd.GetText());
	m_MarkEnd.SetPosition(source.m_MarkEnd.GetPosition());
	*/
	
	m_MarkEnd=source.m_MarkEnd;
	
	m_OldShift=source.m_OldShift;
	m_Shift=source.m_Shift;
	
	m_DrawFrame=source.m_DrawFrame;
	
	m_AllowNumbers=true;
	m_AllowSeparators=true;
	
	m_WaitForRelease=false;
	
	m_Timer=source.m_Timer;
	
	m_OldDoubleClickTicks=0; 
	
	m_DrawPrompt=false;
	
	m_StoredInputLines=new std::vector<std::string>;
	//m_StoredInputLines->push_back("");
	
	m_CurrentStoredInputLine=0;
	
}

/**
 *
 */
TextInput& TextInput::operator=(const TextInput& source)
{
	m_Text=source.m_Text;
	
	Rect newRect=source.m_Rect;
	
	Vector2d newSize(newRect.size.x,GuiData::guiSmallFont->getHeight()+7);
		
	
	newRect.size=newSize;
	
	setRect(newRect);
	
	promptWidth=GuiData::guiSmallFont->getDrawWidth(promptString);
	
	/*
	m_CursorPosition.pos=initText.length();
	
	m_CursorPosition.posPixels=GuiData::guiFont->GetStringWidth(initText);
	*/

	/*
	m_CursorPosition.SetText(source.m_CursorPosition.GetText());	
	m_CursorPosition.SetPosition((int)source.m_CursorPosition.GetText().length());
	*/
	
	m_CursorPosition=source.m_CursorPosition;
	
	
	m_CursorVisible=source.m_CursorVisible;
	
	// No marking from the start.
	/*
	m_MarkStart.SetText(initText);
	m_MarkStart.SetPosition(-1);
	*/
	
	m_MarkStart=source.m_MarkStart;
	/*
	m_MarkStart.pos=2;
	m_MarkStart.posPixels=GuiData::guiFont->GetStringWidth(initText.substr(0,2));
	*/
	
	/*
	m_MarkEnd.SetText(source.m_MarkEnd.GetText());
	m_MarkEnd.SetPosition(source.m_MarkEnd.GetPosition());
	*/
	
	m_MarkEnd=source.m_MarkEnd;
	
	m_OldShift=source.m_OldShift;
	m_Shift=source.m_Shift;
	
	m_DrawFrame=source.m_DrawFrame;
	
	m_AllowNumbers=true;
	m_AllowSeparators=true;
	
	m_WaitForRelease=false;
	
	m_Timer=source.m_Timer;
	
	m_OldDoubleClickTicks=0; 
	
	m_DrawPrompt=false;
	
	m_StoredInputLines=new std::vector<std::string>;
	//m_StoredInputLines->push_back("");
	
	m_CurrentStoredInputLine=0;

	return *this;
}

/**
 *
 */
TextInput::~TextInput()
{
	if (m_StoredInputLines!=NULL) {
		m_StoredInputLines->clear();
	
		delete m_StoredInputLines;
		m_StoredInputLines=NULL;
	}
}

/**
 *
 */
void TextInput::draw(const Vector2d &position,float opacity)
{
	Rect newRect=getRect()+position;
	
	/*
	if (m_MouseOver) {
		if (m_Fade<0.1f) m_Fade=0.1f;
	}
	*/
	
	Color col=Color(1.0f,1.0f,1.0f,opacity);
	
	if (m_DrawFrame) {
		GLPrimitives::rectFill(newRect,colorBlack);
		GLPrimitives::drawRect(newRect,col);
	}
	
	
	int promptAdd=0;
	if (m_DrawPrompt) promptAdd=promptWidth;
	


	if (m_MarkStart.getPosition()!=-1) {
		
		if (m_MarkStart!=m_MarkEnd) {
			
			//CheckSwap();
			
			int y1=newRect.position.y+4;
			int y2=newRect.size.y-5;
		
			int xpos=newRect.position.x;
			
			m_MarkStart.setText(m_Text);
			m_MarkEnd.setText(m_Text);
			
			int start=m_MarkStart.getPixels();
			int end=m_MarkEnd.getPixels();
			
			if (start>end) {
				int q=start;
				start=end;
				end=q;
			}
		
			
			Vector2d startPos(xpos+start-2+1+3+promptAdd,y1);
			Vector2d endPos(end-start+1/*+promptAdd*/,y2);
			
			GLPrimitives::rectFill(Rect(startPos,endPos),colorDarkRed);
		}
		
	}
	
	col=colorWhite;
	
	//GuiDraw::DrawStandardText(newRect.position+Vector2d(2,4),m_Text,col);
	
	

	if (m_DrawPrompt) 
		GuiData::guiSmallFont->draw(newRect.position+Vector2d(2,4),">",colorWhite);
	
	GuiData::guiSmallFont->draw(newRect.position+Vector2d(2+promptAdd,4),m_Text,colorLightGray);
		
	if (GuiHandler::instance()->getCurrentGuiObject()==this) {
		//col=colorRed;
		if (m_CursorVisible) drawCursor(newRect);
	}
	
	/*
	std::stringstream st;
	
	st << "Start:" << m_MarkStart.GetPosition() << " , End:" << m_MarkEnd.GetPosition();

	GuiData::guiFont->Draw(newRect.position+Vector2d(2,-20),st.str(),col);

	st.str("");
	
	st << "Cursor:" << m_CursorPosition.GetPosition() << " ,Len:" << (int)m_Text.length();
	GuiData::guiFont->Draw(newRect.position+Vector2d(2,-40),st.str(),col);

	st.str("");
	
	st << "Cursor pix:" << m_CursorPosition.GetPixels();
	GuiData::guiFont->Draw(newRect.position+Vector2d(2,-60),st.str(),col);
	*/
	

	//std::stringstream newString;

	
}

/**
 *
 */
void TextInput::drawCursor(const Rect &rect)
{
	int y1=rect.position.y+4;
	int y2=rect.position.y+rect.size.y-4;
	
	int xpos=rect.position.x+3;
	
	int promptAdd=0;
	if (m_DrawPrompt) promptAdd=promptWidth;
	
	GLPrimitives::line(Vector2d(xpos+m_CursorPosition.getPixels()+promptAdd,y1),
							 Vector2d(xpos+m_CursorPosition.getPixels()+promptAdd,y2),colorWhite,2);
}

/**
 *
 */
bool TextInput::moveWordRight()
{
	bool result=false;
	
	if (m_CursorPosition.getPosition()<(int)m_Text.length()) {
						
		// find position to go to
		
		int cursPos=m_CursorPosition.getPosition();
		char ch=m_Text.at(cursPos);
		int pos=0;
		
		
		bool done=false;
		
		do {
			ch=m_Text.at(cursPos+pos);
		
			//std::cout << "Letter:" << (char)ch << std::endl;
			pos++;
			
			if (cursPos+pos>=(int)m_Text.length()) done=true;
			if (isPunctuation(ch)) done=true;
			
		} while(!done);
		
		m_CursorPosition.setPosition(cursPos+pos);
		
		result=true;
	}
					
	return result;
}


/**
 *
 */
int TextInput::positionWordLeft()
{
	int result=-1;

	int cursPos=m_CursorPosition.getPosition()-1;
	
	//std::cout << "Curs pos:" << cursPos << std::endl;
	
	if (cursPos>0) {
	
		char ch=m_Text.at(cursPos);
		int pos=0;
		
		bool done=false;
		
		do {
			if (cursPos-pos>0) {
				ch=m_Text.at(cursPos-pos-1);
			}
			
			if (cursPos-pos<=0) done=true;
			if (isPunctuation(ch)) done=true;
			
			pos++;

			
		} while(!done);
		
		result=cursPos-pos+1;
	} else {
		result=0;
	}
	
	return result;
}

/**
 *
 */
bool TextInput::moveWordLeft()
{
	bool result=false;
	
	if (m_CursorPosition.getPosition()>0) {
	
		// find position to go to
		TextMarker savedPosition=m_CursorPosition;

		int newPos=positionWordLeft();
		
		if (newPos!=-1) m_CursorPosition.setPosition(newPos/*cursPos-pos+1*/);
		
		result=true;
	}
	
	return result;
}

/**
 *
 */
bool TextInput::left(KeyEvent &event)
{
	bool result=false;
				
	if (event.getCtrlPressed()) {
		result=moveWordLeft();
		
	} else {
		m_CursorPosition--;
		result=true;
	}
	
	if (!m_Shift) clearMarking();

	return result;
}

/**
 *
 */
bool TextInput::right(KeyEvent &event)
{
	bool result=false;
				
	if (event.getCtrlPressed()) {
		result=moveWordRight();
		
	} else {
		m_CursorPosition++;
		result=true;
	}
	
	if (!m_Shift) clearMarking();

	return result;
}

/**
 *
 */
bool TextInput::handleKeyboardEvent(KeyEvent &event)
{
	bool result=false;
	
	m_OldShift=m_Shift;
	
	int len=m_Text.length();
				
	
	//if (keysym->mod & KMOD_SHIFT) {
	if (event.getShiftPressed()) {
		m_Shift=true;
	} else {
		m_Shift=false;
	}
	
	if (m_Shift!=m_OldShift) {
		if (!haveMarker()) {
			m_CursorPosition.setText(m_Text);
			m_MarkStart=m_CursorPosition;
		}
	}
		
	if (GuiHandler::instance()->getCurrentGuiObject()==this) {
		/*
		if (key==SDL_KEYUP) {
			
			switch(keysym->sym) {
			case SDLK_RSHIFT:
			case SDLK_LSHIFT:
			{
				std::cout << "release..." << std::endl;
				m_Shift=!m_Shift;
				break;
			}
			default:
				break;
			};

		}
		*/
		
		if (event.getType()==KeyEventPressed) { //key==SDL_KEYDOWN) {
			
			switch(event.getValue()) {
			// ------------------------------------------------------------------------------
			case Key::Delete:
			{
				if (m_MarkStart==m_MarkEnd) clearMarking();
				
				int len=m_Text.length();
				int pos=m_CursorPosition.getPosition();
				
				if (haveMarker()) {
					
					checkSwap();
					
					int start=m_MarkStart.getPosition();
					int end=m_MarkEnd.getPosition();

					//printf("Havemarker! start:%d end:%d \n",start,end);
					
					
					std::stringstream newst;
					
					//int marked=end-start;
					
					newst.str("");
					newst << m_Text.substr(0,start) << /*st.str() <<*/ m_Text.substr(end/*-end-marked*/);
					
					m_Text=newst.str();
					
					m_MarkStart.setText(m_Text);
					//m_MarkStart.SetPixelPos(GuiData::guiSmallFont->GetStringWidth(m_Text.substr(0,start)));
					m_MarkStart.setPosition(start);
				
					m_CursorPosition.setText(m_Text);
					m_CursorPosition.setPosition(m_MarkStart.getPosition());
					

					clearMarking();
					
					if (event.getShiftPressed()) { //keysym->mod & KMOD_SHIFT) {
					//if (!m_OldShift) {
						m_Shift=true;
						//}
					} else {
						m_Shift=false;
					}
				
				
					
				} else {
				
					if ((len!=0) && (m_CursorPosition.getPosition()<len)) {
					
						std::string newText=m_Text.substr(0,pos)+m_Text.substr(pos+1,len-(pos)-1);
						m_Text=newText;
						m_CursorPosition.setText(m_Text);
					}
				}
				result=true;
				break;
			}
			// ------------------------------------------------------------------------------
			case Key::Backspace:
			{
				
				if (m_MarkStart==m_MarkEnd) {
					clearMarking();
				}
				
				int pos=m_CursorPosition.getPosition();
				
				if (haveMarker()) {
					
					checkSwap();
					
					int start=m_MarkStart.getPosition();
					int end=m_MarkEnd.getPosition();
					
					std::stringstream newst;
					
					//int marked=end-start;
					
					newst.str("");
					
					/*
					std::stringstream stlog;
					stlog << "start:" << start << "  ,end:" << end;
					STLOG(stlog);
					stlog << "text_length:" << len;
					STLOG(stlog);
					*/
					
					//newst << m_Text.substr(0,start) << /*st.str() <<*/ m_Text.substr(end,m_Text.length()/*-end-marked*/);
					newst << m_Text.substr(0,start) << /*st.str() <<*/ m_Text.substr(end/*-end-marked*/);
					
					m_Text=newst.str();
					
					/*
					m_MarkStart.SetText(m_Text);
					m_MarkStart.SetPixelPos(GuiData::guiFont->GetStringWidth(m_Text.substr(0,start)));
					*/
				
					m_CursorPosition=m_MarkStart;
					m_CursorPosition.setText(m_Text);
	
					//STLOG(newst);
					clearMarking();
					
				} else {
					
					if ((len!=0) && (m_CursorPosition.getPosition()>0)) {
						
						//DLOG("m_CursorPosition",m_CursorPosition.GetPosition());
						
						m_CursorPosition--;
						std::string newText=m_Text.substr(0,pos-1)+m_Text.substr(pos,len-pos);
						m_Text=newText;
						m_CursorPosition.setText(m_Text);
						
						clearMarking();
					}
				}
			
				result=true;
				break;
			}
			// ------------------------------------------------------------------------------
			case Key::Right:
			{
				right(event);
				result=true;
				break;
			}
			// ------------------------------------------------------------------------------
			case Key::Left:
			{
				left(event);
				result=true;
				break;
			}
			// ------------------------------------------------------------------------------
			case Key::Home:
			{
				//m_MarkActive=false;
				TextMarker saved=m_CursorPosition;
				
				m_CursorPosition.setText(m_Text);
				
				//m_CursorPosition.SetPixelPos(0);
				m_CursorPosition.setPosition(0);
				
				
				if (!m_Shift) {
					clearMarking();
				}
					
				/*
					
					if (m_MarkEnd.GetPosition()==-1) {
						m_MarkEnd=saved;
					}
					
					m_MarkStart=m_CursorPosition;
					
					//m_MarkActive=true;
				} else {
					ClearMarking();
				}
				*/
				
				result=true;
				break;
			}
			// ------------------------------------------------------------------------------
			case Key::End:
			{
				TextMarker saved=m_CursorPosition;
				
				//m_CursorPosition.SetPixelPos(GuiData::guiFont->GetStringWidth(m_Text));
				
				//std::cout << "Text Length:" << (int)m_Text.length() << std::endl;
				
				//m_CursorPosition.SetPixelPos(GuiData::guiSmallFont->GetStringWidth(m_Text));
				
				m_CursorPosition.setText(m_Text);
				
				m_CursorPosition.setPosition((int)m_Text.length());
				
				
				if (!m_Shift) {
					clearMarking();
				}
					
				result=true;
				break;
			}

			// ------------------------------------------------------------------------------
			case Key::Tab:
			{
				//m_MarkActive=false;
				clearMarking();
				result=true;
				break;
			}		
			// ------------------------------------------------------------------------------
			case Key::Escape:
			{
				
				if (m_MarkStart.getPosition()==m_MarkEnd.getPosition()) {
					clearMarking();
				}
				
				// We have a marking?
				if (m_MarkStart.getPosition()!=-1) {
					
					// Remove it, and do nothing else
					clearMarking();
					
					// Finished with keyboard handling.
					result=true;
				} else {
					// don't handle this one here, leave it so it is grabbed
					// by the panel handler, which makes it close alerts and dialogs.
					result=false;
				}
				break;
			}
			//case SDLK_KP_ENTER:
			case Key::Enter:
				{
					if (getText()!="") {
						
						int listSize=(int)m_StoredInputLines->size();
						
						
						std::string textToCheck="";
						if (listSize!=0) {
							textToCheck=m_StoredInputLines->at(listSize-1);
						}
						
						// only store if it is different from the last stored line
						if (textToCheck!=getText()) {
						
							m_StoredInputLines->push_back(getText());
							m_CurrentStoredInputLine++;
						}
						GuiHandler::instance()->eventEnterConsoleCommand->pushEvent();
					}
					result=true;
				}
				break;
			case Key::Up:
				{
					getPreviousInputLine();
					
					// Check if we are positioned outside the stringstream
					if ((int)m_CursorPosition.getPosition()>(int)m_Text.length()) {
						m_CursorPosition.setPosition((int)m_Text.length());
					}
					
					result=true;
				}
				break;
			case Key::Down:
				{
					getNextInputLine();
				
					if ((int)m_CursorPosition.getPosition()>(int)m_Text.length()) {
						m_CursorPosition.setPosition((int)m_Text.length());
					}

					result=true;
				}
				break;
			};

			
			// ------------------------------------------------------------------------------
			if (!result) {
				// Check if we have a ASCII value:
				//if ((keysym->unicode & 0xff80)==0) {
				if ((event.getUnicode() & 0xff80)==0) {
					char ch=event.getUnicode() & 0x7f;
					
					std::stringstream st;
					st.str("");
					st << ch;
					
					
					if (canAddCharacter(st.str())) {
						// Do we have a marker?
						
						if (haveMarker()) {
							
							int start=m_MarkStart.getPosition();
							int end=m_MarkEnd.getPosition();
							int marked=end-start;
							
							if (marked<0) marked=-marked;
							
							std::stringstream newst;
							newst.str("");
							
							if (start==-1) start=m_CursorPosition.getPosition();

							/*
							std::stringstream stlog;
							stlog << "start:" << start << "  ,end:" << end;
							STLOG(stlog);
							stlog << "text_length:" << len;
							STLOG(stlog);
							*/
							
							newst << m_Text.substr(0,start) << st.str() << m_Text.substr(end/*,m_Text.length()*//*-end-marked*/);
							m_Text=newst.str();
														
							m_MarkStart.setText(m_Text);
							m_CursorPosition.setText(m_Text);
							
							//m_MarkStart.SetPixelPos(GuiData::guiSmallFont->GetStringWidth(m_Text.substr(0,start)));
							m_MarkStart.setPosition(start);
							
							if (m_MarkStart.getPosition()!=-1) m_CursorPosition=m_MarkStart;
							m_CursorPosition++;
			
							//STLOG(newst);
							
						} else {
							addCharacter(st.str());
						}
						clearMarking();
						result=true;
					
					}
					
				}
			}
		}
	}
	
	if (m_Shift) m_MarkEnd=m_CursorPosition;
	
	//CheckSwap();
	
	return result;
}

/**
 *
 */
void TextInput::clearMarking()
{
	m_MarkStart.setPosition(-1);
	m_MarkEnd.setPosition(-1);
	
	//m_MarkActive=false;
	
}

/**
 *	returns true if a character was added
 */
void TextInput::addCharacter(std::string str)
{
	//bool result=false;
	// check if it is an allowed character...

	//m_Text+=ch;
	
	int pos=m_CursorPosition.getPosition();
	
	/*
	std::stringstream st;
	st << "Pos:" << pos;
	STLOG(st);
	*/
	
	if (pos!=0) {
		if (pos==(int)m_Text.length()) {
			//LOG("pos=length()");
			m_Text+=str;
		} else {
			//printf("Pos:%d, Length:%d\n",pos,(int)m_Text.length());
			m_Text.insert(pos,(std::string)(str));
		}
	} else {
		m_Text=str+m_Text;
	}
	
	/*
	std::stringstream st;
	st.str("");
	st << str;
	*/
	
	m_CursorPosition.setText(m_Text);
	m_CursorPosition++;
	
	m_MarkStart.setText(m_Text);
	m_MarkEnd.setText(m_Text);
	
	//result=true;
	
	/*
	m_CursorPosition.posPixels+=GuiData::guiFont->GetStringWidth(st.str());
	m_CursorPosition.pos++;
	*/

	//m_CursorPositionPixels+=GuiData::guiFont->GetStringWidth(st.str());
	//m_CursorPosition++;
	
	//return result;
}

/**
 *
 */
bool TextInput::canAddCharacter(std::string str)
{
	bool result=false;
	
	std::string validCharacters=
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
	
	if (m_AllowNumbers) validCharacters+="0123456789";
	
	if (m_AllowSeparators) validCharacters+="().,:;-+-*/\\_\"{}[]='!?";
	
	std::stringstream st;
	st.str("");
	st << str;
	
	int q=(int)validCharacters.find(st.str());
	
	//int width=GuiData::guiSmallFont->GetStringWidth(st.str());
	
	if (q!=-1) result=true;
	
	return result;
}

/**
 *
 */
bool TextInput::onLeftMouseButtonPressed(const Vector2d& pos)
{
	bool handled=false;
	if (m_MouseOver) {
		setCursorActive();
						
		//handled=true;
		
		int x=pos.x-getPosition().x/*-promptAdd*/;
		
		int q=getPositionInText(x);
		
		m_CursorPosition.setPosition(q);
		
		m_MarkEnd.setPosition(q); //=m_CursorPosition;
		
		//mouse->SetWaitForZero();
		//m_WaitForRelease=true;
		
		handled=true;
	}
	
	return handled;
}

/**
 *
 */
void TextInput::setCursorActive()
{
	GuiHandler::instance()->setCurrentGuiObject(this);
	m_CursorPosition.setPosition(0);
	
}

/**
 *
 */
void TextInput::update()
{
	//m_Timer+=Timer::diffTime;
	m_Timer+=Timer::instance()->getDeltaTime();
	
	// We want the timer to stay lower that c_FlashDelay
	if (m_Timer>c_FlashDelay) {
		
		/*
		do {
			m_Timer-=c_FlashDelay;
		} while(m_Timer>c_FlashDelay);
		*/
		
		m_Timer=0.0f;
		
		
		m_CursorVisible=!m_CursorVisible;
	}
	
	/*
	if (m_MarkEnd==m_MarkStart) {
		ClearMarking();
	}
	*/
	
	/*
	if (m_MarkEnd<m_MarkStart) {
		
		TextMarker buf=m_MarkStart;
		m_MarkStart=m_MarkEnd;
		m_MarkEnd=buf;
		
	}
	*/
}

/**
 *
 */
void TextInput::lostFocus()
{
	clearMarking();
}

/**
 *
 */
int TextInput::getPositionInText(int pixelPos)
{
	int result=0;
	int q=2;		// text distance from left edge
	
	bool done=false;
	
	
		
	int promptAdd=0;
	if (m_DrawPrompt) promptAdd=promptWidth;
	
	
	// +1 eftersom man ska kunna markera så att cursorn är efter texten också
	for (int co=0;co<(int)m_Text.length()+1;co++) {
		
		std::string tempString=m_Text.substr(0,co);
		//q=GuiData::guiSmallFont->GetStringWidth(tempString);
		q=GuiData::guiSmallFont->getDrawWidth(tempString);
		
		if (pixelPos>q+promptAdd) {
			result=co;
			done=true;
		}
	}
	
	if (!done) {
		result=(int)m_Text.length();
	}
	
	return result;
}

/**
 *
 */
bool TextInput::isPunctuation(char ch)
{
	std::string validPunctuation="., ()'";
	
	std::stringstream st;
	st.str("");
	st << ch;
	
	
	int q=(int)validPunctuation.find(st.str());
	
	return q!=-1;
}

/**
 *
 */
bool TextInput::haveMarker()
{
	
	int start=m_MarkStart.getPosition();
	int end=m_MarkEnd.getPosition();
	
	if ((start!=-1) && (end!=-1)) {
		checkSwap();
				
		return true;
	}
	
	return false;
}

/**
 *
 */
void TextInput::setDrawFrame(bool draw)
{
	m_DrawFrame=draw;
}

/**
 *
 */
std::string TextInput::getText()
{
	return m_Text;
}

/**
 *
 */
void TextInput::setText(std::string text)
{
	m_Text=text;
	clearMarking();
}

/**
 *
 */
void TextInput::clear()
{
	setText("");
	m_CursorPosition.setPosition(0);
}

/**
 *
 */
void TextInput::gainFocus()
{
	int listSize=(int)m_StoredInputLines->size();
	m_CurrentStoredInputLine=listSize;
	
	LOG("TextInput GainFocus()");
}


/**
 *
 */
void TextInput::checkSwap()
{
	if (m_MarkStart.getPosition()>m_MarkEnd.getPosition()) {
		TextMarker buf=m_MarkEnd;
		m_MarkEnd=m_MarkStart;
		m_MarkStart=buf;
	}
}

/**
 *
 */
void TextInput::setDrawPrompt(bool drawPrompt)
{
	m_DrawPrompt=drawPrompt;
}

/**
 *
 */
void TextInput::getNextInputLine()
{
	int listSize=(int)m_StoredInputLines->size();
		
	if (listSize!=0) {
		m_CurrentStoredInputLine++;
		
		// Check if we are at line listSize+1;
		// 
		// for example list with size 3:
		//
		// 0
		// 1
		// 2
		//		empty line (current input)
		//    <- here
		//
		//
		if (m_CurrentStoredInputLine>listSize) {
			m_CurrentStoredInputLine=0;
		}
		
		if (m_CurrentStoredInputLine==listSize) {
			setText("");
		} else {
			
			setText(m_StoredInputLines->at(m_CurrentStoredInputLine));
		}
		
	}
}

/**
 *
 */
void TextInput::getPreviousInputLine()
{
	int listSize=(int)m_StoredInputLines->size();
					
	if (listSize!=0) {
		m_CurrentStoredInputLine--;
		
		// if going over the top, set position at one position after last line 
		// (represents the current empty line)
		if (m_CurrentStoredInputLine<0) m_CurrentStoredInputLine=listSize;
		
		if (m_CurrentStoredInputLine==listSize) {
			
			setText("");
		
		} else {
		
			setText(m_StoredInputLines->at(m_CurrentStoredInputLine));
		}
	}
}

// end of namespace
// ----------------
};
