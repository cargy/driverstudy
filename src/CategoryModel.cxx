/*
 * CategoryModel.cxx
 *
 *  Created on: Sep 2, 2010
 *      Author: krizz
 */

#include "CategoryModel.h"
#include "config.h"

using namespace std;

CategoryModel::CategoryModel(int cid, string label, int amountOfTestQuestions, int time):
Model()
{
	cid_ = cid;
	label_ = label;
	amountOfTestQuestions_ = amountOfTestQuestions;
	time_ = time;
}

CategoryModel::~CategoryModel() {
	// TODO Auto-generated destructor stub
}

int CategoryModel::getCID() { return cid_; }

string CategoryModel::getLabel() { return _(label_.c_str()); }

int CategoryModel::getTime() { return time_; }

int CategoryModel::getAmountOfTestQuestions() { return amountOfTestQuestions_; }
