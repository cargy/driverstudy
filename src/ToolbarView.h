/*
 * ToolbarView.h
 *
 *  Created on: Aug 3, 2010
 *      Author: krizz
 */

#ifndef TOOLBARVIEW_H_
#define TOOLBARVIEW_H_

#include "MV.h"
#include <fltk/BarGroup.h>
#include <fltk/Button.h>
#include <fltk/ToggleButton.h>
#include <fltk/LightButton.h>

#define TOOLBARVIEW_ID 2;

class ToolbarView: public fltk::BarGroup, public View {
private:
	static void cb_quitBtn(fltk::Widget* w, void* v) ;
	inline void cb_quitBtn_i(fltk::Button* btn);
	static void cb_aboutBtn(fltk::Widget* w, void* v) ;
	inline void cb_aboutBtn_i(fltk::Button* btn);
	static void cb_fullscreenBtn(fltk::Widget* w, void* v) ;
	inline void cb_fullscreenBtn_i(fltk::Button* btn);

public:
	ToolbarView(int x, int y, int width, int height, const char* label);
	~ToolbarView();
	fltk::ToggleButton fullscreenBtn;
	fltk::Button quitBtn;
	fltk::Button aboutBtn;
	fltk::LightButton dicationBtn;
};

#endif /* TOOLBARVIEW_H_ */
