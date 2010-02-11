//      driverstudy.cxx
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
#include <clocale>
#include <libintl.h>

#include <fltk/Window.h>
#include <fltk/Widget.h>
#include <fltk/run.h>
#ifdef DEBUG
#include <fltk/ask.h>
#endif
#include <fltk/error.h>

#include <cstdio>
#include <cstdlib>
#include "MainMenuUI.h"


bool fullscreen_flag=false;

void force_locale(const char* f_locale)
{
	/* Change language.  */
	#ifdef _WIN32
	char buffer [15];
	sprintf (buffer, "LANGUAGE=%s", f_locale);
	putenv(buffer);
	#else
	setenv ("LANGUAGE", f_locale, 1);
	#endif /* !_WIN32 */

	/* Make change known.  */
	{
	extern int  _nl_msg_cat_cntr;
	++_nl_msg_cat_cntr;
	}
}

int handle_args(int argc, char** argv, int&i){
	
	if (strcmp(argv[i],"-f")==0 || strcmp(argv[i],"-fullscreen")==0 )
	{
		#ifdef DEBUG
		printf("fullscreen mode enabled by arg = %s\n",argv[i]);
		#endif
		fullscreen_flag = true;
		return ++i;
	}
	if (strcmp(argv[i],"-l")==0 || strcmp(argv[i],"-locale")==0 ) 
	{
	   if (i >= argc -1 || argv[i+1][0]=='-') return 0;
	   //printf("argv[%d][0]= %c\n",i+1,argv[i+1][0]);
	   i++;
	   #ifdef DEBUG
	   printf("locale = %s\n",argv[i]);
	   #endif
	   force_locale(argv[i]);
	   i++;
	   return i;
	}
   
  return 0;
}

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
	#ifdef DEBUG
	fltk::message("LANG=%s\nLC_MESSAGES=%s\nLC_ALL=%s\nLANGUAGE=%s\nWe take=%s",
		getenv("LANG"),setlocale (LC_MESSAGES, NULL),setlocale (LC_ALL, NULL),getenv("LANGUAGE"),default_test_language);
	#endif
	return default_test_language;
}


int main(int argc, char** argv)
{
	// Initial global objects.
	
	// read locale from enviroment
	setlocale (LC_ALL, "");
	int i;
	if ( fltk::args(argc, argv, i, handle_args) < argc ) {
		#ifdef DEBUG
		fprintf(stderr,"args return %d (%d)\n",i,argc);
		#endif
		fltk::fatal("%s\n -l[ocale] uilocale\n -f[ullscreen]\n", fltk::help);
	}
	
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);
    
    char applicationTitle[50];
    sprintf(applicationTitle, "%s %s", APPLICATIONTITLE, DRIVERSTUDYVERSION);
	MainMenuUI *window = new MainMenuUI(fltk::USEDEFAULT, fltk::USEDEFAULT,640,480,applicationTitle);
	
	// if fullscreen requested by command line
	if (fullscreen_flag) { window->fullscreenBtn->do_callback(); window->fullscreenBtn->state(true);}
	window->show(argc, argv);
	
	return fltk::run();
};
