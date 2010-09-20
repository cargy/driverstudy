/*
 * Model.cxx
 *
 *  Created on: Jul 24, 2010
 *      Author: krizz
 */

#include "MV.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <typeinfo>

Model::Model() {
	view_cnt = 0;
	_facade = NULL;
	std::cout << "New Model Created: " << this << std::endl;
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
		pview[view_cnt] = pv;
		pv->setModel(this);
		std::cout << "Added View " << view_cnt << " <" << typeid(*pv).name() << "> on Model:" << this << std::endl;
		view_cnt++;
	}else{ printf("setView(): Max Views (%i), reached\n", MAX_VIEWS); }
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
void View::modelAttached() { std::cout << "Model Attached to View: " << pModel;}

void View::update() {
}

void View::onShow() {
}
