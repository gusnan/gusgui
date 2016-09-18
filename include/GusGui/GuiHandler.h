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
namespace GusGui
{


// Gui Events 64 - 127
const int EVENT_SWITCH_CONSOLE = 64;
const int EVENT_ENTER_CONSOLE_COMMAND = 65;

/**
 *	GuiHandler Singleton
 */
class GuiHandler
{
public:
	static GuiHandler *instance();

	static void destroy();

	bool getShowKeyboardShortcuts() const;

	GuiObjectPtr getCurrentGuiObject();
	void setCurrentGuiObject(GuiObjectPtr guiObj);

	void setNoMouseOver();

	void draw();
	void update();

	//SDL_Event MakeEvent(int code);

	void addGuiObject(GuiObjectPtr guiObject);
	void removeGuiObject(GuiObjectPtr guiObject);

	void addToDrawList(GuiObjectPtr guiObject);
	void removeFromDrawList(GuiObjectPtr guiObject);

	void addToHandleList(GuiObjectPtr guiObject);
	void removeFromHandleList(GuiObjectPtr guiObject);

	void copyDrawListToHandleList();

	void clearHandleList();

	bool isGuiObjectInList(GuiObjectPtr guiObject);

	friend GuiEventHandler;

	void setGuiObjectListActive(bool active);

	void updateMouseOver();

protected:

	GuiHandler();
	virtual ~GuiHandler();

	GuiHandler(const GuiHandler &);
	GuiHandler& operator=(const GuiHandler&);

	GuiObjectPtr m_CurrentGuiObject;

	bool showKeyboardShortcuts;

	std::vector<boost::shared_ptr<GuiObject> > *m_GuiList;
	std::vector<boost::shared_ptr<GuiObject> > *m_GuiDrawList;

private:
	static GuiHandler *pinstance;

};

// end of namespace
// ----------------
}

#endif /*__HEADER_GUI_HANDLER_*/
