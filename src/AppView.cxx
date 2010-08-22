/*
 * AppView.cxx
 *
 *  Created on: Jul 25, 2010
 *      Author: krizz
 */

#include "AppView.h"
#include "AppModel.h"
#include "MainMenuView.h"
#include "TestView.h"

using namespace fltk;

AppView::AppView(int x, int y, int w, int h, const char* l):
Window(x, y, w, h, l),
View(),
group(0,0,w,580),
statusBar(20)
//toolbar(0,500,800,80,"ToolBar"),
//container(0,0,800, 500)

{


	add(group);
	toolbar = new ToolbarView(0,h - 80 - statusBar.h(),w,80,"ToolBar");
	container = new ContainerView(0,0,w, h - toolbar->h() - statusBar.h(),"Container View", false);

	group.add(container);
	group.add(toolbar);
	group.resizable(container);
	resizable(group);
	add(statusBar);

	callback(cb_exit);
	fullscreen_status = false;

	statusBar.child_box(FLAT_BOX);
	statusBar.set("Hello!",  StatusBarGroup::SBAR_LEFT);


}

AppView::~AppView() {
}

AppModel* AppView::model() {
	return ((AppModel*)pModel);
}

void AppView::cb_exit(fltk::Widget* pWdg, void* p) {
	exit(0);
}
/*
void AppView::cb_fullscreenBtn(fltk::Widget* pWdg, void* p) {
	((AppView*)(p))->pModel->setfullscreen(true);
}
*/

inline void AppView::cb_fullscreenBtn_i(ToggleButton* fullscreenBtn) {
	model()->fullscreen_toggle();
}
void AppView::cb_fullscreenBtn(Widget* w, void* v) {
  ((AppView*)v)->cb_fullscreenBtn_i((ToggleButton*)w);

}
#include <cstdio>
#include <fltk/run.h>

void move(void* v) {
  //printf("TICK: %s\n",((Button*)v)->label());
	Button* btn = (Button*)v;
  btn->x(btn->x()+20);
  btn->parent()->redraw();
  //fltk::check();

  if (btn->x() < 790)
	  repeat_timeout(0.05f,move,v);
}

inline void AppView::cb_nextBtn_i(Button* btn) {
	//model()->nextpage();
	//add_timeout(0.5,move);
	//add_timeout(0.01f, move, quitBtn);
	//quitBtn->x(quitBtn->x()+1);
}
void AppView::cb_nextBtn(Widget* w, void* v) {
  ((AppView*)v)->cb_nextBtn_i((Button*)w);

}

inline void AppView::cb_prevBtn_i(Button* btn) {
	model()->gotoMainMenu();
}
void AppView::cb_prevBtn(Widget* w, void* v) {
  ((AppView*)v)->cb_prevBtn_i((Button*)w);

}


void AppView::update() {

	if ( model()->isfullscreen() && !fullscreen_status)
	{
		fullscreen();
		fullscreen_status = true;
		toolbar->fullscreenBtn.value(model()->isfullscreen());
	}

	else if (!model()->isfullscreen() && fullscreen_status)
	{
		int x = model()->getx();
		int y = model()->gety();
		int w = model()->getw();
		int h = model()->geth();
		fullscreen_off(x,y,w,h);
		fullscreen_status = false;
		//model()->setpos(window->x(),window->y());
		//model()->setsize(window->w(),window->h());
		toolbar->fullscreenBtn.value(model()->isfullscreen());

	}


	char buf[100];

	container->showPage(model()->getpage());
	//container->update();

	//container->draw();
	sprintf(buf, "%s page: %d", container->value()->label(), model()->getpage());
	statusBar.set(buf);

	statusBar.set(model()->getStuatusBarMsg(),  StatusBarGroup::SBAR_LEFT);
}
