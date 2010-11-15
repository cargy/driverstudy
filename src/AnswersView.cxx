/*
 * AnswersView.cxx
 *
 *  Created on: Aug 2, 2010
 *      Author: krizz
 */

#include "AnswersView.h"
#include <fltk/SharedImage.h>

using namespace fltk;

AnswersView::AnswersView(int x, int y, int w, int h, const char* l):
Group(x,y,w,h,l),
View()
{
	size = 2;
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
		answerBtn[i] = new RadioButton(5,rb_y,w()-space,rb_height,"");
		answerBtn[i]->copy_label(model()->question()->getAnswer(i).c_str());
		answerBtn[i]->buttonbox(fltk::RSHADOW_BOX);
		answerBtn[i]->labelsize(16);
		answerBtn[i]->textsize(16);
		answerBtn[i]->callback(cb_answerBtn, this);
		answerBtn[i]->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);

		if (model()->completed())
		{
			answerBtn[i]->box(fltk::NO_BOX);
			answerBtn[i]->image(NULL);
			answerBtn[i]->image(fltk::SharedImage::get("icons/wrong_24x24.png"));
		}

		add(answerBtn[i]);

		rb_y = (answerBtn[i]->y() + answerBtn[i]->h() + space);
	}

	if (model()->completed())
	{
		answerBtn[model()->question()->getSelectedAnswer()]->labelcolor(fltk::color(190,47,10));
		answerBtn[model()->question()->getCorrectAnswer()]->labelcolor(fltk::color(81,118,17));
		answerBtn[model()->question()->getCorrectAnswer()]->image(fltk::SharedImage::get("icons/tick_24x24.png"));
	}

	if ( model()->question()->getSelectedAnswer() > -1 && !model()->completed() )
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
}
