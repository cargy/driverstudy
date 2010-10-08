/*
 * LanguageModel.cxx
 *
 *  Created on: Sep 27, 2010
 *      Author: krizz
 */

#include "LanguageModel.h"
using namespace std;

LanguageModel::LanguageModel(int lid, string code, string shortcode, string label) {
	// TODO Auto-generated constructor stub
	lid_ = lid;
	code_ = code;
	shortcode_ = shortcode;
	label_ = label;
}

LanguageModel::~LanguageModel() {
	// TODO Auto-generated destructor stub
}

int LanguageModel::getLID() { return lid_;}
void LanguageModel::setLID(int lid) { lid_ = lid; }
string LanguageModel::getLabel() { return label_; }
void LanguageModel::setLabel(string label) { label_ = label; }
string LanguageModel::getCode() { return code_; }
void LanguageModel::setCode(string code) { code_ = code; }
string LanguageModel::getShortCode() { return shortcode_; }
void LanguageModel::setShortCode(string shortcode) { shortcode_ = shortcode; }
