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
#ifndef __HEADER_PANEL_
#define __HEADER_PANEL_

/**
 *
 */
namespace GusGui
{
	
/**
 *
 */
class Panel : public GuiObject
{
public:
	Panel();

	Panel(Rect rect,bool transFrame=true);
	Panel(const Panel& source);
	virtual ~Panel();

	Panel& operator=(const Panel& source);


	void addGuiObject(GuiObjectPtr guiObject);

	void draw(const Vector2d& pos,float alpha=1.0);

	void update();

	void setDrawFrame(bool drawFrame=true);
	void setDrawBackground(bool drawBackground=true);

	void setMouseOver(bool b);

	virtual bool handleUserEvent(UserEvent &event);
	virtual bool handleKeyboardEvent(KeyEvent &event);
	
	virtual bool onLeftMouseButtonPressed(const Vector2d& pos);
	virtual void onLeftMouseButtonReleased(const Vector2d& pos);
	
	virtual bool onRightMouseButtonPressed(const Vector2d& pos);
	virtual void onRightMouseButtonReleased(const Vector2d& pos);
	
	virtual void onMouseMove(const Vector2d& pos);
	
	virtual void onMouseScrollUp();
	virtual void onMouseScrollDown();
	
	virtual void onDrag(const Vector2d& pos);

	virtual void setVisible(bool visible=true);
	
	virtual void setActive(bool active=true);
	
protected:
	
	std::vector<GuiObjectPtr> *m_GuiList;

	bool m_DrawFrame;
	bool m_TransparentFrame;
	bool m_DrawBackground;
	
};

// end of namespace
// ----------------
}

#endif /*__HEADER_PANEL_*/
