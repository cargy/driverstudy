/*
 * CategoryBtnView.cxx
 *
 *  Created on: Sep 4, 2010
 *      Author: krizz
 */

#include "CategoryBtnView.h"
#include <fltk/Image.h>
#include <fltk/SharedImage.h>

using namespace fltk;

CategoryBtnView::CategoryBtnView(int x, int y, int w, int h, const char* l):
Button(x, y, w, h, l),
View()
{
	align((fltk::RESIZE_FIT | fltk::ALIGN_INSIDE));
}

CategoryBtnView::~CategoryBtnView() {
	// TODO Auto-generated destructor stub
}

void CategoryBtnView::attach() {
	image( fltk::SharedImage::get("icons/motorcycle_256x182.png") );
}

int CategoryBtnView::getCID() { return cid_; }
