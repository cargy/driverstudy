/*
 * ViewContainer.cxx
 *
 *  Created on: Jul 27, 2010
 *      Author: krizz
 */

#include "ContainerView.h"
#include <fltk/Window.h>
#include <fltk/draw.h>
#include <fltk/Cursor.h>
#include <fltk/events.h>

ContainerView::ContainerView(int x,int y,int w,int h, const char * l, bool begin):
Group(x,y,w,h,l,begin),
View(),
value_(0)
{
	transitioning_ = false;
	interval_ = 0.01f;
	step_ = (float)w / (float)STEP_FACTOR;
	box(THIN_UP_BOX);
	end();


	mainMenuView_ = new MainMenuView(0,0,w,h, "Main Menu");
	testView_ = new TestView(0,0,w,h, "Test View");

	testResultsView_ = new TestResultsView(0,0,w,h, "Results View");
	add(mainMenuView_);
	add(testView_);
	add(testResultsView_);
	prev_ = next_ = NULL;



}

void ContainerView::attach()
{
	if (!getFacade())
		return;
	getFacade()->attachView(MAINMENUVIEW_ID, mainMenuView_);
	getFacade()->attachView(TESTVIEW_ID, testView_);
	getFacade()->attachView(TESTRESULTSVIEW_ID, testResultsView_);
}

void ContainerView::modelAttached()
{
	model()->getTestProperties()->setView(mainMenuView_);
}

ContainerView::~ContainerView() {
	// TODO Auto-generated destructor stub
}

void ContainerView::draw() {
  if (!value()) value(children() ? child(0) : 0);
  Group::draw();
}

void ContainerView::next() {
  int num_kids, i;
  Widget	*kids;

  if ((num_kids = children()) == 0)  return;
  for (kids = child(0),i=0; i<num_kids; kids=child(++i))
    if (kids->visible()) break;
  if (i < num_kids-1)  {kids->hide(); value(child(i+1));}
}

void ContainerView::prev() {
  int	         num_kids, i;
  Widget	*kids;

  if ((num_kids = children()) == 0)  return;
  for (kids = child(0),i=0; i<num_kids; kids=child(++i))
    if (kids->visible()) break;
  if (i > 0 && i < num_kids) {kids->hide(); value(child(i-1));}
}

void ContainerView::value(Widget *kid) {
  int num_kids, i;

  value_=kid;
  //prev_ = next_ = NULL;

  if ((num_kids = children()) == 0)  return;

  for (i=0; i<num_kids; i++)
    if (child(i) != kid)  child(i)->hide();
    else {
    	kid->clear();
    	kid->activate();
    }

  // This will restore the mouse pointer to the window's default cursor
  // whenever the wizard pane is changed.  Otherwise text widgets that
  // show the next pane may leave the cursor set to the I beam, etc...
  if (window()) window()->cursor(CURSOR_DEFAULT);

}

AppModel* ContainerView::model() {
	return ((AppModel*)pModel);
}


int ContainerView::handle(int event) {

	if (fltk::Group::handle(event)) return 1;

	switch (event)
	{
	case SHOW:
		remove_timeout();
		if (!transitioning_) break;
	case TIMEOUT:
		if ( prev_ < next_ )
			move_left();
		else
			move_right();
		break;
	case HIDE:
		remove_timeout();
	    break;
	default:
		return 0;
	}

	return 1;
	//return fltk::Group::handle(event);
}

void ContainerView::move_left() {
	if ( prev_->x() > -prev_->w()) {

		// easing effect
		if ( -prev_->x() >  prev_->parent()->w()*(0.65f)) {
			//std::cout << -prev_->x() << " > " << prev_->parent()->w()*(0.65f) << " step:" << step_ << std::endl;
			if ( step_ * (0.08f) > 1 ) step_-= step_ * (0.08f);
			else step_ = 3;
		}

		// fix step_
		if (prev_->x()-step_ < -prev_->w())
			step_ =  (float)prev_->r();

		prev_->x((int)(prev_->x()-step_));
		next_->x(prev_->r());
		if (!next_->visible()) next_->show();
		redraw();
		add_timeout(interval_);
	}else{
		transitioning_ = false;
		remove_timeout();
		if (prev_) prev_->x(0);
		value(next_);
		relayout();
		redraw();

	}
}

void ContainerView::move_right() {
	if (prev_ && prev_->x() < prev_->parent()->w()) {

		// easing effect
		if ( prev_->x() >  prev_->parent()->w()*(0.65f)) {
			//std::cout << prev_->x() << " > " << prev_->parent()->w()*(0.65f) << " step:" << step_ << std::endl;
			if ( step_ * (0.08f) > 1 ) step_-= step_ * (0.08f);
			else step_ = 3;
		}

		// fix step
		if ( prev_->x()+step_ > (float)(prev_->parent()->w()))
			step_ = (float)(prev_->parent()->w() - prev_->x());

		prev_->x((int)(prev_->x()+step_));
		next_->x(prev_->x() - next_->w());
		if (!next_->visible()) next_->show();
		redraw();
		add_timeout(interval_);
	}else{
		transitioning_ = false;
		remove_timeout();
		if (prev_) prev_->x(0);
		value(next_);
		relayout();
		redraw();

	}
}

void ContainerView::showPage(int i) {
	if ( children() == 0 || child(i) == NULL )  return;
	if (transitioning_) return;

	slide(child(i));

}

void ContainerView::update()
{
	//if (AppModel::getInstance()->getpage() == 1) ((View*)child(1))->update();
}

void ContainerView::slide(Widget *kid) {
  int num_kids;

  prev_ = value_;
  next_ = kid;
  prev_->deactivate();
  next_->deactivate();
  step_ = (float)w() / (float)STEP_FACTOR;
  if ((num_kids = children()) == 0)  return;

  if (kid == value_ )
	  value(kid);
  else {
	  transitioning_ = true;
	  add_timeout(interval_);
  }

}

TestView* ContainerView::getTestView() { return testView_; }


