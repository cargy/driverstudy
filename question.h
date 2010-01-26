//      question.h
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


#ifndef QUESTION_H
#define QUESTION_H
#define MAXQUESTIONSIZE 500
#define MAXIMGFILESIZE 255

#include "answer.h"

using namespace std;

#define DEBUG

#ifdef DEBUG
#include <cstdlib>
#include <iostream>
#include <cassert>
#endif /* DEBUG */ 


class Question
{
	public:
		Question();
		Question(const char* pQuestion, const char* pImgFile, const char* pSndFile,const char* pBook,Answer *xferAnswers, unsigned int aoa);
		bool isCorrect();
		void selectAnswer(int selected);
		const char *title();
		const char *image();
		const char *getBookSection();
		const char *getAnswer(unsigned int i);
		unsigned int getAOA();
		int getSelectedAnswer();
		unsigned int getCorrectAnswer();
		bool isVerified();
		void verify();
		#ifdef DEBUG
		void answerRandomly();
		void showAnswers();
		#endif
			
	private:
		int dbId;
		char question[MAXQUESTIONSIZE];
		unsigned int amountOfAnswers;
		int selectedAnswer;
		Answer *qAnswers;
		char imgFile[MAXIMGFILESIZE];
		char sndFile[MAXSNDFILESIZE];
		char book[128];
		bool verified;

};

#endif /* QUESTION_H */ 
