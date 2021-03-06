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
#include "CategoryModel.h"
#include "MV.h"

#define TESTMODEL_ID 2

class TestModel: public Model
{
public:
		TestModel(QuestionModel *xferQuestions, int aoq, CategoryModel* tcategory);
		virtual ~TestModel();
		void loadTest(TestModel* pTestModel);
		void selectAnswerOfCurrentQuestion(int a);
		void verifyAnswerOfCurrentQuestion();
		bool completed();
		int getCorrect();
		int getWrong();
		QuestionModel* question();
		void nextQuestion();
		void nextWrongQuestion();
		void firstWrongQuestion();
		void startTest();
		bool isRunning();
		bool is_next();
		bool is_nextWrong();
		int size(){	return csize;}	
		int cursor(){return ccursor;}
		int time();
		int category_id();
		void showResults();
		CategoryModel* getCategory();
		#ifdef DEBUG
		void answerRandomly();
		void showResultsDbg();
		#endif
		
	protected:
		QuestionModel *tQuestions;
		int csize;
		int ccursor;
		int testTime;
		CategoryModel* testCategory;
		bool run_;
	
	private:
		QuestionModel* currentQuestion;
		QuestionModel *wrongQuestions();
		QuestionModel *next();
		QuestionModel *nextWrong();
		QuestionModel *firstWrong();

};

#endif /* TESTMODEL_H */
