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
	std::string code_;
	std::string shortcode_;
	std::string label_;
public:
	LanguageModel(int lid, std::string code, std::string shortcode, std::string label);
	virtual ~LanguageModel();
	int getLID();
	void setLID(int lid);
	std::string getLabel();
	void setLabel(std::string label);
	std::string getCode();
	void setCode(std::string code);
	std::string getShortCode();
	void setShortCode(std::string shortcode);

};

#endif /* LANGUAGEMODEL_H_ */
