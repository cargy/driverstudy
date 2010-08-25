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


#ifndef TESTMODEL_H
#define TESTMODEL_H
#include "QuestionModel.h"
#include "MV.h"

#define TESTMODEL_ID 2

class TestModel: public Model
{
	public:
		TestModel(QuestionModel *xferQuestions, int aoq, int ttime, int tcategory);
		~TestModel();
		void loadTest(TestModel* pTestModel);
		void selectAnswerOfCurrentQuestion(int a);
		void verifyAnswerOfCurrentQuestion();
		bool completed();
		int getCorrect();
		int getWrong();
		QuestionModel *wrongQuestions();
		QuestionModel *next();
		QuestionModel* question();
		QuestionModel *nextWrong();
		void nextQuestion();
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
		QuestionModel *tQuestions;
		int csize;
		int ccursor;
		int testTime;
		int testCategory;
	
	private:
		QuestionModel* currentQuestion;

};

#endif /* TESTMODEL_H */
