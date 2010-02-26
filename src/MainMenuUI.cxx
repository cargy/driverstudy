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
#include <fltk/run.h>
#include <fltk/Image.h>
#include <fltk/SharedImage.h>
#include "question.h"
#include "test.h"
#include "sqlite3.cxx"
#include "QuestionUI.h"

MainMenuUI::MainMenuUI(int x, int y, int width, int height, const char* label)
	: MainMenuUIAbstract(x,y,width,height,label)
{
	appTitle->label(APPLICATIONTITLE);
	resizable(this);
	win_x = 100; win_y = 100;
	win_w = width; win_h = height;
	// set defaut value of languagePUM
	languagePUM->value(convLangtoMenuItemIndexNo());
	languagePUM->label(languagePUM->get_item()->label());
	extern bool fullscreen_flag;
	if (fullscreen_flag) { fullscreen_flag=false;fullscreenBtn->do_callback(); fullscreenBtn->state(true);}
	
	fltk::register_images();
	motorcycleBtn->image( fltk::SharedImage::get("icons/motorcycle_256x182.png") );
	//motorcycleBtn->align(fltk::ALIGN_CLIP);
    motorcycleBtn->align((fltk::RESIZE_FIT | fltk::ALIGN_INSIDE));
    
    carBtn->image( fltk::SharedImage::get("icons/car_256x182.png") );
	//carBtn->align(fltk::ALIGN_CLIP);
    carBtn->align((fltk::RESIZE_FIT | fltk::ALIGN_INSIDE));

    truckBtn->image( fltk::SharedImage::get("icons/truck_256x182.png") );
	//truckBtn->align(fltk::ALIGN_CLIP);
    truckBtn->align((fltk::RESIZE_FIT | fltk::ALIGN_INSIDE));
	
	busBtn->image( fltk::SharedImage::get("icons/bus_256x182.png") );
	//truckBtn->align(fltk::ALIGN_CLIP);
    busBtn->align((fltk::RESIZE_FIT | fltk::ALIGN_INSIDE));
    
    smotorcycleBtn->image( fltk::SharedImage::get("icons/motorcycle_256x182.png") );
	//motorcycleBtn->align(fltk::ALIGN_CLIP);
    smotorcycleBtn->align((fltk::RESIZE_FIT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP));
    
    scarBtn->image( fltk::SharedImage::get("icons/car_256x182.png") );
	//carBtn->align(fltk::ALIGN_CLIP);
    scarBtn->align((fltk::RESIZE_FIT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP));
}

int MainMenuUI::convLangtoMenuItemIndexNo() {
	extern char* getUILanguage();
	const char* lang = getUILanguage();
	
	if ( strcmp(lang,"el") == 0 || strcmp(lang,"Greek") == 0 ) return 0;
	else if ( strcmp(lang,"en") == 0 || strcmp(lang,"English") == 0 ) return 1;
	else if ( strcmp(lang,"ru") == 0 || strcmp(lang,"Russian") == 0 ) return 2;
	else if ( strcmp(lang,"sq") == 0 || strcmp(lang,"Albanian") == 0 ) return 3;
	else return 0;
	
}

void MainMenuUI::cb_exit()
{
	if ( fltk::ask(_("Do you want to cancel this Test?")) ) exit(0);
}

void MainMenuUI::cb_help()
{
	fltk::message(_("@c;%s ver. %s\nCopyright(c) 2010\nArgyriadis Christos\nc.argyriadis@@locusta.gr"), APPLICATIONTITLE,DRIVERSTUDYVERSION );
}

void MainMenuUI::cb_fullscreen()
{
	extern bool fullscreen_flag;
	
	if (fullscreen_flag) 
	{
		fullscreen_off( win_x, win_y, win_w, win_h);
		if (qv) qv->fullscreen_off();
	}
	else 
	{
		// store last position of window before going fullscreen
		// ONLY if Window is already show or else x(), y() are
		// not set by ftlk::USEDAFAULT yet.
		if ( shown() ) { win_x = x(); win_y = y(); }
		
		win_w = w();
		win_h = h();
		fullscreen();
		if (qv) qv->fullscreen(); 
	}
	fullscreen_flag = !fullscreen_flag; 
	
}

void MainMenuUI::cb_start(fltk::Widget* pBtn, const char* tCategory)
{
	statusBar->label("Creating Test...");
	deactivate();
	fltk::check();
	//fltk::message("Starting %s Test in %s",tCategory, languagePUM->get_item()->label() );
	//fltk::message("languagePUM->item->userdata() == %s",languagePUM->get_item()->user_data() );
	SQLITE3 sql(DATABASE);
	int catid = 0;
	if (strcmp(tCategory, "car")==0) catid = DBCARID;
	if (strcmp(tCategory, "motorcycle")==0) catid = DBMOTORCYCLEID;
	if (strcmp(tCategory, "truck")==0) catid = DBTRUCKID;
	if (strcmp(tCategory, "bus")==0) catid = DBBUSID;
	if (strcmp(tCategory, "scar")==0) catid = DBSCARID;
	if (strcmp(tCategory, "smotorcycle")==0) catid = DBSMOTORCYCLEID;
	assert(catid>0);
	
	int langid = 0;
	const char* slang = (const char*)languagePUM->get_item()->user_data();
	
	if (strcmp(slang,"greek") == 0) langid = DBGREEKID;
	if (strcmp(slang,"english") == 0 ) langid = DBENGLISHID;
	if (strcmp(slang,"russian") == 0) langid = DBRUSSIAN;
	if (strcmp(slang,"albanian") == 0) langid = DBALBANIANID;
	assert(langid>0);
	
	//if (qv) delete qv;
	vector<int> *v = sql.testTemplate(catid,langid);
	
	int *array = sql.createRandomTestFromTemplate(v);
	
	Test* ct = sql.getTest(array);
	fltk::check();
	
	#ifdef DEBUG
	ct->answerRandomly();
	#endif
	
	qv = new QuestionUI(fltk::USEDEFAULT,fltk::USEDEFAULT,800,600,"You should never see this! But shit always can happen :(");
	qv->setTest(ct);
	//qv->show_inside(this);
	qv->child_of(this);
	qv->show();
	activate();
	statusBar->label("Test created Successfully!");
}

// debrecated method
// it was supposed to update the provided fltk::Group
// and it's childs label to languagePUM selected language
// using gettext
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
	
	// set languagePUM label to selected item label
	menu->label(item->label());
	
	//fltk::message("Item selected: %s->%s",menu->label(),item->user_data() );
	//fltk::message("Item selected: %s->%s\n LANG= %s\nLC_ALL= %s\nLC_MESSAGES = %s\n LANGUAGE= %s\n gettext Domain=%s\n",
	//	menu->label(),menu->user_data(),getenv( "LANG" ),setlocale( LC_ALL, NULL ), setlocale( LC_MESSAGES, NULL ),getenv("LANGUAGE"),textdomain(NULL) );
	


	//changeUILocale(mainContainer);
}
