/*
 * SectionModel.h
 *
 *  Created on: Oct 11, 2010
 *      Author: krizz
 */

#ifndef SECTIONMODEL_H_
#define SECTIONMODEL_H_

#include "MV.h"
#include "CategoryModel.h"
#include <string>

class SectionModel: public Model {
private:
	int id_;
	CategoryModel* category_;
	std::string name_;
	std::string description_;

public:
	SectionModel(int id, CategoryModel* category, std::string name, std::string description);
	virtual ~SectionModel();
	void setID(int i);
	int getID();
	void setCategory(CategoryModel* category);
	CategoryModel* getCategory();
	void setName(std::string name);
	std::string getName();
	void setDecscription(std::string description);
	std::string getDescription();
};

#endif /* SECTIONMODEL_H_ */
