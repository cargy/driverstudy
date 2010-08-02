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

class AppView: public fltk::Window, public View {
private:
	fltk::PackedGroup group;
		ContainerView* container;
		fltk::BarGroup* toolbar;
	fltk::StatusBarGroup statusBar;


		fltk::ToggleButton* fullscreenBtn;
		fltk::Button* quitBtn;
		fltk::Button* aboutBtn;
		fltk::LightButton* dicationBtn;
	//
	bool fullscreen_status;

	static void cb_exit(fltk::Widget* pWdg, void* p);
	//static void cb_fullscreenBtn(fltk::Widget* pWdg, void* p);
	static void cb_fullscreenBtn(Widget* w, void* v) ;
	inline void cb_fullscreenBtn_i(fltk::ToggleButton* fullscreenBtn);
	static void cb_nextBtn(fltk::Widget* w, void* v) ;
	inline void cb_nextBtn_i(fltk::Button* btn);
	static void cb_prevBtn(fltk::Widget* w, void* v) ;
	inline void cb_prevBtn_i(fltk::Button* btn);
	AppModel* model();


public:
	AppView(int x, int y, int w, int h, const char* l);
	~AppView();
	void update();
};

#endif /* APPVIEW_H_ */
