/**
 * This file is part of Damnation of the Gods
 * Copyright 2008,2009 Andreas Rönnquist
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
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "GusGame/GusGame.h"
using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"
#include "Button.h"
#include "Panel.h"

#include "GuiHandler.h"

/**
 *
 */
namespace GuiLib
{

	
GuiHandler* GuiHandler::pinstance = 0;// initialize pointer

/**
 *	This should be a singleton, thus we need the Instance method
 */
GuiHandler* GuiHandler::instance () 
{
	if (pinstance == 0) {  
		pinstance = new GuiHandler;
	}
	return pinstance;
}

/**
 *
 */
void GuiHandler::destroy()
{
	delete pinstance;
	pinstance=0;
}


/**
 *
 */
GuiHandler::GuiHandler() : 
	eventSwitchConsole(0),
	eventEnterConsoleCommand(0),
	m_CurrentGuiObject(0),
	showKeyboardShortcuts(false)
{
	LOG("Init Gui Handler...");
	
	showKeyboardShortcuts=false;
	
	m_CurrentGuiObject=0;
	
	eventSwitchConsole=new UserEvent(EVENT_SWITCH_CONSOLE);
	eventEnterConsoleCommand=new UserEvent(EVENT_ENTER_CONSOLE_COMMAND);
}

/**
 *
 */
GuiHandler::~GuiHandler()
{
	LOG("Done Gui Handler");
	
	if (eventSwitchConsole!=NULL) {
		delete eventSwitchConsole;
		eventSwitchConsole=NULL;
	}
	
	if (eventEnterConsoleCommand!=NULL) {
		delete eventEnterConsoleCommand;
		eventEnterConsoleCommand=NULL;
	}
}

/**
 *
 */
/*
SDL_Event GuiHandler::MakeEvent(int code)
{
	SDL_Event event;
	
	event.type=SDL_USEREVENT;
	event.user.code=code;
	event.user.data1=0;
	event.user.data2=0;
	
	return event;
}
*/


/**
 *
 */
void GuiHandler::draw(std::vector<GuiObject*> *guiList)
{
	const Vector2d pos=Vector2d(0,0);
	for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
		//(*iter)->Draw(Vector2d(0,0));
		(*iter)->draw(pos);
		++iter;
	}

}

/**
 *
 */
void GuiHandler::update(std::vector<GuiObject*> *guiList)
{
	
	std::vector<GuiObject*>::iterator iter;
	for (iter=guiList->begin();iter!=guiList->end();) {
		
		(*iter)->update();
		++iter;
	}

}

/**
 *
 */
void GuiHandler::setNoMouseOver(std::vector<GuiObject*> *guiList)
{
	for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
		(*iter)->setMouseOver(false);
		++iter;
	}
}

/**
 *
 */
bool GuiHandler::handleUserEvent(std::vector<GuiObject*> *guiList,UserEvent &event)
{
	bool res=false;
	
	if (guiList) {
		for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
			
			if (!res) {
				res=(*iter)->handleUserEvent(event);
			}
			++iter;
		}
		
	}
	
	return res;
}

/**
 *
 */
bool GuiHandler::handleKeyboardEvent(std::vector<GuiObject*> *guiList,KeyEvent &event)
{
	bool res=false;
	
	//LOG("GuiHandler::HandleKeyboardEvent");
	
	if (guiList) {
		for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
			
			if (!res) {
				res=(*iter)->handleKeyboardEvent(event);
			}
			++iter;
		}
		
	}
	
	return res;
	
}

/**
 *
 */
void GuiHandler::onLeftMouseButtonPressed(std::vector<GuiObject*> *guiList,const Vector2d& pos)
{
	bool handled=false;
	
	if (guiList) {
		for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
			GuiObject *current=(*iter);
			
			if (current && !handled) {
				handled=current->onLeftMouseButtonPressed(pos);
			}
			++iter;
		}
	}
}

/**
 *
 */
void GuiHandler::onLeftMouseButtonReleased(std::vector<GuiObject*> *guiList,const Vector2d& pos)
{
	if (guiList) {
		for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
			GuiObject *current=(*iter);
			
			if (current) {
				current->onLeftMouseButtonReleased(pos);
			}
			++iter;
		}
	}
}

/**
 *
 */
void GuiHandler::onRightMouseButtonPressed(std::vector<GuiObject*> *guiList,const Vector2d& pos)
{
	bool handled=false;
	if (guiList) {
		for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
			GuiObject *current=(*iter);
			
			if (current && !handled) {
				handled=current->onRightMouseButtonPressed(pos);
			}
			++iter;
		}
	}
}

/**
 *
 */
void GuiHandler::onRightMouseButtonReleased(std::vector<GuiObject*> *guiList,const Vector2d& pos)
{
	if (guiList) {
		for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
			GuiObject *current=(*iter);
			
			if (current) {
				current->onRightMouseButtonReleased(pos);
			}
			++iter;
		}
	}
}

/**
 *
 */
bool GuiHandler::getShowKeyboardShortcuts() const
{
	return showKeyboardShortcuts;
}

/**
 *
 */
GuiObject *GuiHandler::getCurrentGuiObject()
{
	return m_CurrentGuiObject;
}

/**
 *
 */
void GuiHandler::setCurrentGuiObject(GuiObject *guiObj)
{
	GuiObject *oldCurrentGuiObject=m_CurrentGuiObject;
	
	m_CurrentGuiObject=guiObj;
	
	if	(m_CurrentGuiObject!=oldCurrentGuiObject) {
		if (m_CurrentGuiObject) {
			m_CurrentGuiObject->gainFocus();
		}
	}

}

/**
 *
 */
void GuiHandler::onMouseMove(std::vector<GuiObject*> *guiList,const Vector2d& pos)
{
	
	for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
		GuiObject *object=(*iter);
		
		if (object) {
			object->onMouseMove(pos);
		}
		
		++iter;
	}
}

/**
 *
 */
void GuiHandler::onMouseScrollUp(std::vector<GuiObject*> *guiList,const Vector2d& pos)
{
	if (guiList) {
		for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
			GuiObject *object=(*iter);
			
			if (object) {
				object->onMouseScrollUp(pos);
			}
			
			++iter;
		}	
	}
}

/**
 *
 */
void GuiHandler::onMouseScrollDown(std::vector<GuiObject*> *guiList,const Vector2d& pos)
{
	if (guiList) {	
		for (std::vector<GuiObject*>::iterator iter=guiList->begin();iter!=guiList->end();) {
			GuiObject *object=(*iter);
			
			if (object) {
				object->onMouseScrollDown(pos);
			}
			
			++iter;
		}	
	}
}

// end of namespace
// ----------------
}

