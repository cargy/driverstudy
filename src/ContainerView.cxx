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

#include "MainMenuView.h"
#include "HomeView.h"
#include "TestView.h"

ContainerView::ContainerView(int x,int y,int w,int h, const char * l, bool begin):
Group(x,y,w,h,l,begin), value_(0),
View()
{
	transitioning_ = false;
	interval_ = 0.01f;
	box(THIN_UP_BOX);
	end();

	add(new MainMenuView(0,0,w,h, "Main Menu"));
	//add(new HomeView(0,0,w,h, "Choices"));
	//add(new QuestionView(0,0,w,h, "Question View"));
	add(new TestView(0,0,w,h, "Test View"));

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
    if (child(i) != kid)  child(i)->hide(); else kid->show();

  // This will restore the mouse pointer to the window's default cursor
  // whenever the wizard pane is changed.  Otherwise text widgets that
  // show the next pane may leave the cursor set to the I beam, etc...
  if (window()) window()->cursor(CURSOR_DEFAULT);
}

AppModel* ContainerView::model() {
	return ((AppModel*)pModel);
}


int ContainerView::handle(int event) {


	switch (event)
	{
	case TIMEOUT:
		if ( prev_ < next_ )
			move_left();
		else
			move_right();
		break;

	}

	if (fltk::Group::handle(event)) return 1;
	else return 0;
	//return fltk::Group::handle(event);
}

void ContainerView::move_left() {
	if ( prev_->x() > -prev_->w()) {
		prev_->x(prev_->x()-20);
		next_->x(prev_->x() + prev_->w());
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
		prev_->x(prev_->x()+20);
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
	slide(child(i));

	if (i == 1)  {
		AppModel::getInstance()->currentTest->setView((View*)child(i));
		AppModel::getInstance()->currentTest->next();
	}

}

void ContainerView::update()
{
	//if (AppModel::getInstance()->getpage() == 1) ((View*)child(1))->update();
}

void ContainerView::slide(Widget *kid) {
  int num_kids, i;

  prev_ = value_;
  next_ = kid;
  if ((num_kids = children()) == 0)  return;

  if (kid == value_ )
	  value(kid);
  else {
	  transitioning_ = true;
	  add_timeout(interval_);
  }

}


