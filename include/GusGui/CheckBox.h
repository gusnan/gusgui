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
#ifndef __HEADER_CHECKBOX_
#define __HEADER_CHECKBOX_

/**
 *
 */
namespace GuiLib
{
	
/**
 *
 */
class CheckBox : public GuiObject
{
public:
	
	CheckBox();
	CheckBox(const CheckBox& source);
	CheckBox(Rect pos,bool checked=false);
	CheckBox(Rect pos,std::string text,bool checked=false);
	virtual ~CheckBox();

	CheckBox& operator=(const CheckBox& source);

	void draw(const Vector2d& pos,float alpha=1.0);

	void update();

	void setText(std::string text);

	bool getChecked() const;
	void setChecked(bool);

	void switchChecked();

	virtual bool handleKeyboardEvent(KeyEvent &event);
	
	bool onLeftMouseButtonPressed(const Vector2d& pos);
	void onLeftMouseButtonReleased(const Vector2d& pos);

protected:
	bool m_Checked;

	bool m_Down;

	std::string m_Text;

	GLBitmap *m_TextBitmap;

	Vector2d m_CheckBoxSize;

	// the text width in pixels
	int m_TextWidth;

};
	
// end of namespace
// ----------------
};

#endif /*__HEADER_CHECKBOX_*/
