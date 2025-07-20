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
namespace GusGui
{

/**
 *
 */
class FadeButton : public Button
{
public:
   FadeButton(Rect rect, std::string name);
   virtual ~FadeButton();

   void setPressed();

   virtual void draw(const Vector2d& pos, float opacity = 1.0f) override;

   virtual void update() override;

   void setShowHover(bool hover);

   bool onLeftMouseButtonPressed(const Vector2d& pos) override;
   bool onLeftMouseButtonReleased(const Vector2d& pos) override;

   virtual void onMouseMove(const Vector2d& pos) override;

protected:
   float m_Fade;

   bool m_ShowHover;
};

// end of namespace
// ----------------
};

#endif
