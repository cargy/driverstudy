/*
 * HomeView.h
 *
 *  Created on: Jul 26, 2010
 *      Author: krizz
 */

#ifndef TESTRESULTSVIEW_H_
#define TESTRESULTSVIEW_H_

#include "MV.h"
#include "TestModel.h"
#include <fltk/Group.h>
#include <fltk/Button.h>

#define TESTRESULTSVIEW_ID 7

class TestResultsView: public fltk::Group, public View {
private:
	fltk::Widget result;
	fltk::Button showWrongQuestionsBtn;
	fltk::Button newTestBtn;
	fltk::Button gotoMainMenuBtn;
	static void cb_showWrongQuestionsBtn(fltk::Widget* v, void *);
	void cb_showWrongQuestionsBtn_i();
	static void cb_gotoMainMenuBtn(fltk::Widget* v, void *);
	void cb_gotoMainMenuBtn_i();
	static void cb_newTestBtn(fltk::Widget* v, void *);
	void cb_newTestBtn_i();
	TestModel* model();

public:
	TestResultsView(int x, int y, int w, int h, const char* l);
	~TestResultsView();
	void update();
};

#endif /* TESTRESULTSVIEW_H_ */
