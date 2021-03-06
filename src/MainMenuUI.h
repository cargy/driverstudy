//      MainMenuUI.h
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


#ifndef MAINMENUUI_H
#define MAINMENUUI_H
#include "config.h"
#include "MainMenuUIAbstract.h"
#include "QuestionUI.h"
//#include "Application.h"

class MainMenuUI: public MainMenuUIAbstract
{
	public:
		MainMenuUI(int x, int y, int width, int height, const char* label);
		QuestionUI *qv;
		virtual void cb_start(fltk::Widget* pBtn, const char* tCategory);
		int getSelectedLanguage();
		int getSelectedCategory(const char* tCategory);
				
	private:

		int win_x, win_y, win_w, win_h;
		//bool fullscreen_flag;
		int convLangtoMenuItemIndexNo();
		virtual void cb_exit();
		virtual void cb_help();
		//virtual void cb_fullscreen();
		
		virtual void cb_selectLanguage(fltk::Widget* sItem, void* userdata);
		virtual void cb_soundToggle();
		void changeUILocale(fltk::Group* o);
};

#endif /* MAINMENUUI_H */ 
