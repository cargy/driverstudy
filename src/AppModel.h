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

using namespace std;

class AppModel: public Model {
private:
	string title;
	int x,y,w,h;
	bool fullscreen_flag;
	int page_index;
	const char* statusbar_msg;
	static AppModel* instance;

public:
	AppModel();
	~AppModel();
	static AppModel* getInstance();
	bool fullscreen_toggle(int x, int y, int w, int h);
	const char* getappTitle();
	void setTitle(const char* appTitle);
	bool isfullscreen();
	int getx();
	int gety();
	int getw();
	int geth();
	void nextpage();
	void gotoTest();
	void gotoMainMenu();
	void gotoTestPage();
	void setStatusBarMsg(const char* msg);
	const char* getStuatusBarMsg();
	int getpage();
	void setpos(int x, int y);
	void setsize(int w, int h);
};

#endif /* APPMODEL_H_ */
