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
#include <fltk/ask.h>
#include <fltk/Image.h>
#include <fltk/SharedImage.h>


QuestionUI::QuestionUI()
	: QuestionUIAbstract()
{
	win_x = 0; win_y = 0;
	fullscreen_flag = false;
	fltk::register_images();

}

QuestionUI::~QuestionUI()
{
	printf("QuestionUI object Goind down!\n");
	delete currTest;
	mainWindow->destroy();
}

void QuestionUI::show()
{
	mainWindow->show();
}
	
void QuestionUI::cb_close() 
{
	if ( fltk::ask(_("Do you want to cancel this Test?")) ) mainWindow->hide();
}

void QuestionUI::cb_fullscreen()
{

	if (this->fullscreen_flag) 
	{
		mainWindow->fullscreen_off( win_x, win_y,win_w,win_h);
		mainWindow->set_non_modal();
	}
	else 
	{
		win_x = mainWindow->x();
		win_y = mainWindow->y();
		win_w = mainWindow->w();
		win_h = mainWindow->h();
		mainWindow->fullscreen();
		mainWindow->set_modal();
	}
	  
	if (fullscreen_flag) fullscreen_flag=false;
	else fullscreen_flag=true;
}
	
void QuestionUI::cb_answerSelected(fltk::Widget *pRB, long rbId)
{
	if (selectedRB() > -1)
	{
		validateBtn->activate();
		currTest->selectAnswerOfCurrentQuestion(selectedRB());
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
		fltk::message(_("Test Completed!\n\nYou answered correctly:\n%d from %d questions."),currTest->getCorrect(), currTest->size());

		preview_mode = true;
		previewQuestion(currTest->next());    
	}
	// load next question
	else 
	{
		if (!preview_mode )showQuestion(currTest->next());  //Question *q = currTest->next();
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
	
	char qNo[150];
	sprintf(qNo, _("Question %i/%i"),currTest->cursor()+1,currTest->size());
	questionDisplay->copy_label(qNo);
	questionDisplay->text(q->title());

	// reset answer buttons
	for (unsigned int i=0; i<4; i++) {
	answerRB[i]->state(false);
	answerRB[i]->labelcolor((fltk::Color)56);
	if ( i >= q->getAOA() ) answerRB[i]->hide();
	else answerRB[i]->show();

	}

	for (unsigned int i=0; i<q->getAOA(); i++) 
	{
	answerRB[i]->label(q->getAnswer(i));
	}
	answerRB[q->getSelectedAnswer()]->state(true);
	answerRB[q->getCorrectAnswer()]->labelcolor((fltk::Color)0xff00);
	//resizeAnswers(q->getAOA());

	char imgPath[MAXIMGFILESIZE];
	sprintf(imgPath, "img/%s.jpg",q->image());
	locale loc;
	use_facet< ctype<char> >(loc).tolower ( imgPath, imgPath+sizeof(imgPath) );
	//cout << imgPath <<endl;
	imageHolder->image( fltk::SharedImage::get(imgPath) );
	imageHolder->redraw();
	mainWindow->redraw();
	
	// check if any answer is selected or if question is already validated
	// to disable/enable validateBtn
	if ( q->getSelectedAnswer() == -1 || q->isVerified()) validateBtn->deactivate();
	else validateBtn->activate();
	
	// check if there is any other un-validated question
	// to disable/enable nextBtn
	if ( currTest->is_next() ) nextBtn->activate();
	else nextBtn->deactivate();
	
}

void QuestionUI::previewQuestion(Question* q)
{
	char qNo[150];
    sprintf(qNo, _("Question %i (%s)"),currTest->cursor()+1,q->getBookSection());
    mainWindow->label(qNo);
    questionDisplay->copy_label(qNo);
    questionDisplay->text(q->title());
    
    // reset answer buttons
    for (unsigned int i=0; i<4; i++) {
    	answerRB[i]->state(false);
    	answerRB[i]->labelcolor((fltk::Color)56);
    	if ( i >= q->getAOA() ) answerRB[i]->hide();
    	else answerRB[i]->show();
    	
    }
     
    for (unsigned int i=0; i<q->getAOA(); i++) 
    {
    	answerRB[i]->label(q->getAnswer(i));
    }
    answerRB[q->getSelectedAnswer()]->state(true);
    answerRB[q->getCorrectAnswer()]->labelcolor((fltk::Color)0xff00);
    //resizeAnswers(q->getAOA());
    
    char imgPath[MAXIMGFILESIZE];
    sprintf(imgPath, "img/%s.jpg",q->image());
    locale loc;
    use_facet< ctype<char> >(loc).tolower ( imgPath, imgPath+sizeof(imgPath) );
    //cout << imgPath <<endl;
    imageHolder->image( fltk::SharedImage::get(imgPath) );
    imageHolder->redraw();
    mainWindow->redraw();
    
	// hide validateBtn we are in preview_mode
	if ( validateBtn->visible() ) validateBtn->hide();
    
    // activate nextBtn because it's probably
    // deactivated from showQuestion()
	if ( !nextBtn->active() ) nextBtn->activate();

}

void QuestionUI::setTest(Test* t, bool pmode)
{
	currTest = t;
	preview_mode = false;
	
	// set window label
	char tl[50];
	char* tcl;
	if (currTest->category_id() == DBCARID) tcl = _("Car");
	if (currTest->category_id() == DBMOTORCYCLEID) tcl = _("Motorcycle");
	if (currTest->category_id() == DBTRUCKID) tcl = _("Truck");
	if (currTest->category_id() == DBBUSID) tcl = _("Bus");
	sprintf(tl, _("Questionnaire %i - %s"),currTest->category_id(),tcl);
	mainWindow->copy_label(tl);
	
	// show first question
	showQuestion(currTest->next());
}

void QuestionUI::resizeAnswers(int no)
{
	int rb_height = 0;
  	const int space = 2;
  	//int no = q->getAOA();
  	rb_height = ( ( AnswerGroup->h() - (no)* space ) / no ) - 3;
  	answerRB[0]->set_y(1);
  	answerRB[0]->h(rb_height);
  	for (int i = 1; i <=no; i++ ) 
  	{
  		answerRB[i]->h(rb_height);
  		answerRB[i]->y( answerRB[i-1]->y() + answerRB[i-1]->h() + space  ); 
  	}
  	//AnswerGroup->redraw();
}