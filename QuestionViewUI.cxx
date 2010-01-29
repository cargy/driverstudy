// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "QuestionViewUI.h"
#include <fltk/ask.h>
#include <fltk/Image.h>
#include <fltk/SharedImage.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale>

inline void QuestionViewUI::cb_answerRB_i(fltk::RadioButton*, void*) {
  if (selectedRB() > -1) validateBtn->activate();
  else validateBtn->deactivate();
}
void QuestionViewUI::cb_answerRB(fltk::RadioButton* o, void* v) {
  ((QuestionViewUI*)(o->parent()->parent()->parent()->parent()->parent()->user_data()))->cb_answerRB_i(o,v);
}

inline void QuestionViewUI::cb_exitBtn_i(fltk::Button*, void*) {
  if (fltk::ask("Do you want to quit?")) exit(0);
}
void QuestionViewUI::cb_exitBtn(fltk::Button* o, void* v) {
  ((QuestionViewUI*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_exitBtn_i(o,v);
}

inline void QuestionViewUI::cb_fullscreenBtn_i(fltk::Button*, void*) {
  if (this->fullscreen_flag) 
  {
      mainWindow->fullscreen_off( win_x, win_y,800,600);
      mainWindow->set_non_modal();
  }
  else 
  {
      win_x = mainWindow->x();
      win_y = mainWindow->y();
      mainWindow->fullscreen();
      mainWindow->set_modal();
      
  }
    
  if (fullscreen_flag) fullscreen_flag=false;
  else fullscreen_flag=true;
}
void QuestionViewUI::cb_fullscreenBtn(fltk::Button* o, void* v) {
  ((QuestionViewUI*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_fullscreenBtn_i(o,v);
}

inline void QuestionViewUI::cb_validateBtn_i(fltk::Button* o, void*) {
  nextBtn->do_callback(o);
}
void QuestionViewUI::cb_validateBtn(fltk::Button* o, void* v) {
  ((QuestionViewUI*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_validateBtn_i(o,v);
}

inline void QuestionViewUI::cb_nextBtn_i(fltk::Button* o, void*) {
  // get user input answer
  currTest->selectAnswerOfCurrentQuestion(selectedRB());
  
  // validate the answer of current question
  if ( strcmp(o->label(), "Validate Answer  @+1+") == 0 ) currTest->verifyAnswerOfCurrentQuestion();	  
  
  //check if test is completed
  if (currTest->completed()) 
  {
    fltk::message("Απαντήσατε:\n%d από τις %d ερωτήσεις σωστά.",currTest->getCorrect(), currTest->size());
    
    Test *w = new Test(currTest->wrongQuestions(),currTest->size()-currTest->getCorrect(),35);
    w->showResults();
    setTest(w);
  }
  // load next question
  else 
  showQuestion(currTest->next());  //Question *q = currTest->next();
}
void QuestionViewUI::cb_nextBtn(fltk::Button* o, void* v) {
  ((QuestionViewUI*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_nextBtn_i(o,v);
}

QuestionViewUI::QuestionViewUI() {
  fltk::Window* w;
  
  {
fltk::Window* o = mainWindow = new fltk::Window(800, 600);
    w = o;
    o->shortcut(0xff1b);
    o->user_data((void*)(this));
    o->begin();
    
    {
fltk::Group* o = new fltk::Group(0, 0, 800, 600);
      o->begin();
      
      {
fltk::Group* o = LeftGroup = new fltk::Group(5, 5, 450, 590);
        o->set_vertical();
        o->box(fltk::THIN_DOWN_BOX);
        o->begin();
        
        {
fltk::Group* o = QuestionGroup = new fltk::Group(5, 5, 440, 465);
          o->set_vertical();
          o->box(fltk::THIN_UP_BOX);
          o->begin();
          
          {
fltk::TextDisplay* o = questionDisplay = new fltk::TextDisplay(5, 20, 430, 130, "Question #/#");
            o->labeltype(fltk::ENGRAVED_LABEL);
            o->labelsize(18);
            o->textsize(16);
            o->align(fltk::ALIGN_TOP);
            o->wrap_mode(true);
          }
          
          {
fltk::Group* o = AnswerGroup = new fltk::Group(5, 155, 430, 305);
            o->box(fltk::THIN_DOWN_BOX);
            o->begin();
            
            {
fltk::RadioButton* o = answerRB[0] = new fltk::RadioButton(5, 1, 420, 75, "Answer 0");
              o->buttonbox(fltk::BORDER_BOX);
              o->labelsize(16);
              o->textsize(16);
              o->callback((fltk::Callback*)cb_answerRB);
              o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
            }
            
            {
fltk::RadioButton* o = answerRB[1] = new fltk::RadioButton(5, 77, 420, 75, "Answer 1");
              o->buttonbox(fltk::BORDER_BOX);
              o->labelsize(16);
              o->textsize(16);
              o->callback((fltk::Callback*)cb_answerRB);
              o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
            }
            
            {
fltk::RadioButton* o = answerRB[2] = new fltk::RadioButton(5, 153, 420, 75, "Answer 2");
              o->buttonbox(fltk::BORDER_BOX);
              o->labelsize(16);
              o->textsize(16);
              o->callback((fltk::Callback*)cb_answerRB);
              o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
            }
            
            {
fltk::RadioButton* o = answerRB[3] = new fltk::RadioButton(5, 229, 420, 75, "Answer 3");
              o->buttonbox(fltk::BORDER_BOX);
              o->labelsize(16);
              o->textsize(16);
              o->callback((fltk::Callback*)cb_answerRB);
              o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
            }
            o->end();
          }
          o->end();
        }
        
        {
fltk::Group* o = MainControlsGroup = new fltk::Group(5, 475, 440, 110);
          o->box(fltk::THIN_UP_BOX);
          o->begin();
          
          {
fltk::Button* o = exitBtn = new fltk::Button(10, 15, 115, 80, "Exit");
            o->labelfont(fltk::HELVETICA_BOLD);
            o->callback((fltk::Callback*)cb_exitBtn);
          }
          
          {
fltk::Button* o = fullscreenBtn = new fltk::Button(165, 15, 115, 80, "Fullscreen");
            o->labelfont(fltk::HELVETICA_BOLD);
            o->labelsize(14);
            o->callback((fltk::Callback*)cb_fullscreenBtn);
          }
          
          {
fltk::Button* o = auxBtn = new fltk::Button(315, 15, 115, 80, "Aux");
            o->labelfont(fltk::HELVETICA_BOLD);
            o->labelsize(14);
            o->deactivate();
          }
          o->end();
        }
        o->end();
        fltk::Group::current()->resizable(o);
      }
      
      {
fltk::Group* o = RightGroup = new fltk::Group(455, 5, 340, 590);
        o->set_vertical();
        o->box(fltk::THIN_DOWN_BOX);
        o->begin();
        imageHolder = new fltk::Widget(5, 5, 330, 300);
        
        {
fltk::Group* o = QuestionControlsGroup = new fltk::Group(5, 310, 330, 275);
          o->box(fltk::THIN_UP_BOX);
          o->begin();
          
          {
fltk::Button* o = validateBtn = new fltk::Button(15, 25, 300, 100, "Validate Answer  @+1+");
            o->labeltype(fltk::EMBOSSED_LABEL);
            o->labelsize(16);
            o->callback((fltk::Callback*)cb_validateBtn);
            o->deactivate();
          }
          
          {
fltk::Button* o = nextBtn = new fltk::Button(15, 150, 300, 100, "Next Question  @+1>@+1>[]");
            o->labeltype(fltk::EMBOSSED_LABEL);
            o->labelsize(16);
            o->callback((fltk::Callback*)cb_nextBtn);
          }
          o->end();
          fltk::Group::current()->resizable(o);
        }
        o->end();
      }
      o->end();
      fltk::Group::current()->resizable(o);
    }
    o->end();
  }
  win_x = 0; win_y = 0;
  fullscreen_flag = false;
  fltk::register_images();
}

void QuestionViewUI::show() {
  mainWindow->show();
}

int QuestionViewUI::selectedRB() {
  for (int i=0; i<4; i++) 
  {
    if ( answerRB[i]->visible() && answerRB[i]->state() )
  	return i;
  }
  return -1;
}

void QuestionViewUI::showQuestion(Question* q) {
  char qNo[150];
    sprintf(qNo, "Ερώτηση %i/%i (%s)",currTest->cursor()+1,currTest->size(),q->getBookSection());
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
    
    if ( q->getSelectedAnswer() == -1 || q->isVerified()) 
    {
    	validateBtn->deactivate();
    }
    else 
    {
    	validateBtn->activate();
    }
}

void QuestionViewUI::setTest(Test* t) {
  currTest = t;
  showQuestion(currTest->next());
}

void QuestionViewUI::resizeAnswers(int no) {
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
