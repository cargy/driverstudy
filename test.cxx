//      test.cxx
//      
//      Copyright 2010 Argyriadis Christos <krizz@Freak>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include "test.h"


Test::Test(Question *xferQuestions, int aoq)
{
	tQuestions = xferQuestions;
	amountOfQuestions = aoq;
	cursor = -1;
}

Test::~Test()
{
	
}

void Test::selectAnswerOfCurrentQuestion(int a)
{
	tQuestions[cursor].selectAnswer(a);
}

void Test::verifyAnswerOfCurrentQuestion()
{
	tQuestions[cursor].verify();
}

bool Test::completed()
{
	bool flag = true;
	
	for(int i=0;i<amountOfQuestions;i++) 
		if (!tQuestions[i].isVerified())
			return false;
	
	return flag;
}

int Test::getCorrect() {
	int correctQuestions = 0;
	for(int i=0;i<amountOfQuestions;i++) {
		if ( tQuestions[i].isCorrect() ) correctQuestions++;
	}
	//cout << endl << correctQuestions << " out of " << amountOfQuestions << " correct Questions" << endl;
	return correctQuestions;
}

Question* Test::wrongQuestions() 
{
	Question *wq = new Question[amountOfQuestions-getCorrect()];
	int index = -1;
	for(int i=0;i<amountOfQuestions;i++) {
		if ( !tQuestions[i].isCorrect() ) {
			wq[++index] = tQuestions[i];
		}
	}
	return wq;			
}

int Test::getAOQ()
{
	return amountOfQuestions;
}

Question* Test::next()
{			
	if (cursor >= amountOfQuestions-1) cursor = -1;
	
	while ( tQuestions[++cursor].isVerified() && !completed() ) 
	{
		if (cursor >= amountOfQuestions-1) cursor = -1;
	}
	return &tQuestions[cursor];
	
}

int Test::getCursor()
{
	return cursor;
}

#ifdef DEBUG
void Test::answerRandomly() 
{
	for(int i=0;i<amountOfQuestions;i++)
		tQuestions[i].answerRandomly();			
}

void Test::showResults() {
	int i=0;
	for(i=0;i<amountOfQuestions;i++) {
		cout << "\nQuestion " << i+1 << "\n";
		tQuestions[i].showAnswers();
	}
}
#endif
