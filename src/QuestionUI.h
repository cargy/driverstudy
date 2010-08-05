//      QuestionUI.h
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


#ifndef QUESTIONUI_H
#define QUESTIONUI_H
#include "config.h"
#include "QuestionUIAbstract.h"
#include "question.h"
#include "test.h"

class QuestionUI: public QuestionUIAbstract
{
	public:
		QuestionUI(int x, int y, int width, int height, const char* label);
		~QuestionUI();
		virtual void cb_close();
		//void fullscreen();
		//void fullscreen_off();
		virtual void cb_fullscreen();
		virtual void cb_answerSelected(fltk::Widget *pRB, long rbId);
		virtual void cb_next(fltk::Widget* pBtn, const char* Btn);
		virtual void cb_timeout();
		virtual void cb_questionRelease();
		virtual void cb_soundToggle();
		int selectedRB();
		void showQuestion(Question* q);
		void previewQuestion(Question* q);
		void setTest(TestModel* t, bool pmode=false);
		void show();
		
			
	private:
//		Application *app;
		int win_x, win_y, win_w, win_h;
		//bool fullscreen_flag;
		//fltk::WizardGroup *wizard;
		TestModel* currTest;
		bool preview_mode;
		inline void cb_answerRB_i(fltk::Widget*, long);
		static void cb_answerRB(fltk::Widget*, long);
		void createAnswerRB(int no);
		
};

#endif /* QUESTIONUI_H */ 
