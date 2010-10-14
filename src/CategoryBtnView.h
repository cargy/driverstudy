/*
 * CategoryBtnView.h
 *
 *  Created on: Sep 4, 2010
 *      Author: krizz
 */

#ifndef CATEGORYBTNVIEW_H_
#define CATEGORYBTNVIEW_H_

#include "MV.h"
#include <fltk/Button.h>

class CategoryBtnView: public fltk::Button, public View {
private:
	int cid_;

public:
	CategoryBtnView(int x, int y, int w, int h, const char* l);
	virtual ~CategoryBtnView();
	int getCID();
	virtual void modelAttached();
};

#endif /* CATEGORYBTNVIEW_H_ */
