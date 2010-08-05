/*
 * AnswersView.h
 *
 *  Created on: Aug 2, 2010
 *      Author: krizz
 */

#ifndef ANSWERSVIEW_H_
#define ANSWERSVIEW_H_

#include "MV.h"
#include <fltk/Group.h>
#include <fltk/RadioButton.h>

class AnswersView: public fltk::Group, public View {
public:
	AnswersView(int x, int y, int w, int h, const char* l);
	~AnswersView();
	fltk::RadioButton* answerBtn[6];
	int size;
	void update();
	static void cb_answerBtn(Widget* v, void *);
	void cb_answerBtn_i(fltk::RadioButton* btn);
};

#endif /* ANSWERSVIEW_H_ */
