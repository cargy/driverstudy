/*
 * TestView.h
 *
 *  Created on: Jul 31, 2010
 *      Author: krizz
 */

#ifndef TESTVIEW_H_
#define TESTVIEW_H_

#include "MV.h"
#include <fltk/Group.h>
#include <fltk/Button.h>
#include <fltk/Widget.h>
#include "TimerProgressBar.h"

using namespace fltk;

class QuestionView: public Group, public View {
private:
	Group leftGroup;
		Group questionGroup;
			Button questionHolder;
			Group answerGroup;
	Group rightGroup;
		Widget imageHolder;
		Group controlGroup;
			TimerProgressBar timerBar;
			Button validateBtn;
			Button nextBtn;

public:
	QuestionView(int x, int y, int w, int h, const char* l);
	~QuestionView();
};

#endif /* TESTVIEW_H_ */

