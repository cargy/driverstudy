/*
 * TestPropertiesModel.h
 *
 *  Created on: Sep 28, 2010
 *      Author: krizz
 */

#ifndef TESTPROPERTIESMODEL_H_
#define TESTPROPERTIESMODEL_H_

#include "MV.h"
#include "CategoryModel.h"
#include "LanguageModel.h"

class TestPropertiesModel: public Model {
private:
	CategoryModel* category_;
	LanguageModel* language_;

public:
	TestPropertiesModel();
	virtual ~TestPropertiesModel();
	void setCategory(CategoryModel* category);
	CategoryModel* getCategory();
	void setLanguage(LanguageModel* language);
	LanguageModel* getLanguage();
};

#endif /* TESTPROPERTIESMODEL_H_ */
