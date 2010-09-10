//      question.cxx
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


#include "QuestionModel.h"


#ifdef DEBUG
#include <cstdlib>
#include <iostream>
#include <cassert>

#endif /* DEBUG */
#include <iostream>

QuestionModel::QuestionModel():
Model()
{
	amountOfAnswers = 0;
	selectedAnswer = -1;
	std::cout << __LINE__ << ":QuestionModel1 constructed:" << this << std::endl;
}

QuestionModel::QuestionModel(const char* pQuestion, const char* pImgFile, const char* pSndFile,const char* pBook,Answer *xferAnswers, unsigned int aoa):
Model()
{
	strncpy(question, pQuestion, MAXQUESTIONSIZE);
	question[MAXQUESTIONSIZE - 1] = '\0';

	strncpy(imgFile, pImgFile, MAXIMGFILESIZE);
	imgFile[MAXIMGFILESIZE - 1] = '\0';
	
	strncpy(sndFile, pSndFile, MAXSNDFILESIZE);
	sndFile[MAXSNDFILESIZE - 1] = '\0';	
			
	strncpy(book, pBook, 128);
	book[128 - 1] = '\0';	
			
	qAnswers = xferAnswers;
	selectedAnswer = -1;
	amountOfAnswers = aoa;
	verified = false;
	std::cout << "QuestionModel constructed:" << this << std::endl;
}

bool QuestionModel::isCorrect() {
	return qAnswers[selectedAnswer].isCorrect();
}

void QuestionModel::selectAnswer(int selected) {
	for (unsigned int i=0; i < amountOfAnswers;i++) qAnswers[i].deselect();
	if (selected != -1 ) qAnswers[selected].select();
	selectedAnswer = selected;
}		
	
const char* QuestionModel::title() {	return question;}

const char* QuestionModel::image() {	return imgFile; }

const char* QuestionModel::sound() {	return sndFile; }

const char* QuestionModel::getBookSection(){	return book;}

const char* QuestionModel::getAnswer(unsigned int i)
{
	#ifdef DEBUG
	assert(i<amountOfAnswers);
	#endif
	return qAnswers[i].text();
}

const char* QuestionModel::answerSound(unsigned int i)
{
	#ifdef DEBUG
	assert(i<amountOfAnswers);
	#endif
	return qAnswers[i].soundFile();
}

unsigned int QuestionModel::getAOA(){return amountOfAnswers;}

int QuestionModel::getSelectedAnswer(){return selectedAnswer;}

int QuestionModel::getCorrectAnswer()
{
	for (unsigned int i=0; i<amountOfAnswers;i++) 
	{
		if ( qAnswers[i].isCorrect() ) return i;
	}
			
	return -1;
}

bool QuestionModel::isVerified(){return verified;}

void QuestionModel::verify()
{
	// flag question verified ONLY if a selection is made
	if (selectedAnswer != -1) verified = true;
}

#ifdef DEBUG
using namespace std;
void QuestionModel::answerRandomly() {
	unsigned int s;
	//cin >> s;
	
	s = (rand() % amountOfAnswers ) + 1; 
	//cout << s << endl;
	//qAnswers[s-1].select();
	selectAnswer(s-1);
	
}

void QuestionModel::showAnswers() {
	cout << question << " (" << book << ")" <<endl;
	cout << "Choose:";
	for (unsigned int i=0; i<amountOfAnswers;i++) {
	  cout << "\n " << i+1 << ") " << qAnswers[i].text();
	  if ( qAnswers[i].isCorrect() ) cout << " *";
	  if ( qAnswers[i].isSelected() ) cout << " <--";
  }
	cout << "\n";
}
#endif /* DEBUG */ 
