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

#include "log.h"
#ifdef DEBUG
#include <cstdlib>
#include <iostream>
#include <cassert>

#endif /* DEBUG */
#include <iostream>
#include <string>
using namespace std;

QuestionModel::QuestionModel():
Model()
{
	amountOfAnswers = 0;
	selectedAnswer = -1;
	FILE_LOG(logDEBUG4) << __LINE__ << ":QuestionModel1 constructed:" << this;
}

QuestionModel::QuestionModel(string pQuestion, string pImgFile, string pSndFile,string pBook,Answer *xferAnswers, unsigned int aoa):
Model()
{
	question = pQuestion;
	imgFile = pImgFile;
	sndFile = pSndFile;			
	book = pBook;
			
	qAnswers = xferAnswers;
	selectedAnswer = -1;
	amountOfAnswers = aoa;
	verified = false;
	FILE_LOG(logDEBUG4) << "QuestionModel constructed:" << this;
}

bool QuestionModel::isCorrect() {
	return qAnswers[selectedAnswer].isCorrect();
}

void QuestionModel::selectAnswer(int selected) {
	for (unsigned int i=0; i < amountOfAnswers;i++) qAnswers[i].deselect();
	if (selected != -1 ) qAnswers[selected].select();
	selectedAnswer = selected;
}		
	
string QuestionModel::title() {	return question;}

string QuestionModel::image() {	return imgFile; }

string QuestionModel::sound() {	return sndFile; }

string QuestionModel::getBookSection(){	return book;}

string QuestionModel::getAnswer(unsigned int i)
{
	#ifdef DEBUG
	assert(i<amountOfAnswers);
	#endif
	return qAnswers[i].text();
}

string QuestionModel::answerSound(unsigned int i)
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
