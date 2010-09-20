/*
 * mvmain.cxx
 *
 *  Created on: Jul 25, 2010
 *      Author: krizz
 */

#include "Facade.h"
#include "AppModel.h"
#include "AppView.h"
#include <fltk/run.h>

int main(int argc, char** argv)
{
	Facade* f = new Facade();
	AppModel * appM = new AppModel();
	f->attachModel(APPMODEL_ID, appM);
	f->attachView(APPVIEW_ID, new AppView(fltk::USEDEFAULT, fltk::USEDEFAULT,800,600,appM->getappTitle()) );

	f->setViewToModel(APPMODEL_ID, APPVIEW_ID);

	((AppView*)f->getView(APPVIEW_ID))->show();

	return fltk::run();
}
