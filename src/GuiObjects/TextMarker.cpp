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
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::LogLib;


#include "GuiData.h"

#include "TextMarker.h"

/**
 *
 */
namespace GuiLib
{
	
/**
 *
 */
TextMarker::TextMarker() : m_Text(""), m_PosPixels(0), m_Pos(0)
{
	setPosition(0);
}


/**
 *
 */
TextMarker::TextMarker(const std::string &text) : m_PosPixels(0), m_Pos(0), m_Text(text)
{
	
}

/**
 *
 */
TextMarker::~TextMarker()
{
}

/**
 *
 */
void TextMarker::setPosition(int pos)
{
	m_Pos=pos;
	
	//GuiData::guiSmallFont
	//GuiData::guiSmallFont
	/*
	std::stringstream st;
	st << "String:" << m_Text;
	STLOG(st);
	
	st << "checked string:" << m_Text.substr(0,pos);
	STLOG(st);
	*/
	
	if (pos==0) {
		m_PosPixels=0;
	} else {
	
		m_PosPixels=GuiData::guiSmallFont->getDrawWidth(m_Text.substr(0,pos));
	}
}

/**
 *
 */
int TextMarker::getPosition() const
{
	return m_Pos;
}

/**
 *
 */
int TextMarker::getPixels() const
{
	return m_PosPixels;
}

/*\n *\n */
/*void TextMarker::SetPixelPos(int a)
{
	m_PosPixels=a;
}
*/

/*
 *
 */
TextMarker TextMarker::operator++(int a)
{
	/*
	std::cout << "m_Pos:" << m_Pos << std::endl;
	std::cout << "m_Text.length():" << (int)m_Text.length() << std::endl;
	*/
	
	if (m_Pos<(int)m_Text.length()) {
		
		if (m_Pos==-1) {
			std::cout << "EXCEPTION: m_Pos=-1" << std::endl;
		} else {
			/*
			char ch=m_Text.at(m_Pos);
		
			
			
			//std::cout << "m_Text:" << m_Text << std::endl;
							
			std::stringstream charString;
			charString.str("");
			charString << (char)ch;
			
			//std::cout << "Char:" << charString.str() << std::endl;
			
			
			m_PosPixels+=GuiData::guiSmallFont->GetStringWidth(charString.str());
			m_Pos++;
			*/
			
			// New try:
			
			m_Pos++;
			
			std::string newstring=m_Text.substr(0,m_Pos);
			
			m_PosPixels=GuiData::guiSmallFont->getDrawWidth(newstring);
			
		}
		//}
	}
	
	return *this;
}

/**
 *
 */
TextMarker TextMarker::operator--(int a)
{
	if (m_Pos>0) {
		//char ch=m_Text.at(m_Pos-1);
			/*			
		std::stringstream charString;
		charString << ch;
		
		m_PosPixels-=GuiData::guiSmallFont->DrawWidth(charString.str());
		*/
		
		
		
		m_Pos--;
		
		std::string newstring=m_Text.substr(0,m_Pos);
		
		m_PosPixels=GuiData::guiSmallFont->getDrawWidth(newstring);
	}
	
	return *this;
}

/**
 *
 */
void TextMarker::setText(const std::string &text)
{
	m_Text=text;
	
	//SetPosition((int)m_Text.length());
}

/**
 *
 */
bool TextMarker::operator==(const TextMarker &mark)
{
	bool result=false;
	
	if ((mark.m_PosPixels==m_PosPixels) && (mark.m_Pos==m_Pos)) {
		result=true;
	}
	
	return result;
}

/**
 *
 */
bool TextMarker::operator!=(const TextMarker &mark) 
{
	return !operator==(mark);
}

/**
 *
 */
TextMarker &TextMarker::operator=(const TextMarker &mark)
{
	
	if (this!=&mark) {

		m_PosPixels=mark.m_PosPixels;
		m_Pos=mark.m_Pos;

		m_Text=mark.m_Text;
		
	}
	
	return *this;
}

/**
 *
 */
std::string TextMarker::getText() const
{
	return m_Text;
}


// end of namespace
// ----------------
};
