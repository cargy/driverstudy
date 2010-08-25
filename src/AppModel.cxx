/*
 * AppModel.cxx
 *
 *  Created on: Jul 24, 2010
 *      Author: krizz
 */

#include "AppModel.h"
#include "config.h"
#include <cstdio>
#include <cstring>
#include "AppView.h"
#include <fltk/Widget.h>

AppModel* AppModel::instance = NULL;

AppModel::AppModel() : Model() {

	string appTitle(APPLICATIONTITLE);
	string appVersion(DRIVERSTUDYVERSION);
	title = appTitle + " " + appVersion;

	fullscreen_flag = false;
	w = 800; h = 600;
	page_index = 0;
	instance = this;
	statusbar_msg = "Ready";
	db = new SQLITE3(DATABASE);
	currentTest = NULL;
}

AppModel::~AppModel() {
	// TODO Auto-generated destructor stub
}

AppModel* AppModel::getInstance() {
	return instance;
}

void AppModel::setView(View *pv) {
	if ( dynamic_cast<fltk::Window*>(pv)->is_window() ) mainWindow_ = dynamic_cast<fltk::Window*>(pv);
	Model::setView(pv);
}

bool AppModel::fullscreen_toggle() {
	if (!fullscreen_flag) {
		this->x = mainWindow_->x();
		this->y = mainWindow_->y();
		this->w = mainWindow_->w();
		this->h = mainWindow_->h();
	}
	fullscreen_flag = !fullscreen_flag;
	changed();
	return fullscreen_flag;
}

bool AppModel::isfullscreen() {
	return fullscreen_flag;
}

void AppModel::nextpage() {
	page_index++;
	changed();
}

void AppModel::gotoMainMenu() {
	page_index = 0;
	changed();
}

void AppModel::gotoTestResults() {
	page_index = 2;
	changed();
}

//#include "Facade.h"
void AppModel::gotoTest() {
	page_index = 1;
	//if ( currentTest ) delete currentTest;
	currentTest = db->getTest(2,1);
	getFacade()->attachModel(TESTMODEL_ID, currentTest);
	getFacade()->setViewToModel(TESTMODEL_ID, TESTVIEW_ID);
	getFacade()->setViewToModel(TESTMODEL_ID, QUESTIONVIEW_ID);
	getFacade()->setViewToModel(TESTMODEL_ID, ANSWERSVIEW_ID);

	changed();

	currentTest->nextQuestion();


}

void AppModel::gotoCurrentTest() {
	page_index = 1;
	if ( !currentTest ) return;
	changed();

	currentTest->nextWrong();


}

void AppModel::createTest(int catid, int langid) {
	db->getTest(1,1);
}

void AppModel::setStatusBarMsg(const char* msg)
{
	statusbar_msg = msg;
	changed();
}

const char* AppModel::getStuatusBarMsg() { return statusbar_msg; }

const char* AppModel::getappTitle() {
	return title.c_str();
}

void AppModel::setTitle(const char* appTitle) {
	title = appTitle;
	changed();
}

int AppModel::getx() { return x;}
int AppModel::gety() { return y;}
int AppModel::getw() { return w;}
int AppModel::geth() { return h;}
int AppModel::getpage() { return page_index; }
void AppModel::setpos(int x, int y) { this->x = x; this->y = y; /*changed();*/ }
void AppModel::setsize(int w, int h) { this->w = w; this->h = h; /*changed();*/ }
