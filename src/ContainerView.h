/*
 * ViewContainer.h
 *
 *  Created on: Jul 27, 2010
 *      Author: krizz
 */

#ifndef VIEWCONTAINER_H_
#define VIEWCONTAINER_H_

#include "MV.h"
#include <fltk/Group.h>
#include "AppModel.h"

#include "MainMenuView.h"
#include "HomeView.h"
#include "TestView.h"

class ContainerView: public View, public fltk::Group  {
private:
	fltk::Widget * prev_;
	fltk::Widget * value_;
	fltk::Widget * next_;
	MainMenuView* mainMenuView_;
	TestView* testView_;

	bool transitioning_;
	float interval_;
	void move_left();
	void move_right();

protected:
	int handle(int);

public:
	ContainerView(int x,int y,int w,int h, const char * l = 0, bool begin=false);
	~ContainerView();
	void update();
	void showPage(int i);
	AppModel* model();
	void setView();

	void draw();
	void next();
	void prev();
	void value(fltk::Widget *);
	//! return  the current visible child.
	fltk::Widget* value() const { return value_;}
	void slide(fltk::Widget *kid);
};


#endif /* VIEWCONTAINER_H_ */
