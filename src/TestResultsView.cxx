/*
 * HomeView.cpp
 *
 *  Created on: Jul 26, 2010
 *      Author: krizz
 */

#include "TestResultsView.h"

TestResultsView::TestResultsView(int x, int y, int w, int h, const char* l) :
Group(x, y, w, h, l, true/* auto-begin() */),
View(),
result(x+12, 6, w - 2*12, 54, "Passed/Failed"),
showWrongQuestionsBtn(x+50, 190, w - 2*50, 90, "Show Wrong Questions"),
newTestBtn(x+50, 290, w - 2*50, 90,"New Test"),
gotoMainMenuBtn(x+50, 390, w - 2*50, 90, "Go to MainMenu")
{
	end(); // don't forget to do this!
	// customize result
	result.box(fltk::HIGHLIGHT_UP_BOX);
	result.labeltype(fltk::EMBOSSED_LABEL);
	result.labelsize(32);
	result.textsize(32);

	showWrongQuestionsBtn.labeltype(fltk::EMBOSSED_LABEL);
	showWrongQuestionsBtn.labelsize(22);
	showWrongQuestionsBtn.textsize(22);

	newTestBtn.labeltype(fltk::EMBOSSED_LABEL);
	newTestBtn.labelsize(22);
	newTestBtn.textsize(22);

	gotoMainMenuBtn.labeltype(fltk::EMBOSSED_LABEL);
	gotoMainMenuBtn.labelsize(22);
	gotoMainMenuBtn.textsize(22);

	showWrongQuestionsBtn.callback(cb_showWrongQuestionsBtn);
	gotoMainMenuBtn.callback(cb_gotoMainMenuBtn);
	newTestBtn.callback(cb_newTestBtn);
}

TestResultsView::~TestResultsView() {
	// TODO Auto-generated destructor stub
}

AppModel* TestResultsView::model() {
	return ((AppModel*)pModel);
}



void TestResultsView::cb_showWrongQuestionsBtn(Widget* v, void *) { // static method
  ((TestResultsView*)(v->parent()))->cb_showWrongQuestionsBtn_i();
}

void TestResultsView::cb_showWrongQuestionsBtn_i() {
	if (AppModel::getInstance() == NULL)
		gotoMainMenuBtn.label("BOO!");
	else {
		//testBtn.label(model()->getappTitle());
		AppModel::getInstance()->gotoCurrentTest();
	}
}

void TestResultsView::cb_newTestBtn(Widget* v, void *) { // static method
  ((TestResultsView*)(v->parent()))->cb_newTestBtn_i();
}

void TestResultsView::cb_newTestBtn_i() {
	if (AppModel::getInstance() == NULL)
		gotoMainMenuBtn.label("BOO!");
	else {
		//testBtn.label(model()->getappTitle());
		AppModel::getInstance()->gotoTestResults();
	}
}

void TestResultsView::cb_gotoMainMenuBtn(Widget* v, void *) { // static method
  ((TestResultsView*)(v->parent()))->cb_gotoMainMenuBtn_i();
}

void TestResultsView::cb_gotoMainMenuBtn_i() {
	if (AppModel::getInstance() == NULL)
		gotoMainMenuBtn.label("BOO!");
	else {
		//testBtn.label(model()->getappTitle());
		AppModel::getInstance()->gotoMainMenu();
	}
}

