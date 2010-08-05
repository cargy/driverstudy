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
	update();

}

AnswersView::~AnswersView() {
	// TODO Auto-generated destructor stub
}

void AnswersView::update()
{
	clear();

	int rb_height = 0;
	int rb_y = 10;
  	const int space = 10;
  	rb_height = ( ( h() - (size)* space ) / size ) - 3;

	for (int i=0; i<size; i++)
	{
		answerBtn[i] = new RadioButton(5,rb_y,w()-space,rb_height,"booo");
		answerBtn[i]->buttonbox(fltk::RSHADOW_BOX);
		answerBtn[i]->labelsize(16);
		answerBtn[i]->textsize(16);
		answerBtn[i]->callback(cb_answerBtn, this);
		answerBtn[i]->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
		add(answerBtn[i]);

		rb_y = (answerBtn[i]->y() + answerBtn[i]->h() + space);
	}
	init_sizes();
}

void AnswersView::cb_answerBtn(Widget* v, void *) { // static method
  ((AnswersView*)(v->parent()))->cb_answerBtn_i((RadioButton*)v );
}

void AnswersView::cb_answerBtn_i(RadioButton* btn) {

}
