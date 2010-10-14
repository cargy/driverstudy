/*
 * CategoryBtnView.cxx
 *
 *  Created on: Sep 4, 2010
 *      Author: krizz
 */

#include "CategoryBtnView.h"
#include "CategoryModel.h"
#include <fltk/Image.h>
#include <fltk/SharedImage.h>

using namespace fltk;
using namespace std;

CategoryBtnView::CategoryBtnView(int x, int y, int w, int h, const char* l):
Button(x, y, w, h, l),
View()
{
	align((fltk::RESIZE_FIT | fltk::ALIGN_INSIDE));
}

CategoryBtnView::~CategoryBtnView() {
	// TODO Auto-generated destructor stub
}

void CategoryBtnView::modelAttached()
{
	CategoryModel* category = ((CategoryModel*)pModel);

	copy_label(category->getLabel().c_str());
	image ( fltk::SharedImage::get(category->getImagePath().c_str()));
}

int CategoryBtnView::getCID() { return cid_; }
