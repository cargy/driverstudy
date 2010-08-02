/*
 * HomeView.cpp
 *
 *  Created on: Jul 26, 2010
 *      Author: krizz
 */

#include "HomeView.h"

HomeView::HomeView(int x, int y, int w, int h, const char* l) :
Group(x, y, w, h, l, true/* auto-begin() */),
View(),
backBtn(x + 500, y + 50, 100, 20,l),
nextBtn(x + 500, y + 150, 100, 20,"Next >>"),
title(100,100,100,50)
{
	end(); // don't forget to do this!
	backBtn.callback(cb_testBtn);
	nextBtn.callback(cb_nextBtn);
}

HomeView::~HomeView() {
	// TODO Auto-generated destructor stub
}

AppModel* HomeView::model() {
	return ((AppModel*)pModel);
}

void HomeView::cb_testBtn(Widget* v, void *) { // static method
  ((HomeView*)(v->parent()))->cb_testBtn_i();
}

void HomeView::cb_testBtn_i() {
	if (AppModel::getInstance() == NULL)
		backBtn.label("BOO!");
	else {
		//testBtn.label(model()->getappTitle());
		AppModel::getInstance()->gotoMainMenu();
	}
}

void HomeView::cb_nextBtn(Widget* v, void *) { // static method
  ((HomeView*)(v->parent()))->cb_nextBtn_i();
}

void HomeView::cb_nextBtn_i() {
	if (AppModel::getInstance() == NULL)
		backBtn.label("BOO!");
	else {
		//testBtn.label(model()->getappTitle());
		AppModel::getInstance()->gotoTestPage();
	}
}
