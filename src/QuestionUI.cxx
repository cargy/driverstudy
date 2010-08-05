//      QuestionUI.cxx
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


#include "QuestionUI.h"
#include <cstdio>
#include <cassert>
//#include <fltk/ask.h>
#include "dlg.h"
#include <fltk/Image.h>
#include <fltk/SharedImage.h>

#include <cctype>
using namespace std;
#include "MainMenuUI.h"

#ifdef ENABLE_SOUND
#include "DictationSystem.h"
extern DictationSystem* ds;
#endif //ENABLE_SOUND


QuestionUI::QuestionUI(int x, int y, int width, int height, const char* label)
	: QuestionUIAbstract(x,y,width,height,label)
{
	//resizable(this);
	//app = a;
	win_x = 150; win_y = 50; win_w = width; win_h = height;
	fltk::register_images();
}

QuestionUI::~QuestionUI()
{
#ifdef DEBUG
	printf("QuestionUI object Goind down!\n");
#endif
	delete currTest;
	//destroy();
}
	
void QuestionUI::cb_close() 
{
	timer->stop();
	//if ( dlg::ask(_("Do you want to cancel this Test?")) ) wizard->prev();
	//else timer->start();
}
/*
void QuestionUI::fullscreen()
{
	// store last position of window before going fullscreen
	// ONLY if Window is already show or else x(), y() are
	// not set by ftlk::USEDAFAULT yet.
	if ( shown() ) { win_x = x(); win_y = y(); }
	
	win_w = w();
	win_h = h();
	fltk::Window::fullscreen();
	fullscreenBtn->state(true);

}
*/
void QuestionUI::show()
{
	extern bool fullscreen_flag;
	//if (fullscreen_flag) fullscreen();
	soundBtn->value(ds->initialized());
	fltk::Widget::show();
	timer->start();
}
/*
void QuestionUI::fullscreen_off()
{
	fltk::Window::fullscreen_off( win_x, win_y,win_w,win_h);
	fullscreenBtn->state(false);
}
*/
void QuestionUI::cb_timeout()
{
	dlg::alert(_("You are out of time!"));
}

void QuestionUI::cb_soundToggle()
{
	//((MainMenuUI*)child_of())->soundBtn->do_callback();
}

void QuestionUI::cb_fullscreen()
{
	//((MainMenuUI*)child_of())->fullscreenBtn->do_callback();
	//((MainMenuUI*)child_of())->fullscreenBtn->state(!((MainMenuUI*)child_of())->fullscreenBtn->state());
}
	
