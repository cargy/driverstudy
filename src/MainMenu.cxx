//      MainMenu.cxx
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

#include <fltk/Window.h>
#include <fltk/Widget.h>
#include <fltk/run.h>
#include <locale.h>
#include <libintl.h>
#include "MainMenuUI.h"
#include "config.h"

/* try to determine the ui locale
 * respecting the bellow order as gettext
 * 1. LANGUAGE
 * 2. LC_ALL
 * 3. LC_xxx, according to selected locale category: LC_CTYPE, LC_NUMERIC, LC_TIME, LC_COLLATE, LC_MONETARY, LC_MESSAGES, ...
 * 4. LANG 
 * 
 * returns only the language only (truncates before _)
*/
const char* getUILanguage() {
	char* default_test_language;
	
	if ( getenv("LANG") )default_test_language = getenv("LANG");
	if ( setlocale (LC_MESSAGES, NULL) ) default_test_language = setlocale (LC_MESSAGES, NULL);
	if ( setlocale (LC_ALL, NULL) ) 
	{
		if ( setlocale (LC_MESSAGES, NULL) ) default_test_language = setlocale (LC_MESSAGES, NULL);
		else default_test_language = setlocale (LC_ALL, NULL);
	}
	if ( getenv("LANGUAGE") ) default_test_language = getenv("LANGUAGE");
	
	strtok(default_test_language, "_" );
	
	return default_test_language;
}

int main(int argc, char** argv)
{
	setlocale (LC_ALL, "");
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);
    
	MainMenuUI *window = new MainMenuUI(300, 180,640,480,"Driver Study 0.6");
	window->resizable(window);
	window->show();
	return fltk::run();

}
