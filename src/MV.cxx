/*
 * Model.cxx
 *
 *  Created on: Jul 24, 2010
 *      Author: krizz
 */

#include "MV.h"
#include <cstdlib>

Model::Model() {
	view_cnt = 0;
}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void Model::setView(View *pv) {
	if (view_cnt < MAX_VIEWS) {
		pview[view_cnt] = pv;
		pv->setModel(this);
		view_cnt++;
	}
}

void Model::changed(void) {
	for (int i = 0; i < view_cnt; i++) {
		pview[i]->update();
	}
}

int Model::lol(void) {
	return 5;
}

View::View() {
	pModel = NULL;
}

View::View(Model* pM) {
	pM->setView(this);
}

View::~View() {
	// TODO Auto-generated destructor stub
}

void View::setModel(Model *pM) {
	pModel = pM;
}

Model* View::model() {
	return pModel;
}

void View::update() {
}
