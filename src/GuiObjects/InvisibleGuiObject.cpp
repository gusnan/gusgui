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

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <memory>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiEventHandler.h"
#include "GlobalEventHandler.h"

#include "GuiObject.h"

#include "InvisibleGuiObject.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
InvisibleGuiObject::InvisibleGuiObject() : GuiObject(Rect(-1, -1, -1, -1))
{
}


/**
 *
 */
InvisibleGuiObject::~InvisibleGuiObject()
{
}


/**
 *
 */
void InvisibleGuiObject::draw(const Vector2d &pos,float opacity)
{
}


/**
 *
 */
void InvisibleGuiObject::update()
{
}


// end of namespace
// ----------------
};
