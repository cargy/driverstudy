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
#include <locale.h>
#include <libintl.h>

#include <fltk/Window.h>
#include <fltk/Widget.h>
#include <fltk/run.h>

#include <cstdio>
#include <cstdlib>
#include "MainMenuUI.h"
#include "QuestionView.h"

void force_locale(const char* f_locale)
{
	/* Change language.  */
	#ifdef _WIN32
	char buffer [15];
	n=sprintf (buffer, "LANGUAGE=%s", f_locale);
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

int set_locale(int argc, char** argv, int&i){

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

int main(int argc, char** argv)
{
	// Initial global objects.
	
	// read locale from enviroment
	setlocale (LC_ALL, "");
	
	int i;
	if ( fltk::args(argc, argv, i, set_locale) < argc ) {
		#ifdef DEBUG
		fprintf(stderr,"args return %d (%d)\n",i,argc);
		#endif
		fprintf(stderr, "%s\n -l[ocale] uilocale\n", fltk::help);
		return 1;
	}
	
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);
    

	MainMenuUI *window = new MainMenuUI(fltk::USEDEFAULT, fltk::USEDEFAULT,640,480,"Driver Study 0.6");
	window->show(argc, argv);
	
	return fltk::run();
};
