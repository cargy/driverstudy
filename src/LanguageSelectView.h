/*
 * LanguageSelectView.h
 *
 *  Created on: Sep 24, 2010
 *      Author: krizz
 */

#ifndef LANGUAGESELECTVIEW_H_
#define LANGUAGESELECTVIEW_H_

#include "MV.h"
#include <fltk/PopupMenu.h>
#include <fltk/Item.h>
#include "LanguageModel.h"
#include "TestPropertiesModel.h"

class LanguageSelectView: public fltk::PopupMenu, public View {

private:
	static void cb_languageSelected(fltk::Widget* w, void* v) ;
	inline void cb_languageSelected_i(fltk::PopupMenu* menu);
	fltk::Item* selected_;

public:
	LanguageSelectView(int x, int y, int w, int h, const char* label);
	virtual ~LanguageSelectView();
	void add(LanguageModel* plm);
	LanguageModel* getSelectedLanguage();
	TestPropertiesModel* model();
};

#endif /* LANGUAGESELECTVIEW_H_ */
