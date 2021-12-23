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

/**
 *	GuiHandler Singleton
 */
class GuiHandler
{
public:
   static GuiHandler *instance();

   static void destroy();

   bool getShowKeyboardShortcuts() const;

   std::shared_ptr<GuiObject> getCurrentGuiObject();
   void setCurrentGuiObject(std::shared_ptr<GuiObject> guiObj);

   void setNoMouseOver();

   void draw();
   void update();

   //SDL_Event MakeEvent(int code);

   void addGuiObject(const std::shared_ptr<GuiObject> &guiObject);
   void removeGuiObject(const std::shared_ptr<GuiObject> &guiObject);

   void addToDrawList(const std::shared_ptr<GuiObject> &guiObject);
   void removeFromDrawList(const std::shared_ptr<GuiObject> &guiObject);

   void addToHandleList(const std::shared_ptr<GuiObject> &guiObject);
   void removeFromHandleList(const std::shared_ptr<GuiObject> &guiObject);

   void copyDrawListToHandleList();

   void clearHandleList();

   bool isGuiObjectInList(std::shared_ptr<GuiObject> guiObject);

   friend GuiEventHandler;

   void setGuiObjectListActive(bool active);

   void updateMouseOver();
   
   void print();

protected:

   GuiHandler();
   virtual ~GuiHandler();

   GuiHandler(const GuiHandler &);
   GuiHandler& operator=(const GuiHandler&);

   std::shared_ptr<GuiObject> m_CurrentGuiObject;

   bool showKeyboardShortcuts;

   std::vector<std::shared_ptr<GuiObject> > *m_GuiList;
   std::vector<std::shared_ptr<GuiObject> > *m_GuiDrawList;

private:
   static GuiHandler *pinstance;

};

// end of namespace
// ----------------
}

#endif /*__HEADER_GUI_HANDLER_*/
