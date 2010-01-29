#include "test.h"


Test::Test(Question *xferQuestions, int aoq, int ttime)
	 :QuestionCollection(xferQuestions,aoq)
{
	testTime = ttime;	
}

void Test::selectAnswerOfCurrentQuestion(int a)
{
	tQuestions[ccursor].selectAnswer(a);
}

void Test::verifyAnswerOfCurrentQuestion()
{
	tQuestions[ccursor].verify();
}

bool Test::completed()
{
	bool flag = true;
	
	for(int i=0;i<csize;i++) 
		if (!tQuestions[i].isVerified())
			return false;
	
	return flag;
}

int Test::getCorrect() {
	int correctQuestions = 0;
	for(int i=0;i<csize;i++) {
		if ( tQuestions[i].isCorrect() ) correctQuestions++;
	}
	//cout << endl << correctQuestions << " out of " << amountOfQuestions << " correct Questions" << endl;
	return correctQuestions;
}

Question* Test::wrongQuestions() 
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

Question* Test::next()
{			
	if (ccursor >= csize-1) ccursor = -1;
	
	while ( tQuestions[++ccursor].isVerified() && !completed() ) 
	{
		if (ccursor >= csize-1) ccursor = -1;
	}
	return &tQuestions[ccursor];
	
}

int Test::time() { return testTime;};

#ifdef DEBUG
void Test::answerRandomly() 
{
	for(int i=0;i<csize;i++)
		tQuestions[i].answerRandomly();			
}

void Test::showResults() {
	int i=0;
	for(i=0;i<csize;i++) {
		cout << "\nQuestion " << i+1 << "\n";
		tQuestions[i].showAnswers();
	}
}
#endif
