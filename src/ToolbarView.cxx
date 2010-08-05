/*
 * ToolbarView.cxx
 *
 *  Created on: Aug 3, 2010
 *      Author: krizz
 */

#include "ToolbarView.h"
#include "AppModel.h"

using namespace fltk;

ToolbarView::ToolbarView(int x, int y, int width, int height, const char* label):
BarGroup(x,y,width,height,label, true/* auto-begin() */),
fullscreenBtn(116, 11, 180, 60, "Fullscreen"),
quitBtn(18, 11, 60, 60, "Quit" ),
aboutBtn(536, 11, 60, 60, "About"),
dicationBtn(439, 11, 90, 60, "Dictation")
{
	quitBtn.callback(cb_quitBtn,this);
	fullscreenBtn.callback(cb_fullscreenBtn, this);


}

ToolbarView::~ToolbarView() {
	// TODO Auto-generated destructor stub
}

void ToolbarView::cb_quitBtn(Widget* w, void* v) {
  ((ToolbarView*)v)->cb_quitBtn_i((Button*)w);
}

inline void ToolbarView::cb_quitBtn_i(Button* btn) {
	AppModel::getInstance()->gotoMainMenu();
}

void ToolbarView::cb_aboutBtn(Widget* w, void* v) {
  ((ToolbarView*)v)->cb_aboutBtn_i((Button*)w);
}

inline void ToolbarView::cb_aboutBtn_i(Button* btn) {
	AppModel::getInstance()->gotoMainMenu();
}

void ToolbarView::cb_fullscreenBtn(Widget* w, void* v) {
  ((ToolbarView*)v)->cb_fullscreenBtn_i((Button*)w);
}

inline void ToolbarView::cb_fullscreenBtn_i(Button* btn) {
	AppModel::getInstance()->fullscreen_toggle();
}
