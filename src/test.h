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
#include "question.h"
#include "MV.h"

class Test: public Model
{
	public:
		Test(Question *xferQuestions, int aoq, int ttime, int tcategory);
		void selectAnswerOfCurrentQuestion(int a);
		void verifyAnswerOfCurrentQuestion();
		bool completed();
		int getCorrect();
		int getWrong();
		Question *wrongQuestions();
		Question *next();
		Question* question();
		Question *nextWrong();
		bool is_next();
		bool is_nextWrong();
		int size(){	return csize;}	
		int cursor(){return ccursor;}
		int time();
		int category_id();
		#ifdef DEBUG
		void answerRandomly();
		void showResults();
		#endif
		
	protected:
		Question *tQuestions;
		int csize;
		int ccursor;
	
	private:
		int testTime;
		int testCategory;

};

#endif /* TEST_H */ 
