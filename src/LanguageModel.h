/*
 * LanguageModel.h
 *
 *  Created on: Sep 27, 2010
 *      Author: krizz
 */

#ifndef LANGUAGEMODEL_H_
#define LANGUAGEMODEL_H_

#include "MV.h"
#include <string>

class LanguageModel: public Model {
private:
	int lid_;
	std::string label_;
public:
	LanguageModel(int lid, std::string label);
	virtual ~LanguageModel();
	int getLID();
	void setLID(int lid);
	std::string getLabel();
	void setLabel(std::string label);

};

#endif /* LANGUAGEMODEL_H_ */
