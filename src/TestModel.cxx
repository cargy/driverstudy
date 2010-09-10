#include "TestModel.h"
#include <iostream>

TestModel::TestModel(QuestionModel *xferQuestions, int aoq, CategoryModel* tcategory):
Model()
{
	tQuestions = xferQuestions;
	csize = aoq;
	ccursor = -1;
	testCategory = tcategory;
	testTime = tcategory->getTime();
	run_ = false;
	std::cout << "TestModel constructed:" << this << std::endl;
}

TestModel::~TestModel() {
	std::cout << "TestModel dropped:" << this << std::endl;
}

void TestModel::loadTest(TestModel* pTestModel) {
	tQuestions = pTestModel->tQuestions;
	csize = pTestModel->csize;
	ccursor = -1;
	testTime = pTestModel->testTime;
	testCategory = pTestModel->testCategory;
}

void TestModel::showResults() {
	changed();
}

void TestModel::selectAnswerOfCurrentQuestion(int a)
{
	tQuestions[ccursor].selectAnswer(a);
	changed();
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

QuestionModel* TestModel::wrongQuestions() 
{
	QuestionModel *wq = new QuestionModel[csize-getCorrect()];
	int index = -1;
	for(int i=0;i<csize;i++) {
		if ( !tQuestions[i].isCorrect() ) {
			wq[++index] = tQuestions[i];
		}
	}
	return wq;			
}

QuestionModel* TestModel::next()
{			
	if (ccursor >= csize-1) ccursor = -1;
	
	while ( tQuestions[++ccursor].isVerified() && !completed() ) 
	{
		if (ccursor >= csize-1) ccursor = -1;
	}
	//changed();
	return &tQuestions[ccursor];
	
}

bool TestModel::isRunning() { return run_; }

void TestModel::startTest() {
	currentQuestion = next();
	run_ = true;
	changed();
}

void TestModel::nextQuestion() {
	currentQuestion = next();
	changed();
}

QuestionModel* TestModel::question()
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

QuestionModel* TestModel::nextWrong()
{			
	if (ccursor >= csize-1) ccursor = -1;
	
	while ( tQuestions[++ccursor].isCorrect() && ( getWrong() != 0 ) ) 
	{
		if (ccursor >= csize-1) ccursor = -1;
	}
	changed();
	return &tQuestions[ccursor];
	
}

CategoryModel* TestModel::getCategory() { return testCategory; }
int TestModel::time() { return testTime;};
int TestModel::category_id() {return testCategory->getCID();};

#ifdef DEBUG
#include <cstdio>
void TestModel::answerRandomly() 
{
	for(int i=0;i<csize;i++)
		tQuestions[i].answerRandomly();			
}

void TestModel::showResultsDbg() {
	int i=0;
	for(i=0;i<csize;i++) {
		printf("\nQuestion %i\n",i+1);
		tQuestions[i].showAnswers();
	}
}
#endif
