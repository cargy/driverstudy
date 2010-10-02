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
#include "CategoryBtnView.h"
#include "TestPropertiesModel.h"
#include <vector>

#define MAINMENUVIEW_ID 4

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
	CategoryBtnView motorcycleBtn;
	CategoryBtnView carBtn;
	CategoryBtnView truckBtn;
	CategoryBtnView busBtn;
	std::vector<CategoryBtnView> categoryButtons;
	virtual void attach();
	TestPropertiesModel* model();
};

#endif /* MAINMENUVIEW_H_ */
