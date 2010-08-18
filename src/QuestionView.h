/*
 * TestView.h
 *
 *  Created on: Jul 31, 2010
 *      Author: krizz
 */

#ifndef QUESTIONVIEW_H_
#define QUESTIONVIEW_H_

#include "MV.h"
#include <fltk/Group.h>
#include <fltk/Button.h>
#include <fltk/Widget.h>
#include "TimerProgressBar.h"
#include "AnswersView.h"
#include "TestModel.h"

class QuestionView: public fltk::Group, public View {
private:
	fltk::Group leftGroup;
	fltk::Group questionGroup;
			fltk::Button questionHolder;
			AnswersView answerGroup;
	fltk::Group rightGroup;
		fltk::Widget imageHolder;
		fltk::Group controlGroup;
			TimerProgressBar timerBar;
			fltk::Button validateBtn;
			fltk::Button nextBtn;

	//callbacks
	static void cb_nextQuestionBtn(fltk::Widget* btn, void *v);
	void cb_nextQuestionBtn_i(fltk::Button* btn);
	static void cb_validateBtn(fltk::Widget* btn, void *v);
	void cb_validateBtn_i(fltk::Button* btn);
	static void cb_nextBtn(fltk::Widget* v, void *);
	void cb_nextBtn_i(fltk::Button* btn);
	TestModel* model();

public:
	QuestionView(int x, int y, int w, int h, const char* l);
	void setQuestion(const char* q);
	void setQuestionNumber(int qNo, int size);
	void setAnswers(QuestionModel* pQuestion);
	void setQuestionImage(QuestionModel* pQuestion);
	AnswersView* answersView();
	~QuestionView();
	void update();
};

#endif /* QUESTIONVIEW_H_ */

