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

class View;
class Model {
private:
	View *pview[MAX_VIEWS];
	int view_cnt;

protected:
	void changed();

public:
	Model();
	~Model();
	int lol();
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
	void setModel(Model *pM);
	Model* model();

};

#endif /* MV_H_ */
