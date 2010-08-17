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

void TestView::update() {
	// TODO Auto-generated destructor stub
	//question.update();
	question.setQuestionNumber(model()->cursor(), model()->size());
	question.setQuestion(model()->question()->title());
	question.setAnswers(model()->question());

}

TestModel* TestView::model() {
	return ((TestModel*)pModel);
}
