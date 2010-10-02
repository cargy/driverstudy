/*
 * TestView.cxx
 *
 *  Created on: Aug 11, 2010
 *      Author: krizz
 */

#include "TestView.h"
#include "QuestionView.h"

using namespace fltk;

TestView::TestView(int x,int y,int w,int h, const char * l):
Group(x,y,w,h,l,true),
View(),
question(x,y,w,h,l)
{
	// TODO Auto-generated constructor stub
	//add(new QuestionView(0,0,w,h, "Test View1"));
	end();

}
#include <cstdio>
TestView::~TestView() {
	// TODO Auto-generated destructor stub
	printf("TestView was destoyed");
}

void TestView::modelAttached()
{
	model()->setView(&question);
	model()->setView(question.answersView());
	question.timerBar.starttime(model()->time());
}

void TestView::update() {
	//model()->setView(&question);
	//model()->setView(question.answersView());
	if (model()->isRunning() != question.timerBar.status() )
	{
		if (model()->isRunning()) {
			//question.timerBar.starttime(model()->time());
			question.timerBar.start();
		}
		else question.timerBar.stop();
	}

}

void TestView::attach()
{
	getFacade()->attachView(QUESTIONVIEW_ID, &question);
	getFacade()->attachView(ANSWERSVIEW_ID, question.answersView());
}
/*
void TestView::setModel(Model* pM) {
	pM->setView(this);
	pM->setView(&question);
	pM->setView(question.answersView());
}
*/
TestModel* TestView::model() {
	return ((TestModel*)pModel);
}

