/*
 * Facade.h
 *
 *  Created on: Aug 25, 2010
 *      Author: krizz
 */

#ifndef FACADE_H_
#define FACADE_H_

#include <vector>
#include <map>
#include "MV.h"

class Model;
class View;

class Facade {
public:
	Facade();
	~Facade();
	void attachView(int key, View * const view);
	View *getView(int key);
	void attachModel(int key, Model * const model);
    Model *getModel(int key);
    void setViewToModel(int modelKey, int viewKey);

private:
	typedef std::map<int, View *> ViewList;
	ViewList _views;
	typedef std::map<int, Model *> ModelList;
	ModelList _models;
};

#endif /* FACADE_H_ */
