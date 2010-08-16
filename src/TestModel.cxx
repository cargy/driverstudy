#include "TestModel.h"

TestModel::TestModel(Question *xferQuestions, int aoq, int ttime, int tcategory):
Model()
{
	tQuestions = xferQuestions;
	csize = aoq;
	ccursor = -1;
	testTime = ttime;
	testCategory = tcategory;
}

void TestModel::selectAnswerOfCurrentQuestion(int a)
{
	tQuestions[ccursor].selectAnswer(a);
}

void TestModel::verifyAnswerOfCurrentQuestion()
{
	tQuestions[ccursor].verify();
}

bool TestModel::completed()
{
	bool flag = true;
	
	for(int i=0;i<csize;i++) 
		if (!tQuestions[i].isVerified())
			return false;
	
	return flag;
}

int TestModel::getCorrect() {
	int correctQuestions = 0;
	for(int i=0;i<csize;i++) {
		if ( tQuestions[i].isVerified() && tQuestions[i].isCorrect() ) correctQuestions++;
	}
	return correctQuestions;
}

int TestModel::getWrong() {
	int wrongQuestion = 0;
	for(int i=0;i<csize;i++) {
		if ( tQuestions[i].isVerified() && !tQuestions[i].isCorrect() ) wrongQuestion++;
	}
	return wrongQuestion;
}

Question* TestModel::wrongQuestions() 
{
	Question *wq = new Question[csize-getCorrect()];
	int index = -1;
	for(int i=0;i<csize;i++) {
		if ( !tQuestions[i].isCorrect() ) {
			wq[++index] = tQuestions[i];
		}
	}
	return wq;			
}

Question* TestModel::next()
{			
	if (ccursor >= csize-1) ccursor = -1;
	
	while ( tQuestions[++ccursor].isVerified() && !completed() ) 
	{
		if (ccursor >= csize-1) ccursor = -1;
	}
	//changed();
	return &tQuestions[ccursor];
	
}

Question* TestModel::question()
{
	return &tQuestions[ccursor];
}

bool TestModel::is_next()
{
	unsigned int flag = 0;
	
	for(int i=0;i<csize;i++) 
		if (!tQuestions[i].isVerified()) flag++;
	
	if (flag > 1) return true;
	else return false;
}

bool TestModel::is_nextWrong()
{
	for (int i=ccursor+1; i < csize; i++ )
		if ( !tQuestions[i].isCorrect() ) return true;
		
	return false;
}

Question* TestModel::nextWrong()
{			
	if (ccursor >= csize-1) ccursor = -1;
	
	while ( tQuestions[++ccursor].isCorrect() && ( getWrong() != 0 ) ) 
	{
		if (ccursor >= csize-1) ccursor = -1;
	}
	changed();
	return &tQuestions[ccursor];
	
}

int TestModel::time() { return testTime;};
int TestModel::category_id() {return testCategory;};

#ifdef DEBUG
#include <cstdio>
void TestModel::answerRandomly() 
{
	for(int i=0;i<csize;i++)
		tQuestions[i].answerRandomly();			
}

void TestModel::showResults() {
	int i=0;
	for(i=0;i<csize;i++) {
		printf("\nQuestion %i\n",i+1);
		tQuestions[i].showAnswers();
	}
}
#endif
