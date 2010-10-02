/*
 * TestPropertiesModel.cxx
 *
 *  Created on: Sep 28, 2010
 *      Author: krizz
 */

#include <iostream>
#include <exception>
using namespace std;

class TestPropertiesException: public exception
{
  virtual const char* what() const throw()
  {
    return "TestProperty Model is not complete.";
  }
} NonCompleteTestPropertyModel;


#include "TestPropertiesModel.h"

TestPropertiesModel::TestPropertiesModel(): Model() {
	// TODO Auto-generated constructor stub
	category_ = NULL;
	language_ = NULL;

}

TestPropertiesModel::~TestPropertiesModel() {
	// TODO Auto-generated destructor stub
}

void TestPropertiesModel::setCategory(CategoryModel* category) { category_ = category; }
CategoryModel* TestPropertiesModel::getCategory() { return category_; }
void TestPropertiesModel::setLanguage(LanguageModel* language) { language_ = language; }
LanguageModel* TestPropertiesModel::getLanguage() { if (language_) return language_; else throw  NonCompleteTestPropertyModel;}

