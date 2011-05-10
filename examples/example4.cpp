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
class ExampleEventHandler : public EventHandler
{
public:
	
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
};


/**
 * main - the standard c++ program main entry point
 */
int main(int argc,char **argv)
{
	EventHandler *eventHandler=NULL;
	GLBitmap *mouseBitmap=NULL;
	Font *font=NULL;
	
	try {
		// init the log - this function takes a string (the log file filename) as indata,
		// if none is inserted, "log.txt" is assumed. If you give the empty string "" 
		// as filename for the log, no log will be used.
		// 
		// The second indata is a boolean to determine to print the log to std::cout
		// or not in addition to to the file.
		LogHandler::initLog("",false);
				
		// init system stuff
		System::instance();
		
		// set up a screen with resolution of 640x480, and not fullscreen
		GraphicsHandler::instance()->initGraphicsHandler(Vector2d(640,480),false);
		
		// set a window title
		GraphicsHandler::instance()->setWindowTitle("GusGame Example 4");	
	
		// Create an EventHandler for our "custom" events
		eventHandler=new ExampleEventHandler();
		
		// set the used EventHandler to the one we just created.
		EventHelper::instance()->setEventHandler(eventHandler);
		
		mouseBitmap=new GLBitmap("../data/mouse.png");
		
		System::instance()->getMouse()->setMouseBitmap(mouseBitmap);
		
		FontHandler::instance();
		
		font=new Font("../data/FreeSans.ttf",12);
		
		GuiData::setGuiFont(font);
		
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
		
		// Handle events (see the class just above this main
		EventHelper::instance()->handleEvents();
		
		// Clear the screen every sync
		GraphicsHandler::instance()->clearScreen();
		
		System::instance()->getMouse()->draw();
	
		// Update the screen
		GraphicsHandler::instance()->updateScreen();
	} while(!quit);
	
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
