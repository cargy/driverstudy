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
#include <fltk/WizardGroup.h>
#include <fltk/StatusBarGroup.h>
#include <fltk/run.h>
#include "dlg.h"
#include <fltk/error.h>
#include <fltk/x.h>

#include "DictationSystem.h"
#include <cstdio>
#include <cstdlib>

bool fullscreen_flag=false;

#include "MainMenuUI.h"

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
	char* default_test_language = ((char*)"el");
	
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
	dlg::message("LANG=%s\nLC_MESSAGES=%s\nLC_ALL=%s\nLANGUAGE=%s\nWe take=%s",
		getenv("LANG"),setlocale (LC_MESSAGES, NULL),setlocale (LC_ALL, NULL),getenv("LANGUAGE"),default_test_language);
	#endif
	return default_test_language;
}

DictationSystem* ds;

fltk::WizardGroup *wiz;
fltk::Window *window;

MainMenuUI *menu;
QuestionUI *qv;


// this include are for createTest and will be moved to persistance some
// day
#include "test.h"
#include "sqlite3.cxx"
Test* createTest(int catid, int langid) {
	SQLITE3 sql(DATABASE);
	//catid = DBCARID;

	assert(catid>0);
	
	//if (qv) delete qv;
	vector<int> *v;
	vector<int> alangs = sql.availableLanguages(catid);

	v = sql.testTemplate(catid,langid);
	
	int *array = sql.createRandomTestFromTemplate(v);
	
	Test* ct = sql.getTest(array);
	return ct;
}

void back_cb(Widget*, void*) { wiz->prev(); }

void next_cb(fltk::Widget* pBtn, void* tCategory) {
	const char* selectedCategory = (const char*)tCategory;
	qv->setTest(createTest(menu->getSelectedCategory(selectedCategory),menu->getSelectedLanguage()));
	wiz->next(); 
}

void fullscreen_cb(Widget* pWdg, void*)
{
	window->init_sizes();
	fltk::Button *pBtn = (fltk::Button*)pWdg;
	if (!pBtn->state())
		window->fullscreen_off(0,0,800,600);
	else
		window->fullscreen();

}

void cb_exit(fltk::Widget*, void*)
{
	if ( dlg::ask(_("Are you sure you want to quit?")) ) window->hide();//exit(0);
}

int main(int argc, char** argv)
{
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
    
    // initialize dlg windows parameters
	#ifdef TOUCHSCREEN
	dlg::format(90,80, APPLICATIONTITLE,dlg::POS_MONITOR_CENTER);
	#else
	dlg::format(75,30, APPLICATIONTITLE,dlg::POS_BUTTON_HOTSPOT);
	dlg::position(dlg::POS_BUTTON_HOTSPOT);
	#endif
	//fltk::Button::default_style->labelsize_ = 35;
	dlg::no = _("&No");
	dlg::yes= _("&Yes");
	dlg::ok = _("&OK");
	dlg::cancel= _("&Cancel");

    ds = new DictationSystem();
    
    
    char applicationTitle[50];
    sprintf(applicationTitle, "%s %s", APPLICATIONTITLE, DRIVERSTUDYVERSION);
	//MainMenuUI *window = new MainMenuUI(fltk::USEDEFAULT, fltk::USEDEFAULT,640,480,applicationTitle);
	window = new fltk::Window(fltk::USEDEFAULT, fltk::USEDEFAULT,800,600,applicationTitle);
	//window->icon((char *)LoadIcon(fltk::xdisplay, MAKEINTRESOURCE(101)));

	window->callback(cb_exit);
	//window->exitBtn->callback(cb_exit);

	
	wiz = new fltk::WizardGroup(0,0,800, 580);
	
	menu = new MainMenuUI(0, 0,800,580,applicationTitle);
	
	wiz->add(menu->mainContainer);
	
	qv = new QuestionUI(fltk::USEDEFAULT,fltk::USEDEFAULT,800,580,"You should never see this! But shit always can happen :(");
	qv->exitBtn->callback(back_cb);
	wiz->add(qv->mainContainer);
	menu->carBtn->callback(next_cb);
	menu->motorcycleBtn->callback(next_cb);
	menu->truckBtn->callback(next_cb);
	menu->busBtn->callback(next_cb);
	menu->fullscreenBtn->callback(fullscreen_cb);

	window->add(wiz);
	//wiz->resizable();
	window->resizable(wiz);
	fltk::StatusBarGroup* statusBar = new fltk::StatusBarGroup(20);
	statusBar->label("Hello!");
	window->add(statusBar);
	window->show(argc, argv);
	
	//menu->show();
	//Application *app = new Application();
	//app->show();
	
#ifdef _WIN32
	HANDLE bigicon = LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(101), IMAGE_ICON, 32, 32, 0);
	SendMessage(xid(window), WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(bigicon));
	HANDLE smallicon = LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(101), IMAGE_ICON, 16, 16, 0);
	SendMessage(xid(window), WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(smallicon));
#endif
	// if fullscreen requested by command line
	//if (fullscreen_flag) { window->fullscreenBtn->do_callback(); window->fullscreenBtn->state(true);}	
	return fltk::run();
};
