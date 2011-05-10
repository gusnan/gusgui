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
#ifndef __HEADER_FADE_BUTTON_
#define __HEADER_FADE_BUTTON_

/**
 *
 */
namespace GuiLib
{

/**
 *
 */
class FadeButton : public Button
{
public:
	FadeButton(Rect rect);
	virtual ~FadeButton();

	void setPressed();

	virtual void draw(const Vector2d& pos,float opacity=1.0f);

	virtual void update();

	void setShowHover(bool hover);

	bool onLeftMouseButtonPressed(const Vector2d& pos);
	void onLeftMouseButtonReleased(const Vector2d& pos);

	virtual void onMouseMove(const Vector2d& pos);

protected:
	float m_Fade;

	bool m_ShowHover;
};
	
// end of namespace
// ----------------
};

#endif
