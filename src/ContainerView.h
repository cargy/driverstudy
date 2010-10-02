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
#include "TestResultsView.h"
#include "TestView.h"

#define CONTAINERVIEW_ID 3
#define STEP_FACTOR 20
class ContainerView: public fltk::Group, public View  {
private:
	fltk::Widget * prev_;
	fltk::Widget * value_;
	fltk::Widget * next_;
	MainMenuView* mainMenuView_;
	TestView* testView_;
	TestResultsView* testResultsView_;

	bool transitioning_;
	float interval_;
	int step_;
	void move_left();
	void move_right();

protected:
	int handle(int);

public:
	ContainerView(int x,int y,int w,int h, const char * l = 0, bool begin=false);
	~ContainerView();
	virtual void attach();
	virtual void modelAttached();
	void update();
	void showPage(int i);
	AppModel* model();

	void draw();
	void next();
	void prev();
	void value(fltk::Widget *);
	//! return  the current visible child.
	fltk::Widget* value() const { return value_;}
	void slide(fltk::Widget *kid);
	TestView* getTestView();
};


#endif /* VIEWCONTAINER_H_ */
