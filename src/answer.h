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
#include <string>

class Answer
{
	public:
		Answer();
		Answer(std::string pText, bool xferCorrect, std::string pSndFile, int xferOrder=-1);
		void select();
		void deselect();
		bool isCorrect();
		bool isSelected();
		std::string text();
		std::string soundFile();
		int order();
			
	private:
		std::string answer;
		bool correct;
		bool selected;
		int porder;
		std::string sndFile;

};

#endif /* ANSWER_H */ 
