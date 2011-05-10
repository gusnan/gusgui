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
#ifndef __HEADER_DELAY_BUTTON_
#define __HEADER_DELAY_BUTTON_

/**
 *
 */
namespace GusGui
{
	
/**
 *
 */
class DelayButton : public Button
{
public:
	DelayButton(Rect rect,Rect sourceRect,Rect sourceRectPressed,GLBitmap *icon,Rect iconSourceRect);
	virtual ~DelayButton();

	void draw(const Vector2d& pos,float alpha);

	virtual void update();

	bool getPressed() const;
	void setPressed();

	void setSpeed(float speed);

	virtual bool handleKeyboardEvent(KeyEvent &event);

	virtual bool onLeftMouseButtonPressed(const Vector2d& pos);
	virtual void onLeftMouseButtonReleased(const Vector2d& pos);


protected:
	float m_Delay;

	float m_Speed;

	Rect m_IconSourceRect;
	Rect m_SourceRectPressed;

};

// end of namespace 
// ----------------
};

#endif /*__HEADER_DELAY_BUTTON_*/
