/*
 * AppModel.h
 *
 *  Created on: Jul 24, 2010
 *      Author: krizz
 */

#ifndef APPMODEL_H_
#define APPMODEL_H_
#include "MV.h"
#include <cstdlib>
#include <string>
#include <fltk/Window.h>
#include "sqlite3.cxx"

#define APPMODEL_ID 1

using namespace std;

class AppModel: public Model {
private:
	string title;
	int x,y,w,h;
	bool fullscreen_flag;
	int page_index;
	const char* statusbar_msg;
	static AppModel* instance;
	fltk::Window* mainWindow_;
	SQLITE3* db;


public:
	AppModel();
	~AppModel();
	static AppModel* getInstance();
	bool fullscreen_toggle();
	const char* getappTitle();
	void setTitle(const char* appTitle);
	bool isfullscreen();
	int getx();
	int gety();
	int getw();
	int geth();
	void nextpage();
	void gotoTest();
	void gotoCurrentTest();
	void gotoMainMenu();
	void gotoTestResults();
	void setStatusBarMsg(const char* msg);
	const char* getStuatusBarMsg();
	int getpage();
	void setpos(int x, int y);
	void setsize(int w, int h);
	void setView(View *pw);
	void createTest(int catid, int langid);
	TestModel* currentTest;
};

#endif /* APPMODEL_H_ */
