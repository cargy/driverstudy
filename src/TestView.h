/*
 * TestView.h
 *
 *  Created on: Aug 11, 2010
 *      Author: krizz
 */

#ifndef TESTVIEW_H_
#define TESTVIEW_H_

#include "MV.h"
#include <fltk/Group.h>
#include "TestModel.h"
#include "QuestionView.h"

#define TESTVIEW_ID 5

class TestView: public fltk::Group, public View {
private:
	QuestionView question;

public:
	TestView(int x,int y,int w,int h, const char * l = 0);
	~TestView();
	void update();
	TestModel* model();
	//void setModel(Model* pM);
	virtual void attach();
	virtual void modelAttached();
};

#endif /* TESTVIEW_H_ */
