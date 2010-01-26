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


#include "question.h"



Question::Question()
{
	amountOfAnswers = 0;
	selectedAnswer = -1;
}

Question::Question(const char* pQuestion, const char* pImgFile, const char* pSndFile,const char* pBook,Answer *xferAnswers, unsigned int aoa)
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
}

bool Question::isCorrect() {
	return qAnswers[selectedAnswer].isCorrect();
}

void Question::selectAnswer(int selected) {
	for (unsigned int i=0; i < amountOfAnswers;i++) qAnswers[i].deselect();
	if (selected != -1 ) qAnswers[selected].select();
	selectedAnswer = selected;
}		
	
const char* Question::title() {	return question;}

const char* Question::image() {	return imgFile; }

const char* Question::getBookSection(){	return book;}

const char* Question::getAnswer(unsigned int i)
{
	#ifdef DEBUG
	assert(i<amountOfAnswers);
	#endif
	return qAnswers[i].text();
}

unsigned int Question::getAOA(){return amountOfAnswers;}

int Question::getSelectedAnswer(){return selectedAnswer;}

unsigned int Question::getCorrectAnswer()
{
	for (unsigned int i=0; i<amountOfAnswers;i++) 
	{
		if ( qAnswers[i].isCorrect() ) return i;
	}
			
	return -1;
}

bool Question::isVerified(){return verified;}

void Question::verify()
{
	// flag question verified ONLY if a selection is made
	if (selectedAnswer != -1) verified = true;
}

#ifdef DEBUG
void Question::answerRandomly() {
	unsigned int s;
	//cin >> s;
	
	s = (rand() % amountOfAnswers ) + 1; 
	//cout << s << endl;
	//qAnswers[s-1].select();
	selectAnswer(s-1);
	
}

void Question::showAnswers() {
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
