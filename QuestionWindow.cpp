// This is just small FLTK2 application
// Now you can imediately compile&run it in Dev-C++
// Enjoy FLTK2 - Dejan Lekic, dejan@fltk.net, http://dejan.lekic.org

//#define NDEBUG
#include <cassert>
#include <fltk/run.h>
#include <fltk/ask.h>
#include <fltk/Window.h>
#include <fltk/Slider.h>
#include <fltk/Button.h>
#include <fltk/TextDisplay.h>
#include <fltk/RadioButton.h>
#include <fltk/ReturnButton.h>
#include <fltk/IntInput.h>
#include <fltk/InvisibleBox.h>
#include <fltk/Image.h>
#include <fltk/SharedImage.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fltk/events.h>
#include "sqliteExerBase.cxx"

using namespace fltk;

static void exit_callback(Widget *, void *) {
	if (ask("Do you want to quit?"))
		exit(0);
	
}

char* toLowerCase(char* str)
{	
	int differ = 'A'-'a';
	char ch;
	int ii = strlen(str);
	for (int i=0; i <ii;i++)
	{
		strncpy(&ch,str+i,1);
		if (ch>='A' && ch<='Z')
		{
			ch = ch-differ;
			memcpy(str+i,&ch,1);
		}
	}
	return str;
}

class QuestionWindow : public Window {
  Button nextQuestion;
  ReturnButton validateAnswer;
  Button exit_button;
  Button fullscreen_button;
  Group *AnswersGroup;
  Widget* picBox;
  RadioButton* answers[4];
  TextDisplay* question;
  int winX, winY;
  Test *currTest;
  bool fs_status;
  
  
  static void next_callback(Widget*, void* v)
  {
    ((QuestionWindow*)v)->next_callback_i(false);
  }

  static void validate_callback(Widget*, void* v) {
	  ((QuestionWindow*)v)->next_callback_i(true);
  }
  
  static void cb_check_answer(Widget* , void* v) {

	  ((QuestionWindow*)v)->cb_check_answer_i();
  }  

  inline void cb_check_answer_i()
  {
	  if (getGUISelectedAnswer() > -1)
	  {
		validateAnswer.activate();
	}
	else 
	{

		validateAnswer.deactivate();
	}
	this->redraw();

	  if (getGUISelectedAnswer() > -1) validateAnswer.activate();
	  else validateAnswer.deactivate();

	 //message("Tik: %d.",getGUISelectedAnswer());
  }
  
  inline void next_callback_i(bool validated)
  {
	  // get user input answer
	  currTest->selectAnswerOfCurrentQuestion(getGUISelectedAnswer());
	  
	  // validate the answer of current question
	  if (validated) currTest->verifyAnswerOfCurrentQuestion();	  
	  
	  //check if test is completed
	  if (currTest->completed()) 
	  {
		  message("Απαντήσατε:\n%d από τις %d ερωτήσεις σωστά.",currTest->getCorrect(), currTest->getAOQ());
		  
		  Test *w = new Test(currTest->wrongQuestions(),currTest->getAOQ()-currTest->getCorrect());
		  w->showResults();
		  loadTest(w);
	  }
	  // load next question
	  else 
		loadQuestion(currTest->next());  //Question *q = currTest->next();
	  
  }
  
   
  static void fs_callback(Widget*, void* v) {
	  if (((QuestionWindow*)v)->fs_status) 
	  {
		  ((QuestionWindow*)v)->fullscreen_off(((QuestionWindow*)v)->winX,((QuestionWindow*)v)->winY,800,480);
		  ((QuestionWindow*)v)->set_non_modal();
	  }
	  else 
	  {
		  ((QuestionWindow*)v)->winX = ((QuestionWindow*)v)->x();
		  ((QuestionWindow*)v)->winY = ((QuestionWindow*)v)->y();
		  ((QuestionWindow*)v)->fullscreen();
		  ((QuestionWindow*)v)->set_modal();
		  
	  }
	  
	  if (((QuestionWindow*)v)->fs_status) ((QuestionWindow*)v)->fs_status=false;
	  else ((QuestionWindow*)v)->fs_status=true;
  }

public:

