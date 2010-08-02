/*
 * mvmain.cxx
 *
 *  Created on: Jul 25, 2010
 *      Author: krizz
 */

#include "AppModel.h"
#include "AppView.h"
#include <fltk/run.h>

int main(int argc, char** argv)
{
	AppModel* appM = new AppModel();
	AppView* appV = new AppView(fltk::USEDEFAULT, fltk::USEDEFAULT,800,600,appM->getappTitle());

	appM->setView(appV);

	appV->show();

	return fltk::run();
}
