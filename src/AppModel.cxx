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
}

AppModel::~AppModel() {
	// TODO Auto-generated destructor stub
}

AppModel* AppModel::getInstance() {
	return instance;
}

bool AppModel::fullscreen_toggle(int x, int y, int w, int h) {
	if (!fullscreen_flag) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
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

void AppModel::gotoTestPage() {
	page_index = 2;
	changed();
}

void AppModel::gotoTest() {
	page_index = 1;
	changed();
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
