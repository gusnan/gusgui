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
#include <sstream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "InvisibleGuiObject.h"

namespace GuiLib
{

/**
 *
 */
InvisibleGuiObject::InvisibleGuiObject() : GuiObject(Rect(-1,-1,-1,-1))
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
