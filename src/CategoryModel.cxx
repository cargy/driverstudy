/*
 * CategoryModel.cxx
 *
 *  Created on: Sep 2, 2010
 *      Author: krizz
 */

#include "CategoryModel.h"
#include "config.h"

using namespace std;

CategoryModel::CategoryModel(int cid, string label, int questionnaireNo, int amountOfTestQuestions, int time, string image):
Model()
{
	cid_ = cid;
	label_ = label;
	questionnaireNo_ = questionnaireNo;
	amountOfTestQuestions_ = amountOfTestQuestions;
	time_ = time;
	image_ = image;
}

CategoryModel::~CategoryModel() {
	// TODO Auto-generated destructor stub
}

int CategoryModel::getCID() { return cid_; }

string CategoryModel::getLabel() { return _(label_.c_str()); }

int CategoryModel::getTime() { return time_; }

int CategoryModel::getAmountOfTestQuestions() { return amountOfTestQuestions_; }
void CategoryModel::setQuestionnaireNo(int questionnaireNo) { questionnaireNo_ = questionnaireNo; }
int CategoryModel::getQuestionnaireNo() { return questionnaireNo_; }
void CategoryModel::setImage(string image) { image_ = image; }
string CategoryModel::getImage() { return image_; }

