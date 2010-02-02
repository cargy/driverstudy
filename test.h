//      test.h
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


#ifndef TEST_H
#define TEST_H

#include "questionCollection.h"

class Test:public QuestionCollection
{
	public:
		Test(Question *xferQuestions, int aoq, int ttime);
		void selectAnswerOfCurrentQuestion(int a);
		void verifyAnswerOfCurrentQuestion();
		bool completed();
		int getCorrect();
		Question *wrongQuestions();
		QuestionCollection* wrongQuestionsCollection();
		Question *next();
		Question *nextWrong();
		int time();
		#ifdef DEBUG
		void answerRandomly();
		void showResults();
		#endif
	
	private:
		int testTime;

};

#endif /* TEST_H */ 
