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
	toolbar = new ToolbarView(0,h - 80 - statusBar.h(),w,80,"Toolbar");
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
#ifndef _WIN32
	static unsigned img[] = {
			22, 22,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x7f4994b7, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00,
			0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00, 0x00ffff00,0x00ffff00, 0x00ffff00
	};

	icon((char*)img);
#endif

}

void AppView::attach()
{
	getFacade()->attachView(CONTAINERVIEW_ID, container);
}

void AppView::modelAttached()
{

	model()->setView(container);
	std::cout << "Attach TestProperties to LanguageBar" << std::endl;
	model()->getTestProperties()->setView(&toolbar->languageMenu);
}

AppView::~AppView() {
}

AppModel* AppView::model() {
	return ((AppModel*)pModel);
}

void AppView::cb_exit(fltk::Widget* pWdg, void* p) {
	AppModel::getInstance()->quit();
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
	//toolbar->opened(!model()->getpage());
	//container->update();
	if (model()->getpage())
		toolbar->quitBtn.copy_label("Back");
	else
		toolbar->quitBtn.copy_label("Quit");

	//container->draw();
	sprintf(buf, "%s page: %d", container->value()->label(), model()->getpage());
	statusBar.set(buf);

	statusBar.set(model()->getStuatusBarMsg(),  StatusBarGroup::SBAR_LEFT);
}
