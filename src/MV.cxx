/*
 * Model.cxx
 *
 *  Created on: Jul 24, 2010
 *      Author: krizz
 */

#include "MV.h"
#include "log.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <typeinfo>

Model::Model() {
	view_cnt = 0;
	_facade = NULL;
	for (int i=0; i< MAX_VIEWS; i++) pview[i] = NULL;
	FILE_LOG(logDEBUG4) << "New Model Created: " << this;
	//printf("New Model Created of Type: %d: %i Views\n",typeid(this).name().c_str().view_cnt);
}


Model::~Model() {
	// TODO Auto-generated destructor stub
}

/**
 * Set the facade to be used.
 *
 * @param facade    Facade to use.
 */
void Model::setFacade(Facade * const facade)
{
    _facade = facade;
}

/**
 * Get the facade being used.
 *
 * @return  Facade being used.
 */
Facade *Model::getFacade() const
{
    return _facade;
}

void Model::setView(View *pv) {
	if (view_cnt < MAX_VIEWS) {
		pview[view_cnt++] = pv;
		pv->setModel(this);
		FILE_LOG(logDEBUG4) << "Added View " << view_cnt << " <" << typeid(*pv).name() << "> on Model:" << this;
	}else{ FILE_LOG(logWARNING) << "setView(): Max Views (" << MAX_VIEWS << "), reached\n"; }
}

void Model::changed(void) {
	for (int i = 0; i < view_cnt; i++) {
		if (pview[i] != NULL) pview[i]->update();
	}
}

int Model::lol(void) {
	return 5;
}

View::View() {
	pModel = NULL;
	_facade = NULL;
}


View::View(Model* pM) {
	pM->setView(this);
}

View::~View() {
	// TODO Auto-generated destructor stub
}

/**
 * Set the facade to be used.
 *
 * @param facade    Facade to use.
 */
void View::setFacade(Facade * const facade)
{
    _facade = facade;
}

/**
 * Get the facade being used.
 *
 * @return  Facade being used.
 */
Facade *View::getFacade() const
{
    return _facade;
}

void View::setModel(Model *pM) {
	pModel = pM;
	modelAttached();
}


Model* View::model() {
	return pModel;
}

/**
 * Do any kind of model attachment needed.
 */
void View::attach() {}
void View::modelAttached() { FILE_LOG(logDEBUG4) << "Model Attached to View: " << pModel;}

void View::update() {
}

void View::onShow() {
}
