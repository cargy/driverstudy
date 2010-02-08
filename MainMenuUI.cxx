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
#include "question.h"
#include "test.h"
#include "sqlite3.cxx"
#include "QuestionView.h"

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
	fltk::message(_("@c;Driver Study ver.%s\nCopyright(c) 2010\nArgyriadis Christos\nc.argyriadis@@locusta.gr"), DRIVERSTUDYVERSION );
}

void MainMenuUI::cb_fullscreen()
{
	fullscreen();
	set_modal();
}

void MainMenuUI::cb_start(fltk::Widget* pBtn, const char* tCategory)
{
	//fltk::message("Starting %s Test in %s",tCategory, languagePUM->get_item()->label() );
	//fltk::message("languagePUM->item->userdata() == %s",languagePUM->get_item()->user_data() );
	SQLITE3 sql(DATABASE);
	int catid = 0;
	if (strcmp(tCategory, "car")==0) catid = DBCARID;
	if (strcmp(tCategory, "motorcycle")==0) catid = DBMOTORCYCLEID;
	if (strcmp(tCategory, "track")==0) catid = DBTRUCKID;
	if (strcmp(tCategory, "bus")==0) catid = DBBUSID;
	assert(catid>0);
	
	int langid = 0;
	const char* slang = (const char*)languagePUM->get_item()->user_data();
	
	if (strcmp(slang,"greek") == 0) langid = DBGREEKID;
	if (strcmp(slang,"english") == 0 ) langid = DBENGLISHID;
	if (strcmp(slang,"russian") == 0) langid = DBRUSSIAN;
	if (strcmp(slang,"albanian") == 0) langid = DBALBANIANID;
	assert(langid>0);

	vector<int> *v = sql.testTemplate(catid,langid);
	int *array = sql.createRandomTestFromTemplate(v);

	Test* ct = sql.getTest(array);

	ct->answerRandomly();
	if (qv) delete qv;
	qv = new QuestionView();
	qv->setTest(ct);
	//qv->mainWindow->show_inside(this);
	qv->mainWindow->child_of(this);
	qv->show();
	
}


void MainMenuUI::changeUILocale(fltk::Group* o)
{

    for (int index = o->children(); index--;) {
		fltk::Widget* cd = o->child(index);
		if (  cd->is_group() ) 
			if ( ((fltk::Group*)(cd))->children() > 0 )
				changeUILocale((fltk::Group*)(o)->child(index));
				
		printf("label[%d]:%s - _(%s) - N_(%s)\n",index,o->child(index)->label(),_(o->child(index)->label()),N_(o->child(index)->label()));
		cd->label(_(o->child(index)->label()));
		cd->redraw_label();
	}
  

}


void MainMenuUI::cb_selectLanguage(fltk::Widget* sItem, void* userdata)
{
	fltk::Menu* menu = (fltk::Menu*)sItem;
	fltk::Widget* item = menu->get_item();
	//fltk::message("Item selected: %s->%s",menu->label(),item->user_data() );
	menu->label(item->label());
	
	const char* slang = (const char*)item->user_data();
	
	const char* langLOCALE = "el_GR";
	if (strcmp(slang,"greek") == 0) langLOCALE = "el_GR";
	if (strcmp(slang,"english") == 0 ) langLOCALE = "en_US";
	/* Change language.  */
	#ifdef _WIN32
	putenv("LANGUAGE=el_GR");
	#else
	setenv ("LANGUAGE", langLOCALE, 1);
	#endif /* !_WIN32 */
	
	/* Make change known.  */
	{
	  extern int  _nl_msg_cat_cntr;
	  ++_nl_msg_cat_cntr;
	}
	//changeUILocale(mainContainer);
}
