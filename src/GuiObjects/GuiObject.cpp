#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

/**
 *
 */
namespace GuiLib
{

/**
 *
 */
GuiObject::GuiObject() : m_Rect(), m_MouseOver(false), m_Active(true), m_Visible(true), 
	m_PanelPosition(), m_Drag(false), m_DragOnlyWhenMouseOver(true), m_LastMousePosition()
{

}

/**
 *
 */
GuiObject::GuiObject(Rect rect) : m_Rect(rect), m_Active(true), m_Visible(true), m_MouseOver(false), 
	m_PanelPosition(), m_Drag(false), m_DragOnlyWhenMouseOver(true), m_LastMousePosition()
{
}

/**
 *
 */
GuiObject::~GuiObject()
{
}

/**
 *
 */
Vector2d GuiObject::getPosition() const
{
	return m_Rect.position;
}

/**
 *
 */
Rect GuiObject::getRect() const
{
	return m_Rect;
}

/**
 *
 */
void GuiObject::setRect(const Rect& rect)
{
	m_Rect=rect;
}

/**
 *
 */
void GuiObject::setSize(const Vector2d& size)
{
	m_Rect.size=size;
}

/**
 *
 */
void GuiObject::setCenter(const Vector2d& pos)
{
	m_Rect.setCenter(pos);
}


/**
 *
 */
void GuiObject::setMouseOver(bool over)
{
	m_MouseOver=over;
}

/**
 *
 */
void GuiObject::setActive(bool active)
{
	m_Active=active;
	
	//if (m_Active) {
		onMouseMove(m_LastMousePosition);
	//}
	
	//if (!active) m_MouseOver=false;
	
}

/**
 *
 */
void GuiObject::setVisible(bool visible)
{
	m_Visible=visible;
}

/**
 *
 */
void GuiObject::switchVisible()
{
	m_Visible=!m_Visible;
}

/**
 *
 */
bool GuiObject::getVisible() const
{
	return m_Visible;
}

/**
 *
 */
bool GuiObject::getMouseOver() const
{
	return m_MouseOver;
}

/**
 *
 */
bool GuiObject::handleUserEvent(UserEvent &event)
{
	return false;	
}

/**
 *
 */
bool GuiObject::handleKeyboardEvent(KeyEvent &event)
{
	return false;
}

/**
 *
 */
void GuiObject::gainFocus()
{
	
}

/**
 *
 */
void GuiObject::releaseFocus()
{
}

/**
 *
 */
bool GuiObject::onLeftMouseButtonPressed(const Vector2d& pos)
{
	m_Drag=true;
	return false;
}

/**
 *
 */
void GuiObject::onLeftMouseButtonReleased(const Vector2d& pos)
{
	m_Drag=false;
}

/**
 *
 */
bool GuiObject::onRightMouseButtonPressed(const Vector2d& pos)
{
	return false;
}

/**
 *
 */
void GuiObject::onRightMouseButtonReleased(const Vector2d& pos)
{
	
}

/**
 *
 */
void GuiObject::setPanelPosition(const Vector2d& pos)
{
	m_PanelPosition=pos;
}

/**
 *
 */
void GuiObject::onMouseMove(const Vector2d& pos)
{
	m_MouseOver=false;
	if (m_Active) {
		if (m_Rect.isPointOver(pos)) {
			m_MouseOver=true;
		} else {
			m_MouseOver=false;
		}
	}
	
	if (m_DragOnlyWhenMouseOver) {
		if (!m_MouseOver) m_Drag=false;
	}
	
	if (m_Drag) onDrag(pos);
	
	m_LastMousePosition=pos;
}

/**
 *
 */
void GuiObject::onMouseScrollUp(const Vector2d& pos)
{
}

/**
 *
 */
void GuiObject::onMouseScrollDown(const Vector2d& pos)
{
}

/**
 *
 */
void GuiObject::onDrag(const Vector2d& pos)
{
	if (m_MouseOver) {
		/*
		std::stringstream st;
		st << "GuiObject::Drag:" << pos.x << "," << pos.y;
		STLOG(st);
		*/
	}
}


// end of namespace
// ----------------
}
