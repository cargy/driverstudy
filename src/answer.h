//      answer.h
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


#ifndef ANSWER_H
#define ANSWER_H
#include "config.h"
#include <cstring>

class Answer
{
	public:
		Answer();
		Answer(const char* pText, bool xferCorrect, const char* pSndFile, int xferOrder=-1);
		void select();
		void deselect();
		bool isCorrect();
		bool isSelected();
		const char* text();
		const char* soundFile();
		int order();
			
	private:
		char answer[MAXANSWERSIZE];
		bool correct;
		bool selected;
		int porder;
		char sndFile[MAXSNDFILESIZE];

};

#endif /* ANSWER_H */ 
