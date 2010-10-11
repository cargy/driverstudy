/*
 * LanguageSelectView.cxx
 *
 *  Created on: Sep 24, 2010
 *      Author: krizz
 */

#include "LanguageSelectView.h"
#include <fltk/Item.h>
#include "AppModel.h"

using namespace fltk;

LanguageSelectView::LanguageSelectView(int x, int y, int w, int h, const char* label):
PopupMenu(x,y,w,h,label),
View()
{
	callback(cb_languageSelected, this);
}

LanguageSelectView::~LanguageSelectView() {
	// TODO Auto-generated destructor stub
}

TestPropertiesModel* LanguageSelectView::model() { return (TestPropertiesModel*)pModel; }

void LanguageSelectView::modelAttached()
{
	vector<LanguageModel*> langs = AppModel::getInstance()->getLanguages();
	for (unsigned int i=0; i < langs.size(); i++)
		add(langs[i]);

}
void LanguageSelectView::add(LanguageModel* plm) {
	PopupMenu::add(plm->getLabel().c_str(),0,NULL, (void*)plm, 0);
}
void LanguageSelectView::cb_languageSelected(Widget* w, void* v) {
  ((LanguageSelectView*)v)->cb_languageSelected_i((PopupMenu*)w);
}

LanguageModel* LanguageSelectView::getSelectedLanguage()
{
	LanguageModel* lang = ((LanguageModel*)selected_->user_data());
	return lang;
}

inline void LanguageSelectView::cb_languageSelected_i(PopupMenu* menu) {

	fltk::Widget* item = menu->get_item();

	// set languagePUM label to selected item label
	LanguageModel* lang = ((LanguageModel*)item->user_data());
	model()->setLanguage(lang);
	selected_ = (Item*)item;
	menu->label(lang->getLabel().c_str());
}
