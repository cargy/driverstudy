#ifndef QUESTIONCOLLECTION_H
#define QUESTIONCOLLECTION_H

#include <iostream>
#include "question.h"

class QuestionCollection
{
	protected:
		QuestionModel *tQuestions;
		int csize;
		int ccursor;
		
	public:
		QuestionCollection(QuestionModel *questionArray, int aoq);	
		QuestionModel *next();
		int size(){	return csize;}	
		int cursor(){return ccursor;}
	
};

#endif /* QUESTIONCOLLECTION_H */ 
