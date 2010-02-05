//      MainMenuUI.cxx
//      
//      Copyright 2010 Argyriadis Christos <krizz@Freak>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include "config.h"
#include "MainMenuUI.h"
#include <cstdlib>
#include <fltk/ask.h>
#include <fltk/Menu.h>

MainMenuUI::MainMenuUI(int x, int y, int width, int height, const char* label)
	: MainMenuUIAbstract(x,y,width,height,label)
{
	
}

void MainMenuUI::cb_exit()
{
	if ( fltk::ask(_("Do you want to cancel this Test?")) ) exit(0);
}

void MainMenuUI::cb_help()
{
	fltk::message(_("@c;Driver Study ver.%s\nCopyright(c) 2010\nArgyriadis Christos\nc.argyriadis(at)locusta.gr"), DRIVERSTUDYVERSION );
}

void MainMenuUI::cb_fullscreen()
{
	fullscreen();
	set_modal();
}

void MainMenuUI::cb_start(fltk::Widget* pBtn, const char* tCategory)
{
	
}

void MainMenuUI::cb_selectLanguage(fltk::Widget* sItem, void* userdata)
{
	fltk::Menu* menu = (fltk::Menu*)sItem;
	fltk::Widget* item = menu->get_item();
	fltk::message("Item selected: %s",item->label() );
	
	/* Change language.  */
	#ifdef _WIN32
	putenv("LANGUAGE=el_GR");
	#else
	setenv ("LANGUAGE", "el_GR", 1);
	#endif /* !_WIN32 */
	
	/* Make change known.  */
	{
	  extern int  _nl_msg_cat_cntr;
	  ++_nl_msg_cat_cntr;
	}
}
