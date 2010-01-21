//      Question.cpp
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

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <ctime>

using namespace std;
const int MAXQUESTIONSIZE = 500;
const int MAXANSWERSIZE = 500;
const int MAXSNDFILESIZE = 255;
const int MAXIMGFILESIZE = 255;

class Answer
{
	private:
		char answer[MAXANSWERSIZE];
		bool correct;
		bool selected;
		int order;
		char sndFile[MAXSNDFILESIZE];
		
	public:
		
		Answer()
		{
			strncpy(answer, "", MAXANSWERSIZE);
			correct = false;
			selected = false;
			order = -1;
		}
		
		Answer(const char* pText, bool xferCorrect, const char* pSndFile, int xferOrder=-1)
		{
			strncpy(answer, pText, MAXANSWERSIZE);
			answer[MAXANSWERSIZE - 1] = '\0';
			correct = xferCorrect;
			strncpy(sndFile, pSndFile, MAXSNDFILESIZE);
			sndFile[MAXANSWERSIZE - 1] = '\0';			
			selected = false;
			order = xferOrder;
		}
		
		void select()
		{
			selected = true;
		}
		
		void deselect()
		{
			selected = false;
		}
		
		bool isCorrect()
		{
			return correct;
		}
		
		bool isSelected()
		{
			return selected;
		}
		
		const char* getText()
		{
			return answer;
		}

		
};

class Question
{
	private:
		int dbId;
		char question[MAXQUESTIONSIZE];
		unsigned int amountOfAnswers;
		unsigned int selectedAnswer;
		Answer *qAnswers;
		char imgFile[MAXIMGFILESIZE];
		char sndFile[MAXSNDFILESIZE];
		char book[128];
	
	public:
	
		Question()
		{

		}
		
		
		Question(const char* pQuestion, const char* pImgFile, const char* pSndFile,const char* pBook,Answer *xferAnswers, unsigned int aoa)
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
		}
		
		void answerRandomly() {
		    unsigned int s;
		    //cin >> s;
		    
		    s = (rand() % amountOfAnswers ) + 1; 
		    //cout << s << endl;
		    //qAnswers[s-1].select();
		    selectAnswer(s-1);
		    
		}
		
		void showAnswers() {
			cout << question << " (" << book << ")" <<endl;
			cout << "Choose:";
			for (unsigned int i=0; i<amountOfAnswers;i++) {
			  cout << "\n " << i+1 << ") " << qAnswers[i].getText();
			  if ( qAnswers[i].isCorrect() ) cout << " *";
			  if ( qAnswers[i].isSelected() ) cout << " <--";
		  }
		    cout << "\n";
		 
		}
		
		bool isCorrect() {
			return qAnswers[selectedAnswer].isCorrect();
		}
		
		void selectAnswer(unsigned int selected) {
			for (unsigned int i=0; i < amountOfAnswers;i++) qAnswers[i].deselect();
			qAnswers[selected].select();
			selectedAnswer = selected;
		}		
			
		const char *title() 
		{
			return question;
		}
		
		const char *image() 
		{
			return imgFile;
		}
		
		const char *getBookSection()
		{
			return book;
		}
		
		const char *getAnswer(int i)
		{
			return qAnswers[i].getText();
		}
		
		unsigned int getAOA()
		{
			return amountOfAnswers;
		}
		
		unsigned int getSelectedAnswer()
		{
			return selectedAnswer;
		}
	
	
};

class Test {
	private:
		Question *tQuestions;
		int testTime;
		int amountOfQuestions;
		int cursor;
		
	public:
		
		Test(Question *xferQuestions, int aoq)
		{
			tQuestions = xferQuestions;
			amountOfQuestions = aoq;
			cursor = 0;
		}
		
		
		void showResults() {
			int i=0;
			for(i=0;i<amountOfQuestions;i++) {
				cout << "\nQuestion " << i+1 << "\n";
				tQuestions[i].showAnswers();
			}
		}
		
		void answerRandomly() 
		{
		    for(int i=0;i<amountOfQuestions;i++)
				tQuestions[i].answerRandomly();			
		}
		
		int getCorrect() {
			int correctQuestions = 0;
			for(int i=0;i<amountOfQuestions;i++) {
				if ( tQuestions[i].isCorrect() ) correctQuestions++;
			}
			cout << endl << correctQuestions << " out of " << amountOfQuestions << " correct Questions" << endl;
			return correctQuestions;
		}
		
		Question *next()
		{
			if (cursor < amountOfQuestions - 1)	return &tQuestions[cursor++];
			else return &tQuestions[cursor];
		}
		
		int getCursor()
		{
			return cursor;
		}
};
			
/*
int main(int argc, char** argv)
{
	Answer a[3] = { Answer("- Answer 1", 0, -1),
					Answer("- Answer 2", 1, -1),
					Answer("- Answer 3", 0, -1)
				};
				
	Answer b[3] = { Answer("- Answer 1", 0, -1),
					Answer("- Answer 2", 1, -1),
					Answer("- Answer 3", 0, -1)
				};
								
	//Question *q = new Question("What's up?", a, 3);
	Question q[5] = { Question("What's up",a, 3),
					  Question("What's down",b, 3),
					  Question("What's left",a, 3),
					  Question("What's right",a, 3),
					  Question("What's that",a, 3)
				  };
	//q->show();
	Test *t = new Test(q,2);
	t->show();
	cout << "\n============================\n";
	t->showResults();
	
	
					

	return 0;
}	 
*/