  QuestionWindow(const char* label=0) :
    Window(USEDEFAULT,USEDEFAULT,800,480,label,true),
    nextQuestion(470,400,325,65,"Επόμενη Ερώτηση"),
    validateAnswer(470,320,325,65, "Επιβεβαίωση Απάντησης"),
    exit_button(10,390,70,65,"Έξοδος"),
    fullscreen_button(100,390,70,65,"Fullscreen")
  {

	question = new TextDisplay(5,18,460,95,"Ερώτηση ##");
	question->wrap_mode(true);
	question->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
	fltk::Group::current()->resizable(question);
	
	fltk::register_images();
	picBox = new Widget(467,4,330,301);
	//fltk::Group::current()->resizable(picBox);
	picBox->set_vertical();
	SharedImage::set_cache_size(1000000);

	AnswersGroup = new Group(6,125,459,250,"",true);
	AnswersGroup->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
	fltk::Group::current()->resizable(AnswersGroup);

    for (int i=0; i<4; i++) 
    {
    	answers[i] = new RadioButton(5, 60*i, 425, 60, "Answer 1");
    	answers[i]->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
    	answers[i]->buttonbox(fltk::PLASTIC_DOWN_BOX);
    	answers[i]->callback((Callback*)cb_check_answer,this);
	}
	
    //end();
    
    nextQuestion.callback(next_callback,this);
    fullscreen_button.callback(fs_callback,this);
    validateAnswer.callback(validate_callback,this);
    exit_button.callback(exit_callback);
    
    fs_status = false;
    winX = 0; winY = 0;
    //end();
    
  }

  ~QuestionWindow() {}
  
  void loadQuestion(Question* q) {
	  
	 question->label(q->getBookSection());
	 char qNo[150];
	 sprintf(qNo, "Ερώτηση %i",currTest->getCursor()+1);
	 this->label(qNo);
  	question->text(q->title());
  	
  	// reset answer buttons
  	for (unsigned int i=0; i<4; i++) {
		answers[i]->state(false);
		answers[i]->labelcolor((fltk::Color)56);
		if ( i >= q->getAOA() ) answers[i]->hide();
		else answers[i]->show();
		
	}
	 
  	for (unsigned int i=0; i<q->getAOA(); i++) 
  	{
    	answers[i]->label(q->getAnswer(i));
	}
	answers[q->getSelectedAnswer()]->state(true);
	answers[q->getCorrectAnswer()]->labelcolor((fltk::Color)0xff00);
	
	char imgPath[MAXIMGFILESIZE];
	sprintf(imgPath, "img/%s.jpg",q->image());
	//cout << toLowerCase(imgPath) <<endl;
	picBox->image( SharedImage::get(toLowerCase(imgPath)) );
	picBox->redraw();
	this->redraw();
	
	if ( q->getSelectedAnswer() == -1 || q->isVerified()) 
	{
		validateAnswer.deactivate();
	}
	else 
	{
		validateAnswer.activate();
	}
  }
  
  int getGUISelectedAnswer()
  {
	  for (int i=0; i<4; i++) {
		  if ( answers[i]->visible() && answers[i]->state() )
			return i;
		}
		return -1;	
  }
  
  void loadTest(Test *t) {
	  currTest = t;
	  loadQuestion(currTest->next());
  }


};


int main(int argc, char ** argv) {
	
	SQLITE3 sql("ExerBase.db");
	vector<int> *v = sql.testTemplate(1,1);
	int *array = sql.createRandomTestFromTemplate(v);

	Question *q = sql.getQuestionArray(array);

	Test *t = new Test(q,30);
	//t->answerRandomly();
	
	QuestionWindow window1("Test Window");
	window1.show(argc,argv);
	window1.loadTest(t);
	return run();
}
