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
#include <sstream>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::GraphicsLib;
using namespace Gus::EventLib;

#include "GuiObject.h"

#include "CheckBox.h"

#include "GuiData.h"

#include "GuiEventHandler.h"
#include "GuiHandler.h"

/**
 *
 */
namespace GusGui
{

/**
 *
 */
CheckBox::CheckBox() : GuiObject(),
	m_TextBitmap(0), m_Checked(false), m_Text(""), m_Down(false), m_CheckBoxSize(), m_TextWidth()
{
	m_CheckBoxSize = Vector2d(20, 18); //GuiData::checkBoxActivePressed->GetSize();

	m_Rect = Rect(0, 0, 0, 0);

	m_Text = "";

	m_MouseOver = false;
}

/**
 *
 */
CheckBox::CheckBox(Rect rect,bool checked) : GuiObject(rect),
	m_TextBitmap(0), m_Checked(false), m_Text(""), m_Down(false), m_CheckBoxSize(), m_TextWidth()
{

	m_TextBitmap = 0;

	m_CheckBoxSize = Vector2d(20, 18); //GuiData::checkBoxActivePressed->GetSize();

	m_Rect = Rect(rect.position,m_CheckBoxSize);

	m_Checked = checked;

	m_Text = "";

	m_MouseOver = false;

}

/**
 *
 */
CheckBox::CheckBox(Rect rect,std::string text,bool checked) : GuiObject(rect),
	m_TextBitmap(0), m_Checked(false), m_Text(""), m_Down(false), m_CheckBoxSize(), m_TextWidth()
{
	m_TextBitmap = 0;

	m_CheckBoxSize = Vector2d(20, 18); //GuiData::checkBoxActivePressed->GetSize();

	m_Rect = Rect(rect.position, m_CheckBoxSize);

	m_Checked = checked;

	setText(text);

	m_MouseOver = false;

}

/**
 *
 */
CheckBox::CheckBox(const CheckBox& source) :
	m_TextBitmap(0), m_Checked(false), m_Text(""), m_Down(false), m_CheckBoxSize(), m_TextWidth()
{
	m_TextBitmap = source.m_TextBitmap;

	m_CheckBoxSize = source.m_CheckBoxSize;

	m_Rect = source.m_Rect;

	m_Checked = source.m_Checked;

	m_Text = source.m_Text;

	m_MouseOver = source.m_MouseOver;
}

/**
 *
 */
CheckBox& CheckBox::operator=(const CheckBox& source)
{
	if (this!=&source) {
		m_TextBitmap = source.m_TextBitmap;

		m_CheckBoxSize = source.m_CheckBoxSize;

		m_Rect = source.m_Rect;

		m_Checked = source.m_Checked;

		m_Text = source.m_Text;

		m_MouseOver = source.m_MouseOver;

	}
	return *this;
}

/**
 *
 */
CheckBox::~CheckBox()
{
	if (m_TextBitmap) {
		delete m_TextBitmap;
		m_TextBitmap = NULL;
	}
}

/**
 *
 */
void CheckBox::draw(const Vector2d& pos,float alpha)
{
	Rect rect = getRect();

	if (m_MouseOver) {
		if (m_Checked) {
			//GuiData::checkBoxActivePressed->Blit(pos+GetRect().position,alpha);
			GuiData::guiData->blit(Rect(20, 18, 20, 18),pos + getRect().position, FlipNone, alpha);
		} else {
			//GuiData::checkBoxActive->Blit(pos+GetRect().position,alpha);
			GuiData::guiData->blit(Rect(20, 0, 20, 18),pos + getRect().position, FlipNone, alpha);
		}
	} else {
		if (m_Checked) {
			//GuiData::checkBoxPressed->Blit(pos+GetRect().position,alpha);
			GuiData::guiData->blit(Rect(0, 18, 20, 18),pos + getRect().position, FlipNone, alpha);
		} else {
			//GuiData::checkBox->Blit(pos+GetRect().position,alpha);
			GuiData::guiData->blit(Rect(0, 0, 20, 18),pos + getRect().position, FlipNone, alpha);
		}
	}

	if (m_TextBitmap) {

		Color col = colorLightGray; //Color(0.75f,0.75f,0.75f,1.0f);;

		if (m_MouseOver) col = colorWhite;

		m_TextBitmap->blitColor(pos + rect.position + Vector2d(m_CheckBoxSize.x, 0) + Vector2d(6, 4), colorBlack, alpha);
		m_TextBitmap->blitColor(pos + rect.position + Vector2d(m_CheckBoxSize.x, 0) + Vector2d(5, 3), col, alpha);
	}
}


/**
 *
 */
bool CheckBox::onLeftMouseButtonPressed(const Vector2d& pos)
{
	bool handled = false;

	GuiObject::onLeftMouseButtonPressed(pos);

	if (m_MouseOver) {
		switchChecked();
		handled = true;
	}

	return handled;
}

/**
 *
 */
bool CheckBox::onLeftMouseButtonReleased(const Vector2d& pos)
{
	bool handled = false;
	GuiObject::onLeftMouseButtonReleased(pos);

	if (m_MouseOver) {
	}

	return handled;
}

/**
 *
 */
void CheckBox::update()
{
	if (!m_Active) {
		m_MouseOver = false;
	}
}

/**
 *
 */
void CheckBox::setText(std::string text)
{
	Rect rect = getRect();

	if (text!="") {
		//SDLBitmap *tempText=GuiData::guiFont->renderText(text,colorWhite);
		//SDLBitmap *tempBackground=NULL;

		//if (tempText!=NULL) {

			//m_TextWidth=tempText->getSize().x;
			/*

			tempBackground=new SDLBitmap(tempText->getSize());

			tempBackground->clearToColor(Color(0.0,0.0,0.0,1.0));

			tempText->blit(tempBackground,Vector2d(0,0));

			m_TextBitmap=new Bitmap(*tempBackground);
			m_TextBitmap->SEND_TO_GPU();


			delete tempText;
			*/
			//tempText=NULL;
			/*
		}
		if (tempBackground) {
			//delete tempBackground;
			//tempBackground=NULL;
		}
		*/

		m_Text = text;

		//m_Rect=Rect(rect.position,m_CheckBoxSize+Vector2d(5,0)+Vector2d(m_TextBitmap->getSize().x,0));

	} else {
		if (m_TextBitmap) {
			delete m_TextBitmap;
			m_TextBitmap = NULL;
		}

		m_Rect = Rect(rect.position, m_CheckBoxSize);
	}
}

/**
 *
 */
bool CheckBox::getChecked() const
{
	return m_Checked;
}

/**
 *
 */
void CheckBox::setChecked(bool checked)
{
	m_Checked = checked;
}

/**
 *
 */
void CheckBox::switchChecked()
{
	m_Checked = !m_Checked;
}

/**
 *
 */
bool CheckBox::handleKeyboardEvent(KeyEvent &event)
{
	return false;
}

// end of namespace
// ----------------
};
