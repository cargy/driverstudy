// This is just small FLTK2 application
// Now you can imediately compile&run it in Dev-C++
// Enjoy FLTK2 - Dejan Lekic, dejan@fltk.net, http://dejan.lekic.org

#include <fltk/run.h>
#include <fltk/ask.h>
#include <fltk/Window.h>
#include <fltk/Slider.h>
#include <fltk/Button.h>
#include <fltk/WordwrapOutput.h>
#include <fltk/RadioButton.h>
#include <fltk/ReturnButton.h>
#include <fltk/IntInput.h>
#include <fltk/Image.h>
#include <fltk/SharedImage.h>
#include <stdlib.h>
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
  Group *AnswersGroup;
  Widget* picBox;
  RadioButton* answers[4];
  WordwrapOutput* question;
  Test *currTest;
  int curr_no;

  inline void next_callback_i() {
	  
	  Question *q = currTest->next(); 
	  
	  char imgPath[MAXIMGFILESIZE];
	  sprintf(imgPath, "img/%s.jpg",q->image());
	  //strncpy(imgPath, "img/", MAXIMGFILESIZE);
	  //strncpy(imgPath, q->image(), MAXIMGFILESIZE);
	  //imgPath[MAXIMGFILESIZE - 1] = '\0';



	  
	  cout << toLowerCase(imgPath) <<endl;
	  picBox->image( SharedImage::get(imgPath) );
	  picBox->redraw();
    this->redraw();
    
    const char* msg[3];
    msg[0] = "Όταν στρίβετε αριστερά σε ένα σταυροδρόμι όπου αντίθετα εισερχόμενα αυτοκίνητα επίσης στρίβουν αριστερά, ο σωστός και ασφαλής τρόπος διελεύσεως είναι αυτός που φαίνεται:"; 
    msg[1] = "Πινακίδες με μπλε κυκλικό φόντο υποδηλώνουν:";
    msg[2] = "На каком расстоянии от перекрестка разрешено останавливать ваше транспортное средство?";
    
    //loadQuestion(msg[curr_no]);
    
    loadQuestion(q);
    curr_no++;
    if (curr_no == 3) curr_no = 0;
  }
  
  static void next_callback(Widget*, void* v) {
    ((QuestionWindow*)v)->next_callback_i();
  }

public:

  QuestionWindow(const char* label=0) :
    Window(USEDEFAULT,USEDEFAULT,800,480,label,true),
    nextQuestion(470,400,325,65,"Next Question"),
    validateAnswer(470,320,325,65, "Validate Answer"),
    exit_button(10,390,70,65,"Exit")	
  {

	nextQuestion.callback(next_callback,this);
	question = new WordwrapOutput(5,18,460,95,"Ερώτηση ##");
	question->type(5);
	question->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
	fltk::register_images();
	picBox = new Widget(467,4,330,301);
	picBox->set_vertical();
	SharedImage::set_cache_size(1000000);
	
	picBox->image(*SharedImage::get("/home/krizz/Projects/TestDrive/demos/b-01.jpg"));	
	
	AnswersGroup = new Group(6,134,459,250,"Πιθανές Απαντήσεις:",true);
	AnswersGroup->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);

    for (int i=0; i<4; i++) 
    {
    	answers[i] = new RadioButton(14, 15+50*i, 425, 46, "Answer 1");
    	answers[i]->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
    	answers[i]->buttonbox(fltk::PLASTIC_DOWN_BOX);
	}
	
    end();
    curr_no = 0;
    exit_button.callback(exit_callback);
    end();
    resizable(this);
    //this->resize(670,473);
    
  }

  ~QuestionWindow() {}
  
  void loadQuestion(Question* q) {
	  question->label(q->getBookSection());
  	question->text(q->title());
  	
  	// reset answer buttons
  	for (unsigned int i=0; i<4; i++) {
		answers[i]->state(false);
		if ( i >= q->getAOA() ) answers[i]->hide();
		else answers[i]->show();
		
	}
	 
  	for (unsigned int i=0; i<q->getAOA(); i++) 
  	{
    	answers[i]->label(q->getAnswer(i));
	}
	answers[q->getSelectedAnswer()]->state(true);
  }
  
  void loadTest(Test *t) {
	  currTest = t;
  }


};

int main(int argc, char ** argv) {
	SQLITE3 sql("ExerBase.db");
	vector<int> *v = sql.testTemplate(1,1);
	int *array = sql.createRandomTestFromTemplate(v);
	Question *q = sql.getQuestionArray(array);
	Test *t = new Test(q,30);
	t->answerRandomly();
	
  QuestionWindow window1("Test Window");
  window1.show(argc,argv);
  window1.loadTest(t);
  return run();
}
