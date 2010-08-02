/*
 * HomeView.h
 *
 *  Created on: Jul 26, 2010
 *      Author: krizz
 */

#ifndef HOMEVIEW_H_
#define HOMEVIEW_H_

#include "MV.h"
#include "AppModel.h"
#include <fltk/Group.h>
#include <fltk/Button.h>

using namespace fltk;

class HomeView: public Group, public View {
private:
	Button backBtn;
	Button nextBtn;
	Widget title;
	static void cb_testBtn(Widget* v, void *);
	void cb_testBtn_i();
	static void cb_nextBtn(Widget* v, void *);
	void cb_nextBtn_i();
	AppModel* model();

public:
	HomeView(int x, int y, int w, int h, const char* l);
	~HomeView();
};

#endif /* HOMEVIEW_H_ */
