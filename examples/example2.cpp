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
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "GusGame/GusGame.h"

using namespace Gus;

using namespace LogLib;
using namespace ExceptionLib;
using namespace GraphicsLib;
using namespace EventLib;

#include "GusGui/GusGui.h"

using namespace GusGui;

bool quit=false;

/**
 * This is an Eventhandler that takes care of the keyboard events, mouse motion
 *	events, and the Quit events. (This event is pushed when you press the close 
 * window button for example)
 */
class ExampleEventHandler : public GuiEventHandler
{
public:
	
	ExampleEventHandler(std::vector<GuiObject*> *guiList) : GuiEventHandler(guiList)
	{
	}
	
	/**
	 * Handle keyboard presses and releases
	 */
	virtual void handleKeyboard(KeyEvent &keyEvent) {
		
		// Is it the Escape Button that is pressed? - then quit
		if (keyEvent.getType()==KeyEventPressed) {
			if (keyEvent.getValue()==Key::Escape) {
				quit=true;
			}
		}
	}
	
	/**
	 * handle the quit event (This is called when the window close button is pressed.)
	 */
	virtual void handleQuitEvent()
	{
		quit=true;
	}
	
	/**
	 *
	 */
	virtual int handleUserEvent(UserEvent &userEvent)
	{
		LOG("User event..");
		GuiEventHandler::handleUserEvent(userEvent);
	}

};

/**
 *
 */
class ExampleButton : public Button
{
public:
	
	ExampleButton(const Rect &rect) : Button(rect,NULL,true)
	{
	}
	
	virtual ~ExampleButton()
	{
	}
	
	virtual void draw(const Vector2d& pos,float alpha=1.0)
	{
		// Gray for standard button
		GLPrimitives::rectFill(getRect()+pos,colorLightGray);
		if (getMouseOver()) {
			
			// red when hovered
			GLPrimitives::rectFill(getRect()+pos,colorRed);
			if (getDown()) {
				// and white when pressed
				GLPrimitives::rectFill(getRect()+pos,colorWhite);
			}
		}
	}
	
	
protected:
};

/**
 * this is a panel for the example
 * A panel is a container that contains several different GuiObjects. A dialog
 * is a great example of a panel.
 */
class ExamplePanel : Panel
{
public:
	ExamplePanel() : Panel(Rect(100,100,400,300))
	{
		// We add a button to the panel. This at position 10,10 in the panel,
		// which places it at 110,110 on the screen.
		m_ExampleButton=new ExampleButton(Rect(10,10,100,20));
		addGuiObject(m_ExampleButton);
		
		m_QuitButton=new ExampleButton(Rect(10,40,100,20));
		m_QuitButton->setEvent(EventLib::eventQuit);
		addGuiObject(m_QuitButton);
	}
	
	virtual ~ExamplePanel()
	{
		// We don't need to destroy the GuiObjects here - it is automatically done in the
		// Panel destructor, which we inherit this class from.
	}
	
	void draw(const Vector2d &pos,float opacity=1.0)
	{
		// Draw a white outline on the panel
		Rect newRect=getRect()+pos;
		
		GLPrimitives::drawRect(newRect,colorWhite);
		
		// Make the Panel class which we inherit from draw the gui objects
		Panel::draw(pos,opacity);
	}
	
protected:
	Button *m_ExampleButton;
	Button *m_QuitButton;
};



/**
 * main - the standard c++ program main entry point
 */
int main(int argc,char **argv)
{
	EventHandler *eventHandler=NULL;
	GLBitmap *mouseBitmap=NULL;
	Font *font=NULL;
	UserEvent *testEvent=NULL;
	ExamplePanel *panel=NULL;
	std::vector<GuiObject*> *guiList=NULL;
	GuiEventHandler *guiEventHandler=NULL;
	
	try {
		// init the log - this function takes a string (the log file filename) as indata,
		// if none is inserted, "log.txt" is assumed. If you give the empty string "" 
		// as filename for the log, no log will be used.
		// 
		// The second indata is a boolean to determine to print the log to std::cout
		// or not in addition to to the file.
		LogHandler::initLog("log.txt",true);
				
		// init system stuff
		System::instance();
		
		// set up a screen with resolution of 640x480, and not fullscreen
		GraphicsHandler::instance()->initGraphicsHandler(Vector2d(640,480),false);
		
		// set a window title
		GraphicsHandler::instance()->setWindowTitle("GusGame Example 2");
		
		mouseBitmap=new GLBitmap("mouse.png");
		
		System::instance()->getMouse()->setMouseBitmap(mouseBitmap);
		
		FontHandler::instance();
		
		font=new Font("FreeSans.ttf",12);
		
		GuiData::setGuiFont(font);
		
		testEvent=new UserEvent();
		
		// This must be initialized before the Examplepanel
		EventData::instance();

		guiList=new std::vector<GuiObject*>;
		panel=new ExamplePanel();
		
		//guiList->push_back((GuiObject*)panel);
		guiList->push_back((GuiObject*)panel);
		
		// Create an EventHandler for our "custom" events
		// which inherits from the GUI event handler, this for it
		// to handle both GUI events, and our own custom ones for
		// just this example
		eventHandler=new ExampleEventHandler(guiList);

		// set the used EventHandler to the one we just created.
		//	EventHelper::instance()->setEventHandler(guiEventHandler);
		EventHelper::instance()->setEventHandler(eventHandler);

				
	}
	catch (Exception &e)
	{
		// If we get any problems with the code in the throw block, it will be
		// caught here
		std::cerr << "Exception: " << e.getString() << std::endl;
		
		return EXIT_FAILURE;
	}
	
	LOG("Enter main loop.");
	
	// the main loop
	do {
		// Update the timer
		Timer::instance()->updateFrame();
		
		GuiHandler::instance()->update(guiList);
		
		// Handle events (see the class just above this main
		EventHelper::instance()->handleEvents();
		
		// Clear the screen every sync
		GraphicsHandler::instance()->clearScreen();
		
		GuiHandler::instance()->draw(guiList);
		
		// Draw the mouse cursor
		System::instance()->getMouse()->draw();
	
		// Update the screen
		GraphicsHandler::instance()->updateScreen();
	} while(!quit);
	
	delete panel;
	
	delete font;
	delete mouseBitmap;
	
	// Remove our custom eventHandler
	delete eventHandler;
	
	FontHandler::destroy();
	
	// done with system stuff
	System::destroy();
	
	// done with the Log
	LogHandler::doneLog();
	
	return EXIT_SUCCESS;
}
