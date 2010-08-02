/*
 * MainMenuView.h
 *
 *  Created on: Jul 30, 2010
 *      Author: krizz
 */

#ifndef MAINMENUVIEW_H_
#define MAINMENUVIEW_H_

#include "MV.h"
#include <fltk/Group.h>
#include <fltk/Widget.h>
#include <fltk/Button.h>

using namespace fltk;

class MainMenuView: public Group, public View {
private:
	Widget appTitle;
	Group category;
	static void cb_categoryBtn(Widget* v, void *);
	void cb_categoryBtn_i(Button* btn);

public:
	MainMenuView(int x, int y, int w, int h, const char* l);
	~MainMenuView();
	Button motorcycleBtn;
	Button carBtn;
	Button truckBtn;
	Button busBtn;
};

#endif /* MAINMENUVIEW_H_ */