inline void QuestionUI::cb_answerRB_i(fltk::Widget* o, long v) {
  cb_answerSelected(o,v)
;}
void QuestionUI::cb_answerRB(fltk::Widget* o, long v) {
  ((QuestionUI*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_answerRB_i(o,v);
}


void QuestionUI::cb_questionRelease()
{
	ds->play(currTest->question()->sound());
}
void QuestionUI::cb_answerSelected(fltk::Widget *pRB, long rbId)
{
	if (selectedRB() > -1)
	{
		validateBtn->activate();
		currTest->selectAnswerOfCurrentQuestion(selectedRB());
		ds->play(currTest->question()->answerSound(selectedRB()));
	}
	else validateBtn->deactivate();	
}

void QuestionUI::cb_next(fltk::Widget* pBtn, const char* Btn)
{
	//printf("btn: %s\n",Btn);
	if ( strcmp(Btn, "validate") == 0 ) currTest->verifyAnswerOfCurrentQuestion();	  

	//check if test is completed
	if (currTest->completed() && !preview_mode) 
	{
		timer->stop();
		dlg::message(_("Test Completed!\n\nYou answered correctly:\n%d from %d questions."),currTest->getCorrect(), currTest->size());

		preview_mode = true;
		if ( currTest->getWrong() > 0 ) previewQuestion(currTest->nextWrong());
		else hide();
	}
	// load next question
	else if (preview_mode && !currTest->is_nextWrong() )
	{
		int c = dlg::choice(_("All wrong questions were shown!\n\n"
							   "You can:\n"
							   "- see again the wrong questions [Show me again]\n"
							   "- start a new Test[New Test]\n"
							   "- return to home page [Cancel]\n"),
							   _("Show me again"), _("New Test"),_("Cancel")
							);
		switch (c) 
		{
			case 0:
				// Show me again
				previewQuestion(currTest->nextWrong());
				break;
			case 1:
				// New Test
				switch ( currTest->category_id() )
				{
					case DBCARID:
						//((MainMenuUI*)child_of())->carBtn->do_callback();
						break;
					case DBMOTORCYCLEID:
						//((MainMenuUI*)child_of())->motorcycleBtn->do_callback();
						break;
					case DBTRUCKID:
						//((MainMenuUI*)child_of())->truckBtn->do_callback();
						break;
					case DBBUSID:
						//((MainMenuUI*)child_of())->busBtn->do_callback();
						break;
					case DBSCARID:
						//((MainMenuUI*)child_of())->scarBtn->do_callback();
						break;
					case DBSMOTORCYCLEID:
						//((MainMenuUI*)child_of())->smotorcycleBtn->do_callback();
						break;						
				}
				break;
			case 2:
				// Cacnel
				exitBtn->do_callback();
				break;
		}
	}
	else
	{
		if (!preview_mode )showQuestion(currTest->next());
		else previewQuestion(currTest->nextWrong());
	}
}

int QuestionUI::selectedRB()
{
	for (int i=0; i<4; i++) 
	{
	  if ( answerRB[i]->visible() && answerRB[i]->state() )
		return i;
	}
	return -1;
}

void QuestionUI::showQuestion(Question* q)
{
	// restore setting changed by previewQuestion()
	AnswerGroup->clear_output();
  	if ( !timer->visible() ) timer->show();
  	if ( !validateBtn->visible() ) validateBtn->show();

	char qNo[150];
	sprintf(qNo, _("Question %i/%i"),currTest->cursor()+1,currTest->size());
	//QuestionGroup->copy_label(qNo);
	QuestionGroup->copy_label(qNo);
	QuestionGroup->redraw_label();
	questionDisplay->label(q->title());
	questionDisplay->redraw_label();
	
	createAnswerRB(q->getAOA());

	for (unsigned int i=0; i<q->getAOA(); i++) 
	{
		answerRB[i]->label(q->getAnswer(i));
	}
	answerRB[q->getSelectedAnswer()]->state(true);
#ifdef	DEBUG
	answerRB[q->getCorrectAnswer()]->labelcolor(fltk::color(81,118,17));
	//answerRB[q->getCorrectAnswer()]->buttoncolor((fltk::Color)0xb60000);
#endif
	
	// load question image if available
	if ( strcmp(q->image(), "0") != 0 )
	{
		char imgPath[MAXIMGFILESIZE];
		sprintf(imgPath, "img/%s.jpg",q->image());

		int i = -1;
		// make imgPath lowercase
		while (imgPath[++i]) imgPath[i] = tolower(imgPath[i]);
	#ifdef	DEBUG
		printf("imgPath = %s\n",imgPath);
	#endif
		if ( !imageHolder->visible() ) imageHolder->show();
		imageHolder->image( fltk::SharedImage::get(imgPath) );
		imageHolder->redraw();
	}
	else 
		if ( imageHolder->visible() ) imageHolder->hide();
	
	// check if any answer is selected or if question is already validated
	// to disable/enable validateBtn
	if ( q->getSelectedAnswer() == -1 || q->isVerified()) validateBtn->deactivate();
	else validateBtn->activate();
	
	// check if there is any other un-validated question
	// to disable/enable nextBtn
	if ( currTest->is_next() ) nextBtn->activate();
	else nextBtn->deactivate();
	
	redraw();
	ds->play(currTest->question()->sound());
}

void QuestionUI::createAnswerRB(int no)
{
	AnswerGroup->clear();
  	
	int rb_height = 0;
	int rb_y = 10;
  	const int space = 10;
  	rb_height = ( ( AnswerGroup->h() - (no)* space ) / no ) - 3;

	for (int i=0; i<no; i++) 
	{
		answerRB[i] = new fltk::RadioButton(5,rb_y,AnswerGroup->w()-space,rb_height,"booo");
		answerRB[i]->buttonbox(fltk::RSHADOW_BOX);
		answerRB[i]->labelsize(16);
		answerRB[i]->textsize(16);
		answerRB[i]->callback((fltk::Callback*)cb_answerRB, (void*)(i));
		answerRB[i]->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
		AnswerGroup->add(answerRB[i]);

		rb_y = (answerRB[i]->y() + answerRB[i]->h() + space);
	}
	AnswerGroup->init_sizes();
	
}
void QuestionUI::previewQuestion(Question* q)
{
	AnswerGroup->set_output();
	timer->hide();
	char qNo[150];
    sprintf(qNo, _("Question %i (%s)"),currTest->cursor()+1,q->getBookSection());
    label(qNo);
    QuestionGroup->copy_label(qNo);
    QuestionGroup->redraw_label();
    questionDisplay->label(q->title());
    questionDisplay->redraw_label();
    assert(q->getSelectedAnswer() != q->getCorrectAnswer());
    

  	createAnswerRB(q->getAOA());
    for (unsigned int i=0; i<q->getAOA(); i++) 
    {
		answerRB[i]->label(q->getAnswer(i));
    	answerRB[i]->box(fltk::NO_BOX);
    	answerRB[i]->image(NULL);
    	answerRB[i]->image(fltk::SharedImage::get("icons/wrong_24x24.png"));
    }

    answerRB[q->getSelectedAnswer()]->labelcolor(fltk::color(190,47,10));
    answerRB[q->getCorrectAnswer()]->labelcolor(fltk::color(81,118,17));
    answerRB[q->getCorrectAnswer()]->image(fltk::SharedImage::get("icons/tick_24x24.png"));
    
	// load question image if available
	if ( strcmp(q->image(), "0") != 0 )
	{
		char imgPath[MAXIMGFILESIZE];
		sprintf(imgPath, "img/%s.jpg",q->image());

		int i = -1;
		// make imgPath lowercase
		while (imgPath[++i]) imgPath[i] = tolower(imgPath[i]);
	#ifdef	DEBUG
		printf("imgPath = %s\n",imgPath);
	#endif
		if ( !imageHolder->visible() ) imageHolder->show();
		imageHolder->image( fltk::SharedImage::get(imgPath) );
		imageHolder->redraw();
	}
	else 
		if ( imageHolder->visible() ) imageHolder->hide();
    
	// hide validateBtn we are in preview_mode
	if ( validateBtn->visible() ) validateBtn->hide();
    
    // activate nextBtn because it's probably
    // deactivated from showQuestion()
	if ( !nextBtn->active() ) nextBtn->activate();
	
	redraw();
}

void QuestionUI::setTest(TestModel* t, bool pmode)
{
	currTest = t;
	preview_mode = false;
	
	// set window label
	char tl[100];
	const char* tcl = "";
	if (currTest->category_id() == DBCARID) tcl = _("Car");
	if (currTest->category_id() == DBMOTORCYCLEID) tcl = _("Motorcycle");
	if (currTest->category_id() == DBTRUCKID) tcl = _("Truck");
	if (currTest->category_id() == DBBUSID) tcl = _("Bus");
	if (currTest->category_id() == DBSCARID) tcl = _("Car Special Category");
	if (currTest->category_id() == DBSMOTORCYCLEID) tcl = _("Motorcycle Special Category");
	sprintf(tl, _("Questionnaire %i - %s"),currTest->category_id()%10,tcl);
	copy_label(tl);
	#ifdef DEBUG
	timer->starttime(currTest->time());
	#else
	timer->starttime(currTest->time()*60);
	#endif
	timer->warningtime(timer->starttime()*0.25);
	// show first question
	showQuestion(currTest->next());
}
