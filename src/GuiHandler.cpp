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

#include <boost/shared_ptr.hpp>

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

#include "GuiEventHandler.h"
#include "GuiHandler.h"

/**
 *
 */
namespace GusGui
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
	pinstance = 0;
}


/**
 *
 */
GuiHandler::GuiHandler() :
	m_CurrentGuiObject(boost::shared_ptr<GuiObject>()),
	showKeyboardShortcuts(false),
	m_GuiList(NULL),
	m_GuiDrawList(NULL)
{
	LOG("Init Gui Handler...");

	showKeyboardShortcuts = false;

	m_CurrentGuiObject = boost::shared_ptr<GuiObject>();

	m_GuiList = new std::vector<boost::shared_ptr<GuiObject> >;
	m_GuiDrawList = new std::vector<boost::shared_ptr<GuiObject> >;
}

/**
 *
 */
GuiHandler::~GuiHandler()
{
	LOG("Done Gui Handler");

	clearHandleList();

	if (m_GuiList) {
		delete m_GuiList;
		m_GuiList = NULL;
	}

	if (m_GuiDrawList != NULL) {

		std::vector<GuiObjectPtr>::iterator iter;
		for (iter = m_GuiDrawList->begin(); iter != m_GuiDrawList->end();) {

			iter = m_GuiDrawList->erase(iter);
		}


		delete m_GuiDrawList;
		m_GuiDrawList = NULL;
	}
}


/**
 *
 */
