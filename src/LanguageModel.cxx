/*
 * LanguageModel.cxx
 *
 *  Created on: Sep 27, 2010
 *      Author: krizz
 */

#include "LanguageModel.h"
using namespace std;

LanguageModel::LanguageModel(int lid, std::string label) {
	// TODO Auto-generated constructor stub
	lid_ = lid;
	label_ = label;
}

LanguageModel::~LanguageModel() {
	// TODO Auto-generated destructor stub
}

int LanguageModel::getLID() { return lid_;}
void LanguageModel::setLID(int lid) { lid_ = lid; }
string LanguageModel::getLabel() { return label_; }
void LanguageModel::setLabel(string label) { label_ = label; }
