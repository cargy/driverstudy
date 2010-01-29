#ifndef QUESTIONCOLLECTION_H
#define QUESTIONCOLLECTION_H

#include <iostream>
#include "question.h"

class QuestionCollection
{
	protected:
		Question *tQuestions;
		int csize;
		int ccursor;
		
	public:
		QuestionCollection(Question *questionArray, int aoq);	
		Question *next();
		int size(){	return csize;}	
		int cursor(){return ccursor;}
	
};

#endif /* QUESTIONCOLLECTION_H */ 
