/*
 * TestView.cxx
 *
 *  Created on: Jul 31, 2010
 *      Author: krizz
 */

#include "QuestionView.h"
#include <fltk/SharedImage.h>

QuestionView::QuestionView(int x, int y, int w, int h, const char* l):
Group(x, y, w, h, l, true/* auto-begin() */),
View(),
leftGroup(5, 5, 450, h-10),
	questionGroup(5, 5, leftGroup.w()-10, leftGroup.h()-10, "Question #/#"),
		questionHolder(5, 20, questionGroup.w()-10, 120, "The actual Question?"),
		answerGroup(5, 145, 430, questionGroup.h() - questionHolder.y() -  questionHolder.h() - 10, "Answers Group"),
rightGroup(leftGroup.w()+5, 5, 340, h-10),
	imageHolder(5,5,rightGroup.w()-10,300),
	controlGroup(5, 310, rightGroup.w()-10, rightGroup.h() - imageHolder.y() - imageHolder.h() - 10),
		timerBar(15, 10, 300, 25),
		validateBtn(15, timerBar.y() + timerBar.h() + 10, 300, 55, "Validate Answer  @+1+"),
		nextBtn(15, validateBtn.y()+validateBtn.h() + 10, 300, 55, "Next Question  @+1>@+1>[]")
{

	leftGroup.add(questionGroup);
	questionGroup.add(questionHolder);
	questionGroup.add(answerGroup);

	resizable(leftGroup);
	//customize leftGroup
	leftGroup.box(fltk::THIN_DOWN_BOX);
    questionGroup.box(fltk::THIN_UP_BOX);
    questionGroup.labeltype(fltk::ENGRAVED_LABEL);
    questionGroup.labelsize(18);
    questionGroup.textsize(18);
    questionGroup.align(fltk::ALIGN_TOP|fltk::ALIGN_INSIDE);

    questionHolder.buttonbox(fltk::DOWN_BOX);
    questionHolder.buttoncolor((fltk::Color)0xffffff00);
    questionHolder.labelsize(16);
    questionHolder.textsize(16);
    questionHolder.align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);

    answerGroup.box(fltk::THIN_DOWN_BOX);
	// customize rightGroup
	rightGroup.box(fltk::THIN_DOWN_BOX);
	rightGroup.add(imageHolder);
	rightGroup.add(controlGroup);
	rightGroup.resizable(controlGroup);
	controlGroup.box(fltk::THIN_UP_BOX);
	nextBtn.callback(cb_nextQuestionBtn, this);
	validateBtn.callback(cb_validateBtn, this);
	controlGroup.add(timerBar);
	controlGroup.add(validateBtn);
	controlGroup.add(nextBtn);
	end();

	preview_mode = false;

}

QuestionView::~QuestionView() {
	// TODO Auto-generated destructor stub
}

TestModel* QuestionView::model() {
	return ((TestModel*)pModel);
}

#include "AppModel.h"
void QuestionView::update() {
	if (model()->completed() != preview_mode)
	{
		preview_mode = model()->completed();
		if (preview_mode)
			setPreviewMode();
		else
			setTestMode();
	}
	setQuestionNumber(model()->cursor(), model()->size());
	setQuestion(model()->question()->title());

	// handle validateBtn
	if (model()->question()->getSelectedAnswer() == -1 )
		validateBtn.deactivate();
	else
		validateBtn.activate();

	// check if there is any other un-validated question
	// to disable/enable nextBtn
	if ( model()->is_next() || model()->completed() ) nextBtn.activate();
	else nextBtn.deactivate();

	setQuestionImage(model()->question());
}

void QuestionView::setQuestionNumber(int qNo, int size) {
	char label[150];
	sprintf(label, _("Question %i/%i"),qNo+1,size);
	questionGroup.copy_label(label);
	questionGroup.redraw_label();
}
void QuestionView::setQuestion(const char* q) {
	questionHolder.label(q);
	questionHolder.redraw_label();
}

void QuestionView::setAnswers(QuestionModel* pQuestion) {
	answerGroup.size = pQuestion->getAOA();

	answerGroup.update();
	for (int i=0; i<answerGroup.size; i++)
	{
		answerGroup.answerBtn[i]->label(pQuestion->getAnswer(i));
	}

}

void QuestionView::setQuestionImage(QuestionModel* pQuestion) {
	// load question image if available
	if ( strcmp(pQuestion->image(), "0") != 0 )
	{
		char imgPath[MAXIMGFILESIZE];
		sprintf(imgPath, "img/%s.jpg",pQuestion->image());

		int i = -1;
		// make imgPath lowercase
		while (imgPath[++i]) imgPath[i] = tolower(imgPath[i]);
	#ifdef	DEBUG
		printf("imgPath = %s\n",imgPath);
	#endif
		if ( !imageHolder.visible() ) imageHolder.show();
		imageHolder.image( fltk::SharedImage::get(imgPath) );
		imageHolder.redraw();
	}
	else
		if ( imageHolder.visible() ) imageHolder.hide();
}

void QuestionView::setTestMode()
{
	// restore setting changed by previewQuestion()
	answerGroup.clear_output();
  	if ( !timerBar.visible() ) timerBar.show();
  	if ( !validateBtn.visible() ) validateBtn.show();

  	preview_mode = false;
}

void QuestionView::setPreviewMode()
{
	answerGroup.set_output();
	timerBar.hide();


	// hide validateBtn we are in preview_mode
	if ( validateBtn.visible() ) validateBtn.hide();

    // activate nextBtn because it's probably
    // deactivated from showQuestion()
	if ( !nextBtn.active() ) nextBtn.activate();
	preview_mode = true;

}
AnswersView* QuestionView::answersView() {
	return &answerGroup;
}

void QuestionView::cb_nextQuestionBtn(Widget* btn, void *v) { // static method
  ((QuestionView*)(v))->cb_nextQuestionBtn_i((Button*)btn);
}

void QuestionView::cb_nextQuestionBtn_i(Button* btn)
{
	if (!model()->completed())
		model()->nextQuestion();
	else
	{
		if (model()->is_nextWrong())
			model()->nextWrongQuestion();
		else
			AppModel::getInstance()->gotoTestResults();
	}

}

void QuestionView::cb_validateBtn(Widget* btn, void *v) { // static method
  ((QuestionView*)(v))->cb_validateBtn_i((Button*)btn);
}

void QuestionView::cb_validateBtn_i(Button* btn) {
	model()->verifyAnswerOfCurrentQuestion();
	if ( model()->completed())
	{
		AppModel::getInstance()->gotoTestResults();
		model()->showResults();
	}
	else
	{
		model()->nextQuestion();
	}
}
