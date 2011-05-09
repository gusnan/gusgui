/**
 * This file is part of Damnation of the Gods
 * Copyright 2009 Andreas Rönnquist
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
#ifndef __HEADER_TEXT_MARKER_
#define __HEADER_TEXT_MARKER_

/**
 *
 */
namespace GuiLib
{

/**
 *
 */
class TextMarker
{	
public:
	TextMarker();
	TextMarker(const std::string &text);
	virtual ~TextMarker();

	TextMarker &operator=(const TextMarker &mark);


	void setPosition(int pos);
	int getPosition() const;

	int getPixels() const;
	//void SetPixelPos(int a);

	std::string getText() const;

	TextMarker operator++(int a);
	TextMarker operator--(int a);

	bool operator==(const TextMarker &mark);
	bool operator!=(const TextMarker &mark);

	void setText(const std::string &text);

protected:

	int m_PosPixels;
	int m_Pos;

	std::string m_Text;
	
};

// end of namespace
// ----------------
};

#endif
