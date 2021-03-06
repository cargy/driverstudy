// generated by Fast Light User Interface Designer (fluid) version 2.1000

#ifndef QuestionUIAbstract_h
#define QuestionUIAbstract_h
#include <fltk/Group.h>
#include "TimerProgressBar.h"
#include <fltk/Group.h>
#include <fltk/Button.h>
#include <fltk/RadioButton.h>
#include <fltk/LightButton.h>
#include <fltk/Widget.h>

class QuestionUIAbstract : public fltk::Group  {
public:
  QuestionUIAbstract(int x, int y, int width, int height, const char* label);
  fltk::Group *mainContainer;
private:
    fltk::Group *LeftGroup;
public:
      fltk::Group *QuestionGroup;
        fltk::Button *questionDisplay;
private:
        inline void cb_questionDisplay_i(fltk::Button*, void*);
        static void cb_questionDisplay(fltk::Button*, void*);
public:
        fltk::Group *AnswerGroup;
private:
          inline void cb_answerRB_i(fltk::RadioButton*, long);
          static void cb_answerRB(fltk::RadioButton*, long);
          inline void cb_answerRB1_i(fltk::RadioButton*, long);
          static void cb_answerRB1(fltk::RadioButton*, long);
          inline void cb_answerRB2_i(fltk::RadioButton*, long);
          static void cb_answerRB2(fltk::RadioButton*, long);
public:
          fltk::RadioButton *answerRB[4];
private:
          inline void cb_answerRB3_i(fltk::RadioButton*, long);
          static void cb_answerRB3(fltk::RadioButton*, long);
      fltk::Group *MainControlsGroup;
public:
        fltk::Button *exitBtn;
private:
        inline void cb_exitBtn_i(fltk::Button*, void*);
        static void cb_exitBtn(fltk::Button*, void*);
public:
        fltk::Button *fullscreenBtn;
private:
        inline void cb_fullscreenBtn_i(fltk::Button*, void*);
        static void cb_fullscreenBtn(fltk::Button*, void*);
public:
        fltk::LightButton *soundBtn;
private:
        inline void cb_soundBtn_i(fltk::LightButton*, void*);
        static void cb_soundBtn(fltk::LightButton*, void*);
    fltk::Group *RightGroup;
public:
      fltk::Widget *imageHolder;
private:
      fltk::Group *QuestionControlsGroup;
public:
        TimerProgressBar *timer;
private:
        inline void cb_timer_i(TimerProgressBar*, void*);
        static void cb_timer(TimerProgressBar*, void*);
public:
        fltk::Button *validateBtn;
private:
        inline void cb_validateBtn_i(fltk::Button*, const char*);
        static void cb_validateBtn(fltk::Button*, const char*);
public:
        fltk::Button *nextBtn;
private:
        inline void cb_nextBtn_i(fltk::Button*, const char*);
        static void cb_nextBtn(fltk::Button*, const char*);
public:
  virtual void cb_close();
  virtual void cb_fullscreen();
  virtual void cb_answerSelected(fltk::Widget *pRB, long rbId);
  virtual void cb_next(fltk::Widget* pBtn, const char* btn);
  virtual void cb_timeout();
  virtual void cb_questionRelease();
  virtual void cb_soundToggle();
};
#endif
