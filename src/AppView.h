/*
 * AppView.h
 *
 *  Created on: Jul 25, 2010
 *      Author: krizz
 */

#ifndef APPVIEW_H_
#define APPVIEW_H_

#include "MV.h"
#include <fltk/Window.h>
#include <fltk/StatusBarGroup.h>
#include <fltk/BarGroup.h>
#include <fltk/PackedGroup.h>
#include <fltk/ToggleButton.h>
#include <fltk/Button.h>
#include <fltk/LightButton.h>

#include "AppModel.h"
#include "ContainerView.h"
#include "ToolbarView.h"

#define APPVIEW_ID 1

class AppView: public fltk::Window, public View {
private:
	fltk::PackedGroup group;
		ContainerView* container;
		ToolbarView* toolbar;
	fltk::StatusBarGroup statusBar;


		fltk::ToggleButton* fullscreenBtn;
		fltk::Button* quitBtn;
		fltk::Button* aboutBtn;
		fltk::LightButton* dicationBtn;
	//
	bool fullscreen_status;

	static void cb_exit(fltk::Widget* pWdg, void* p);
	AppModel* model();


public:
	AppView(int x, int y, int w, int h, const char* l);
	~AppView();
	virtual void attach();
	void update();
	ContainerView* getTestView();
};

#endif /* APPVIEW_H_ */
