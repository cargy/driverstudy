// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "QuestionUIAbstract.h"
#include "config.h"

inline void QuestionUIAbstract::cb_answerRB_i(fltk::RadioButton* o, long v) {
  cb_answerSelected(o,v)
;}
void QuestionUIAbstract::cb_answerRB(fltk::RadioButton* o, long v) {
  ((QuestionUIAbstract*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_answerRB_i(o,v);
}

inline void QuestionUIAbstract::cb_answerRB1_i(fltk::RadioButton* o, long v) {
  cb_answerSelected(o,v)
;}
void QuestionUIAbstract::cb_answerRB1(fltk::RadioButton* o, long v) {
  ((QuestionUIAbstract*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_answerRB1_i(o,v);
}

inline void QuestionUIAbstract::cb_answerRB2_i(fltk::RadioButton* o, long v) {
  cb_answerSelected(o,v)
;}
void QuestionUIAbstract::cb_answerRB2(fltk::RadioButton* o, long v) {
  ((QuestionUIAbstract*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_answerRB2_i(o,v);
}

inline void QuestionUIAbstract::cb_answerRB3_i(fltk::RadioButton* o, long v) {
  cb_answerSelected(o,v)
;}
void QuestionUIAbstract::cb_answerRB3(fltk::RadioButton* o, long v) {
  ((QuestionUIAbstract*)(o->parent()->parent()->parent()->parent()->user_data()))->cb_answerRB3_i(o,v);
}

inline void QuestionUIAbstract::cb_exitBtn_i(fltk::Button*, void*) {
  cb_close()
;}
void QuestionUIAbstract::cb_exitBtn(fltk::Button* o, void* v) {
  ((QuestionUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_exitBtn_i(o,v);
}

inline void QuestionUIAbstract::cb_fullscreenBtn_i(fltk::Button*, void*) {
  cb_fullscreen()
;}
void QuestionUIAbstract::cb_fullscreenBtn(fltk::Button* o, void* v) {
  ((QuestionUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_fullscreenBtn_i(o,v);
}

inline void QuestionUIAbstract::cb_validateBtn_i(fltk::Button* o, const char* v) {
  cb_next(o,v)
;}
void QuestionUIAbstract::cb_validateBtn(fltk::Button* o, const char* v) {
  ((QuestionUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_validateBtn_i(o,v);
}

inline void QuestionUIAbstract::cb_nextBtn_i(fltk::Button* o, const char* v) {
  cb_next(o,v)
;}
void QuestionUIAbstract::cb_nextBtn(fltk::Button* o, const char* v) {
  ((QuestionUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_nextBtn_i(o,v);
}

QuestionUIAbstract::QuestionUIAbstract(int x, int y, int width, int height, const char* label): fltk::Window(x,y,width,height,label,true) {
  fltk::Group* w;
  
  {
fltk::Group* o = mainContainer = new fltk::Group(0, 0, 800, 600);
    w = o;
    o->shortcut(0xff1b);
    o->user_data((void*)(this));
    o->begin();
    
    {
fltk::Group* o = LeftGroup = new fltk::Group(5, 5, 450, 590);
      o->set_vertical();
      o->box(fltk::THIN_DOWN_BOX);
      o->begin();
      
      {
fltk::Group* o = QuestionGroup = new fltk::Group(5, 5, 440, 520);
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
fltk::Group* o = AnswerGroup = new fltk::Group(5, 155, 430, 355);
          o->box(fltk::THIN_DOWN_BOX);
          o->begin();
          
          {
fltk::RadioButton* o = answerRB[0] = new fltk::RadioButton(5, 4, 420, 85, "Answer 0");
            o->buttonbox(fltk::RSHADOW_BOX);
            o->labelsize(16);
            o->textsize(16);
            o->callback((fltk::Callback*)cb_answerRB, (void*)(0));
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
          }
          
          {
fltk::RadioButton* o = answerRB[1] = new fltk::RadioButton(5, 91, 420, 85, "Answer 1");
            o->buttonbox(fltk::RSHADOW_BOX);
            o->labelsize(16);
            o->textsize(16);
            o->callback((fltk::Callback*)cb_answerRB1, (void*)(1));
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
          }
          
          {
fltk::RadioButton* o = answerRB[2] = new fltk::RadioButton(5, 178, 420, 85, "Answer 2");
            o->buttonbox(fltk::RSHADOW_BOX);
            o->labelsize(16);
            o->textsize(16);
            o->callback((fltk::Callback*)cb_answerRB2, (void*)(2));
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
          }
          
          {
fltk::RadioButton* o = answerRB[3] = new fltk::RadioButton(5, 265, 420, 85, "Answer 3");
            o->buttonbox(fltk::RSHADOW_BOX);
            o->labelsize(16);
            o->textsize(16);
            o->callback((fltk::Callback*)cb_answerRB3, (void*)(3));
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
          }
          o->end();
        }
        o->end();
      }
      
      {
fltk::Group* o = MainControlsGroup = new fltk::Group(5, 530, 440, 57);
        o->box(fltk::THIN_UP_BOX);
        o->begin();
        
        {
fltk::Button* o = exitBtn = new fltk::Button(9, 8, 130, 40, _("Cancel") );
          o->labelfont(fltk::HELVETICA_BOLD);
          o->shortcut(0xff1b);
          o->callback((fltk::Callback*)cb_exitBtn);
        }
        
        {
fltk::Button* o = fullscreenBtn = new fltk::Button(157, 8, 130, 40, _("Fullscreen") );
          o->type(fltk::Button::TOGGLE);
          o->labelfont(fltk::HELVETICA_BOLD);
          o->shortcut(0xffc8);
          o->callback((fltk::Callback*)cb_fullscreenBtn);
        }
        
        {
fltk::Button* o = auxBtn = new fltk::Button(302, 8, 130, 40, _("Aux") );
          o->labelfont(fltk::HELVETICA_BOLD);
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
fltk::Button* o = validateBtn = new fltk::Button(15, 25, 300, 100, _("Validate Answer  @+1+") );
          o->labeltype(fltk::EMBOSSED_LABEL);
          o->labelsize(16);
          o->callback((fltk::Callback*)cb_validateBtn, (void*)("validate"));
          o->deactivate();
        }
        
        {
fltk::Button* o = nextBtn = new fltk::Button(15, 150, 300, 100, _("Next Question  @+1>@+1>[]") );
          o->labeltype(fltk::EMBOSSED_LABEL);
          o->labelsize(16);
          o->callback((fltk::Callback*)cb_nextBtn, (void*)("next"));
        }
        o->end();
        fltk::Group::current()->resizable(o);
      }
      o->end();
    }
    o->end();
  }
}

void QuestionUIAbstract::cb_close() {
}

void QuestionUIAbstract::cb_fullscreen() {
}

void QuestionUIAbstract::cb_answerSelected(fltk::Widget *pRB, long rbId) {
}

void QuestionUIAbstract::cb_next(fltk::Widget* pBtn, const char* btn) {
}
