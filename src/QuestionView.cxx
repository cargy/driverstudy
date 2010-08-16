/*
 * TestView.cxx
 *
 *  Created on: Jul 31, 2010
 *      Author: krizz
 */

#include "QuestionView.h"

QuestionView::QuestionView(int x, int y, int w, int h, const char* l):
Group(x, y, w, h, l, true/* auto-begin() */),
View(),
leftGroup(5, 5, 450, h-10),
rightGroup(leftGroup.w()+5, 5, 340, h-10)
{

	leftGroup.box(fltk::THIN_DOWN_BOX);
	leftGroup.begin();
		questionGroup = new Group(5, 5, leftGroup.w()-10, leftGroup.h()-10, "Question #/#");
		questionGroup->begin();
			questionHolder = new Button(5, 20, questionGroup->w()-10, 120, "The actual Question?");
			answerGroup = new AnswersView(5, 145, 430, questionGroup->h() - questionHolder->y() -  questionHolder->h() - 10, "Answers Group");
		questionGroup->end();
	leftGroup.end();

	resizable(leftGroup);
	//customize leftGroup

    questionGroup->box(fltk::THIN_UP_BOX);
    questionGroup->labeltype(fltk::ENGRAVED_LABEL);
    questionGroup->labelsize(18);
    questionGroup->textsize(18);
    questionGroup->align(fltk::ALIGN_TOP|fltk::ALIGN_INSIDE);

    questionHolder->buttonbox(fltk::DOWN_BOX);
    questionHolder->buttoncolor((fltk::Color)0xffffff00);
    questionHolder->labelsize(16);
    questionHolder->textsize(16);
    questionHolder->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);

    answerGroup->box(fltk::THIN_DOWN_BOX);
	// customize rightGroup

	rightGroup.box(fltk::THIN_DOWN_BOX);
	rightGroup.begin();
		imageHolder = new Widget(5,5,rightGroup.w()-10,300);
		controlGroup = new Group(5, 310, rightGroup.w()-10, rightGroup.h() - imageHolder->y() - imageHolder->h() - 10);
		controlGroup->begin();
			timerBar = new TimerProgressBar(15, 10, 300, 25);
			validateBtn = new Button(15, timerBar->y() + timerBar->h() + 10, 300, 55, "Validate Answer  @+1+");
			nextBtn = new Button(15, validateBtn->y()+validateBtn->h() + 10, 300, 55, "Next Question  @+1>@+1>[]");
		controlGroup->end();
	rightGroup.end();


	rightGroup.resizable(controlGroup);
	controlGroup->box(fltk::THIN_UP_BOX);
	validateBtn->callback(cb_validateBtn, this);
	end();

}

QuestionView::~QuestionView() {
	// TODO Auto-generated destructor stub
}
#include "AppModel.h"
void QuestionView::update() {
	questionHolder->copy_label(AppModel::getInstance()->currentTest->next()->title());
	redraw();
}

void QuestionView::cb_validateBtn(Widget* btn, void *v) { // static method
  ((QuestionView*)(v))->cb_validateBtn_i((Button*)btn);
}

void QuestionView::cb_validateBtn_i(Button* btn) {
	//questionHolder.copy_label(AppModel::getInstance()->currentTest->next()->title());
	answerGroup->copy_label("asadsas");
	//questionHolder.redraw_label();
	//questionHolder.hide();
	questionHolder->label(AppModel::getInstance()->currentTest->next()->title());
	redraw();
	printf("question: %s\n", AppModel::getInstance()->currentTest->next()->title());
}
