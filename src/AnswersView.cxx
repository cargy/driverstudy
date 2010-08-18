/*
 * AnswersView.cxx
 *
 *  Created on: Aug 2, 2010
 *      Author: krizz
 */

#include "AnswersView.h"
#include "answer.h"

using namespace fltk;

AnswersView::AnswersView(int x, int y, int w, int h, const char* l):
Group(x,y,w,h,l),
View()
{
	size = 2;
	Answer* testAnswer[size];
	//update();

}

AnswersView::~AnswersView() {
	// TODO Auto-generated destructor stub
}

TestModel* AnswersView::model() {
	return ((TestModel*)pModel);
}

#include <cstdio>
void AnswersView::update()
{
	if (!visible()) return;
	clear();
	size = model()->question()->getAOA();

	int rb_height = 0;
	int rb_y = 10;
  	const int space = 10;
  	rb_height = ( ( h() - (size)* space ) / size ) - 3;

	for (int i=0; i<size; i++)
	{
		answerBtn[i] = new RadioButton(5,rb_y,w()-space,rb_height,model()->question()->getAnswer(i));
		answerBtn[i]->buttonbox(fltk::RSHADOW_BOX);
		answerBtn[i]->labelsize(16);
		answerBtn[i]->textsize(16);
		answerBtn[i]->callback(cb_answerBtn, this);
		answerBtn[i]->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
		add(answerBtn[i]);

		rb_y = (answerBtn[i]->y() + answerBtn[i]->h() + space);
	}
	printf("model selected answer:%i\n",model()->question()->getSelectedAnswer());
	if (model()->question()->getSelectedAnswer() > -1)
		answerBtn[model()->question()->getSelectedAnswer()]->state(true);
	init_sizes();
}

int AnswersView::selectedRB()
{
	for (int i=0; i<size; i++)
	{
	  if ( answerBtn[i]->visible() && answerBtn[i]->state() )
		return i;
	}
	return -1;
}
void AnswersView::cb_answerBtn(Widget* btn, void* v) { // static method
  ((AnswersView*)v)->cb_answerBtn_i((RadioButton*)btn );
}


void AnswersView::cb_answerBtn_i(RadioButton* btn) {
	if (selectedRB() > -1) model()->selectAnswerOfCurrentQuestion(selectedRB());
	printf("selected:%i - mode:%i\n", selectedRB(), model()->question()->getSelectedAnswer());
}
