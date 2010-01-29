#include <iostream>
#include "question.h"

class QuestionCollection
{
	private:
		Question *tQuestions;
		int csize;
		int ccursor;
		
	public:
		QuestionCollection(Question *questionArray, int aoq);	
		Question *next();
		int size(){	return csize;}	
		int cursor(){return ccursor;}
	
};



QuestionCollection::QuestionCollection(Question *questionArray, int aoq)
{
	tQuestions = questionArray;
	csize = aoq;
	ccursor = -1;
}
Question* QuestionCollection::next()
{			
	if (ccursor >= csize-1) ccursor = -1;

	return &tQuestions[++ccursor];
}
