/*
 * MainMenuView.cxx
 *
 *  Created on: Jul 30, 2010
 *      Author: krizz
 */

#include "MainMenuView.h"
#include "AppModel.h"
#include <fltk/Image.h>
#include <fltk/SharedImage.h>

MainMenuView::MainMenuView(int x, int y, int w, int h, const char* l) :
Group(x, y, w, h, l, true/* auto-begin() */),
View(),
appTitle(x+12, 6, w - 2*12, 54, "Applcation Title"),
category(x+12, 90, w - 2*12, h-90 - 10/*275*/, "Select Category"),
motorcycleBtn(category.x()+15, y + 100 , 130, 120, "Motorcycle"),
carBtn(category.x()+15+w/4*1, y + 100, 130, 120, "Car"),
truckBtn(category.x()+15+w/4*2, y + 100, 130, 120, "Truck"),
busBtn(category.x()+15+w/4*3, y + 100, 130, 120, "Bus")
{
	// customize appTitle
    appTitle.box(fltk::HIGHLIGHT_UP_BOX);
    appTitle.labeltype(fltk::EMBOSSED_LABEL);
    appTitle.labelsize(32);
    appTitle.textsize(32);


	// customize category group
	category.box(fltk::ENGRAVED_BOX);
	category.labeltype(fltk::ENGRAVED_LABEL);
	category.labelsize(18);
	category.textsize(18);

	fltk::register_images();
	motorcycleBtn.callback(cb_categoryBtn, this);
	carBtn.callback(cb_categoryBtn, this);
	truckBtn.callback(cb_categoryBtn, this);
	busBtn.callback(cb_categoryBtn, this);
}

MainMenuView::~MainMenuView() {
	// TODO Auto-generated destructor stub
}

TestPropertiesModel* MainMenuView::model() { return ((TestPropertiesModel*)pModel); }

void MainMenuView::attach() {
	getFacade()->attachModel(11,AppModel::getInstance()->getDB()->getCategory(CAR_CATEGORYMODEL_ID));
	getFacade()->attachModel(12,AppModel::getInstance()->getDB()->getCategory(MOTORCYCLE_CATEGORYMODEL_ID));
	getFacade()->attachModel(13,AppModel::getInstance()->getDB()->getCategory(TRUCK_CATEGORYMODEL_ID));
	getFacade()->attachModel(14,AppModel::getInstance()->getDB()->getCategory(BUS_CATEGORYMODEL_ID));

	getFacade()->getModel(11)->setView(&carBtn);
	getFacade()->getModel(12)->setView(&motorcycleBtn);
	getFacade()->getModel(13)->setView(&truckBtn);
	getFacade()->getModel(14)->setView(&busBtn);
}

void MainMenuView::cb_categoryBtn(Widget* v, void *) { // static method
  ((MainMenuView*)(v->parent()))->cb_categoryBtn_i((Button*)v);
}

#include <cstdio>

void MainMenuView::cb_categoryBtn_i(Button* btn) {
		CategoryModel* pCM = dynamic_cast<CategoryModel*>((dynamic_cast<View*>(btn))->model());
		std::cout << "Category Selected: " << pCM->getCID() << ". " << pCM->getLabel() << std::endl;
		std::cout << "Category Model: " << model() << ". " << pCM->getLabel() << std::endl;
		AppModel::getInstance()->getTestProperties()->setCategory(pCM);
		AppModel::getInstance()->runTest();

}
