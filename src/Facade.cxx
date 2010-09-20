/*
 * Facade.cxx
 *
 *  Created on: Aug 25, 2010
 *      Author: krizz
 */

#include "Facade.h"

Facade::Facade() {
	// TODO Auto-generated constructor stub


}

Facade::~Facade() {

	for (ViewList::iterator iter = _views.begin();
            iter != _views.end();
            iter++) {
        if (iter->second) delete iter->second;
        iter->second = NULL;
    }
    for (ModelList::iterator iter = _models.begin();
            iter != _models.end();
            iter++) {
        if (iter->second) delete iter->second;
        iter->second = NULL;
    }

}

/**
 * Attach a view to the facade.
 *
 * @param key   Key to attach the view with.
 * @param view  View to attach.
 */
void Facade::attachView(int key, View * const view)
{
    ViewList::iterator iter = _views.find(key);
    if (iter != _views.end()) {
        delete (iter->second);
    }
    view->setFacade(this);
    view->attach();
    _views[key] = view;
}

/**
 * Get a view that has been attached.
 *
 * @param key   Key of the view to return.
 * @return      View associated with the key.
 */
View *Facade::getView(int key)
{
    return _views[key];
}

/**
 * Attach a model to the facade.
 *
 * @param key   Key to attach the model with.
 * @param model Model to attach.
 */
void Facade::attachModel(int key, Model * const model)
{
    ModelList::iterator iter = _models.find(key);
    if (iter != _models.end()) {
        delete (iter->second);
    }
    model->setFacade(this);
    _models[key] = model;
}

/**
 * Get a model that has been attached.
 *
 * @param key   Key of the model to return.
 * @return      Model associated with the key.
 */
Model *Facade::getModel(int key)
{
    return _models[key];
}

void Facade::setViewToModel(int modelKey, int viewKey)
{
	getModel(modelKey)->setView(getView(viewKey));
}

