/**
 * This file is part of Damnation of the Gods
 * Copyright 2010 Andreas Rönnquist
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
#ifndef __HEADER_LOADER_METER_
#define __HEADER_LOADER_METER_

/**
 *
 */
namespace GuiLib
{

/**
 *
 */
class LoaderMeter : public GuiObject
{
public:
	LoaderMeter(Rect rect,int maxValue);
	virtual ~LoaderMeter();

	virtual void draw(const Vector2d &pos,float opacity=1.0f);

	virtual void update();

	void increaseValue();

protected:
	
	int m_MaxValue;
	int m_Value;

	int m_FullWidth;
};
	
// end of namespace
// ----------------
};

#endif /*__HEADER_LOADER_METER_*/
