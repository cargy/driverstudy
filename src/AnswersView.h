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
#include "TestModel.h"

class AnswersView: public fltk::Group, public View {
public:
	AnswersView(int x, int y, int w, int h, const char* l);
	~AnswersView();
	fltk::RadioButton* answerBtn[6];
	int size;
	void update();
	int selectedRB();
	static void cb_answerBtn(Widget* btn, void* v);
	void cb_answerBtn_i(fltk::RadioButton* btn);
	TestModel* model();
};

#endif /* ANSWERSVIEW_H_ */
