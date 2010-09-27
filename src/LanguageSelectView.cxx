/*
 * LanguageSelectView.cxx
 *
 *  Created on: Sep 24, 2010
 *      Author: krizz
 */

#include "LanguageSelectView.h"
#include <fltk/Item.h>

using namespace fltk;

LanguageSelectView::LanguageSelectView(int x, int y, int w, int h, const char* label):
PopupMenu(x,y,w,h,label)
{
	// TODO Auto-generated constructor stub
	add(new Item("Greek"));
	add(new Item("English"));
	add(new Item("Russian"));
	add(new Item("Albanian"));
	callback(cb_languageSelected, this);

}

LanguageSelectView::~LanguageSelectView() {
	// TODO Auto-generated destructor stub
}

void LanguageSelectView::cb_languageSelected(Widget* w, void* v) {
  ((LanguageSelectView*)v)->cb_languageSelected_i((PopupMenu*)w);
}

inline void LanguageSelectView::cb_languageSelected_i(PopupMenu* menu) {

	fltk::Widget* item = menu->get_item();

	// set languagePUM label to selected item label
	menu->label(item->label());
}
