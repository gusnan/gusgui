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
#ifndef __HEADER_TEXT_INPUT_FIELD_
#define __HEADER_TEXT_INPUT_FIELD_

#include "TextMarker.h"

/**
 *
 */
namespace GuiLib
{

/**
 *
 */
class TextInput : public GuiObject
{
public:
	TextInput(const Rect &rect,std::string initText);
	virtual ~TextInput();

	TextInput(const TextInput& source);

	TextInput& operator=(const TextInput& source);

	virtual void draw(const Vector2d &position,float opacity=1.0f);
	virtual bool handleKeyboardEvent(KeyEvent &event);

	bool onLeftMouseButtonPressed(const Vector2d& pos);

	virtual void update();

	void addCharacter(std::string st);

	void drawCursor(const Rect &rect);

	void clearMarking();

	bool canAddCharacter(std::string st);

	virtual void lostFocus();

	int getPositionInText(int pixelPos);
	
	bool isPunctuation(char ch);
	
	int positionWordLeft();
	
	bool moveWordRight();
	bool moveWordLeft();
	
	bool left(KeyEvent &event);
	bool right(KeyEvent &event);
	
	bool haveMarker();
	
	void setDrawFrame(bool draw=true);
	
	std::string getText();
	void setText(std::string text);
	void clear();
	
	virtual void gainFocus();
	
	void checkSwap();
	
	void setDrawPrompt(bool drawPrompt=true);
	
	void setCursorActive();

protected:

	void getNextInputLine();
	void getPreviousInputLine();
	
	std::string m_Text;

	float m_Timer;

	bool m_CursorVisible;

	TextMarker m_MarkStart,m_MarkEnd;
	TextMarker m_CursorPosition;

	static const float c_FlashDelay;

	bool m_WaitForRelease;


	Uint32 m_DoubleClickTicks;
	Uint32 m_OldDoubleClickTicks;


	bool m_Shift;
	bool m_OldShift;
	
	bool m_DrawFrame;
	
	bool m_AllowNumbers;
	bool m_AllowSeparators;
	
	bool m_DrawPrompt;
	
	std::vector<std::string> *m_StoredInputLines;
	int m_CurrentStoredInputLine;
	
	//static bool doubleHelper;
};

// end of namespace
// ----------------
};

#endif /*__HEADER_TEXT_INPUT_FIELD_*/
