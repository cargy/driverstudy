//      main.cxx
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


#include <iostream>

#include "config.h"
#include <fltk/run.h>
#include <fltk/visual.h>
#include <locale.h>
#include <libintl.h>
#include "question.h"
#include "test.h"
#include "QuestionView.h"
#include "sqlite3.cxx"


using namespace std;

int main(int argc, char** argv)
{
	setlocale (LC_ALL, "");
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);
    
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


	// Initial global objects.
	fltk::args(argc, argv);

	SQLITE3 sql("ExerBase.db");

	vector<int> *v = sql.testTemplate(1,1);
	int *array = sql.createRandomTestFromTemplate(v);

	Test *ct = sql.getTest(array);

	ct->answerRandomly();
	QuestionView qvui;
	qvui.setTest(ct);
	qvui.show();
    
    return fltk::run();
}
