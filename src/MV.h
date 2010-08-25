/*
 * Model.h
 *
 *  Created on: Jul 24, 2010
 *      Author: krizz
 */

#ifndef MV_H_
#define MV_H_
#define MAX_VIEWS 10

#include <cstdlib>
#include "Facade.h"

class Facade;
class View;
class Model {
private:
	View *pview[MAX_VIEWS];
	int view_cnt;
	Facade *_facade;

protected:
	void changed();

public:
	Model();
	~Model();
	int lol();
	void setFacade(Facade * const facade);
	Facade *getFacade() const;
	void setView(View *pw);
};

class View {
protected:
	Model* pModel;

public:
	View();
	View(Model* pM);
	~View();
	virtual void update();
	virtual void onShow();
	void setFacade(Facade * const facade);
	Facade *getFacade() const;
	void setModel(Model *pM);
	virtual void attach();
	Model* model();

private:
	Facade *_facade;

};

#endif /* MV_H_ */