void GuiHandler::clearHandleList()
{

	if (m_GuiList != NULL) {

		std::vector<GuiObjectPtr>::iterator iter;
		for (iter = m_GuiList->begin(); iter != m_GuiList->end();) {

			iter = m_GuiList->erase(iter);
		}
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
void GuiHandler::draw()
{
	const Vector2d pos=Vector2d(0,0);
	if (m_GuiDrawList) {
		for (std::vector<GuiObjectPtr>::iterator iter = m_GuiDrawList->begin(); iter != m_GuiDrawList->end();) {
			//(*iter)->Draw(Vector2d(0,0));
			(*iter)->draw(pos);
			++iter;
		}
	}

}

/**
 *
 */
void GuiHandler::update()
{

	std::vector<GuiObjectPtr>::iterator iter;
	for (iter = m_GuiList->begin(); iter != m_GuiList->end();) {

		(*iter)->update();
		++iter;
	}

}

/**
 *
 */
void GuiHandler::setNoMouseOver()
{
	for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter != m_GuiList->end();) {
		(*iter)->setMouseOver(false);
		++iter;
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
GuiObjectPtr GuiHandler::getCurrentGuiObject()
{
	return m_CurrentGuiObject;
}

/**
 *
 */
void GuiHandler::setCurrentGuiObject(GuiObjectPtr guiObj)
{
	GuiObject *oldCurrentGuiObject = m_CurrentGuiObject.get();

	m_CurrentGuiObject = guiObj;

	if	(m_CurrentGuiObject.get() != oldCurrentGuiObject) {
		if (m_CurrentGuiObject) {
			m_CurrentGuiObject->gainFocus();
		}
	}

}


/**
 *
 */
void GuiHandler::updateMouseOver()
{
	MouseMotionEvent mouseMotion;
	Vector2d position = mouseMotion.getPosition();

	if (m_GuiList) {
		for (std::vector<GuiObjectPtr>::iterator iter = m_GuiList->begin(); iter != m_GuiList->end();) {
			GuiObjectPtr object=(*iter);

			if (object) {
				object->onMouseMove(position);
			}

			++iter;
		}
	}

}



/**
 *
 */
void GuiHandler::addToHandleList(const GuiObjectPtr &guiObject)
{
	if (guiObject != boost::shared_ptr<GuiObject>()) {
		if (m_GuiList) {
			m_GuiList->push_back(guiObject);
		}
	}
	setNoMouseOver();

	updateMouseOver();


	//update();
}


/**
 *
 */
void GuiHandler::removeFromHandleList(const GuiObjectPtr &guiObject)
{
	std::vector<GuiObjectPtr>::iterator iter;
	GuiObjectPtr currentGuiObject = boost::shared_ptr<GuiObject>();

	// GuiObject *inGuiObject = guiObject.get();

	if (m_GuiList) {

		if (!m_GuiList->empty()) {
			
			
			m_GuiList->erase(
				std::remove(m_GuiList->begin(), m_GuiList->end(), guiObject),
    m_GuiList->end());
			
/*
			for (iter = m_GuiList->begin(); iter != m_GuiList->end(); ) {

				currentGuiObject = (*iter);

				if (inGuiObject == currentGuiObject.get()) {
					iter = m_GuiList->erase(iter);
				} else {
					++iter;
				}
			}
			*/

		}
	}

	setNoMouseOver();
	update();
}


/**
 *
 */
void GuiHandler::addToDrawList(const GuiObjectPtr &guiObject)
{
	if (guiObject != boost::shared_ptr<GuiObject>()) {
		if (m_GuiDrawList) {
			m_GuiDrawList->push_back(guiObject);
		}
	}
}


/**
 *
 */
void GuiHandler::removeFromDrawList(const GuiObjectPtr &guiObject)
{
	std::vector<GuiObjectPtr>::iterator iter;
	GuiObjectPtr currentGuiObject; // = boost::shared_ptr<GuiObject>();

	// GuiObject *inGuiObject = guiObject;
	
	bool done = false;

	if (m_GuiDrawList) {

		if (!m_GuiDrawList->empty()) {

			/*
			for (iter = m_GuiDrawList->begin(); iter != m_GuiDrawList->end(), !done; ) {
				
				if (!done) {

				currentGuiObject = (*iter);

				if (guiObject.get() == currentGuiObject.get()) {
					iter = m_GuiDrawList->erase(iter);
					done = true;
				} else {
					++iter;
				}
			}
			}
			*/
			
			m_GuiDrawList->erase(
				std::remove(m_GuiDrawList->begin(), m_GuiDrawList->end(), guiObject),
    m_GuiDrawList->end());
			
		}
	}
}


/**
 *
 */
void GuiHandler::copyDrawListToHandleList()
{
	GuiObjectPtr currentGuiObject = boost::shared_ptr<GuiObject>();

	if (m_GuiDrawList) {
		if (m_GuiList) {
			clearHandleList();

			std::vector<GuiObjectPtr>::iterator iter;
			for (iter = m_GuiDrawList->begin(); iter != m_GuiDrawList->end(); ) {

				currentGuiObject = (*iter);

				m_GuiList->push_back(currentGuiObject);

				++iter;
			}
		}
	}
}


/**
 *
 */
void GuiHandler::addGuiObject(const GuiObjectPtr &guiObject)
{
	addToDrawList(guiObject);
	addToHandleList(guiObject);
}


/**
 *
 */
void GuiHandler::removeGuiObject(const GuiObjectPtr &guiObject)
{
	removeFromDrawList(guiObject);
	removeFromHandleList(guiObject);
}


/**
 *
 */
bool GuiHandler::isGuiObjectInList(GuiObjectPtr inGuiObject)
{
	bool result=false;
	std::vector<GuiObjectPtr>::iterator iter;
	GuiObjectPtr currentGuiObject = boost::shared_ptr<GuiObject>();

	if (m_GuiList) {

		if (!m_GuiList->empty()) {

			for (iter = m_GuiList->begin(); iter != m_GuiList->end(); ) {

				currentGuiObject = (*iter);

				if (inGuiObject.get() == currentGuiObject.get()) {
					result=true;
				}

				++iter;
			}
		}
	}
	return result;
}



/**
 *
 */
void GuiHandler::setGuiObjectListActive(bool active = true)
{
	std::vector<GuiObjectPtr>::iterator iter;
	GuiObjectPtr currentGuiObject = boost::shared_ptr<GuiObject>();

	if (m_GuiList) {

		if (!m_GuiList->empty()) {

			for (iter = m_GuiList->begin(); iter != m_GuiList->end(); ) {

				currentGuiObject = (*iter);

				currentGuiObject->setActive(active);

				++iter;
			}
		}
	}
}

/**
 *
 */
void GuiHandler::print()
{
	std::vector<GuiObjectPtr>::iterator iter;
	GuiObjectPtr currentGuiObject = boost::shared_ptr<GuiObject>();
	
	std::cout << "----------------------------" << std::endl;

	if (m_GuiList) {

		if (!m_GuiList->empty()) {

			for (iter = m_GuiList->begin(); iter != m_GuiList->end(); ) {

				currentGuiObject = (*iter);

				currentGuiObject->print();

				++iter;
			}
		}
	}
	
	std::cout << "----------------------------" << std::endl;
}


/**
 *
 */
/*
std::vector<GuiObjectPtr> *GuiHandler::getGuiList()
{
	return m_GuiList;
}
*/

// end of namespace
// ----------------
}


