/*
 * CategoryModel.h
 *
 *  Created on: Sep 2, 2010
 *      Author: krizz
 */

#ifndef CATEGORYMODEL_H_
#define CATEGORYMODEL_H_

#include "MV.h"
#include <string>

// DATABASE MAPPINGS
#define CAR_CATEGORYMODEL_ID 1
#define MOTORCYCLE_CATEGORYMODEL_ID 2
#define TRUCK_CATEGORYMODEL_ID 3
#define BUS_CATEGORYMODEL_ID 4
#define DBSCARID 11
#define DBSMOTORCYCLEID 12

class CategoryModel: public Model {
private:
	int cid_;
	std::string label_;
	std::string image_;
	int time_;
	int questionnaireNo_;
	int amountOfTestQuestions_;

public:
	CategoryModel(int cid, std::string label, int questionnaireNo, int amountOfTestQuestions, int time, std::string image);
	virtual ~CategoryModel();
	int getCID();
	int getTime();
	int getQuestionnaireNo();
	void setQuestionnaireNo(int questionnaireNo);
	int getAmountOfTestQuestions();
	std::string getLabel();
	void setImage(std::string image);
	std::string getImage();
};

#endif /* CATEGORYMODEL_H_ */
