/*
 * SectionModel.cxx
 *
 *  Created on: Oct 11, 2010
 *      Author: krizz
 */

#include "SectionModel.h"

using namespace std;

SectionModel::SectionModel(int id, CategoryModel* category, string name, string description):
Model()
{
	id_ = id;
	category_ = category;
	name_= name;
	description_ = description;

}

SectionModel::~SectionModel() {
	// TODO Auto-generated destructor stub
}


void SectionModel::setID(int id) { id_ = id; }
int SectionModel::getID() { return id_; }
void SectionModel::setCategory(CategoryModel* category) { category_ = category; }
CategoryModel* SectionModel::getCategory() { return category_; }
void SectionModel::setName(string name) { name_ = name; }
string SectionModel::getName() { return name_; }
void SectionModel::setDecscription(string description) { description_ = description; }
string SectionModel::getDescription() { return description_; }
