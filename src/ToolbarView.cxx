/*
 * ToolbarView.cxx
 *
 *  Created on: Aug 3, 2010
 *      Author: krizz
 */

#include "ToolbarView.h"
#include "AppModel.h"
#include <fltk/Item.h>

using namespace fltk;

ToolbarView::ToolbarView(int x, int y, int width, int height, const char* label):
BarGroup(x,y,width,height,label, true/* auto-begin() */),
View(),
quitBtn(730, (height-60)/2-1, 60, 60, "Quit" ),
languageMenu(40,(height-60)/2-1, 180, 60, "Language" ),
fullscreenBtn(440, (height-60)/2-1, 180, 60, "Fullscreen"),
dicationBtn(240, (height-60)/2-1, 180, 60, "Dictation"),
aboutBtn(660, (height-60)/2-1, 60, 60, "About")
{
	resizable(this);
	glyph_size(30);
	//align(ALIGN_TOP);

	quitBtn.callback(cb_quitBtn,this);
	fullscreenBtn.callback(cb_fullscreenBtn, this);
	/*
	languageMenu.add(new Item("Greek"));
	languageMenu.add(new Item("English"));
	languageMenu.add(new Item("Russian"));
	languageMenu.add(new Item("Albanian"));
	*/


}

ToolbarView::~ToolbarView() {
	// TODO Auto-generated destructor stub
}

void ToolbarView::cb_quitBtn(Widget* w, void* v) {
  ((ToolbarView*)v)->cb_quitBtn_i((Button*)w);
}

inline void ToolbarView::cb_quitBtn_i(Button* btn) {
	AppModel::getInstance()->quit();
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
