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
#ifndef __HEADER_GUI_HANDLER_
#define __HEADER_GUI_HANDLER_

/**
 *
 */
namespace GuiLib
{


// Gui Events 64 - 127	
const int EVENT_SWITCH_CONSOLE=				64;
const int EVENT_ENTER_CONSOLE_COMMAND=		65;

/**
 *	GuiHandler Singleton
 */
class GuiHandler
{
public:
	static GuiHandler *instance();

	static void destroy();

	bool getShowKeyboardShortcuts() const;

	GuiObject *getCurrentGuiObject();
	void setCurrentGuiObject(GuiObject *guiObj);

	void setNoMouseOver(std::vector<GuiObject*> *guiList);
	
	void draw(std::vector<GuiObject*> *guiList);
	void update(std::vector<GuiObject*> *guiList);

	bool handleUserEvent(std::vector<GuiObject*> *guiList,UserEvent &event);
	bool handleKeyboardEvent(std::vector<GuiObject*> *guiList,KeyEvent &event);
	
	void onLeftMouseButtonPressed(std::vector<GuiObject*> *guiList,const Vector2d& pos);
	void onLeftMouseButtonReleased(std::vector<GuiObject*> *guiList,const Vector2d& pos);
	
	void onRightMouseButtonPressed(std::vector<GuiObject*> *guiList,const Vector2d& pos);
	void onRightMouseButtonReleased(std::vector<GuiObject*> *guiList,const Vector2d& pos);
	
	void onMouseMove(std::vector<GuiObject*> *guiList,const Vector2d& pos);
	
	void onMouseScrollUp(std::vector<GuiObject*> *guiList,const Vector2d& pos);
	void onMouseScrollDown(std::vector<GuiObject*> *guiList,const Vector2d& pos);

	//SDL_Event MakeEvent(int code);

	// Events specific to the GUI
	UserEvent *eventSwitchConsole;
	UserEvent *eventEnterConsoleCommand;

protected:
	GuiHandler();
	virtual ~GuiHandler();

	GuiHandler(const GuiHandler &);
	GuiHandler& operator=(const GuiHandler&);
	
	GuiObject *m_CurrentGuiObject;
	
	bool showKeyboardShortcuts;

private:
	static GuiHandler *pinstance;
	
};

// end of namespace
// ----------------
}

#endif /*__HEADER_GUI_HANDLER_*/
