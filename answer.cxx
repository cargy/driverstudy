//      answer.cxx
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


#include "answer.h"


Answer::Answer()
{
	strncpy(answer, "", MAXANSWERSIZE);
	correct = false;
	selected = false;
	porder = -1;
}

Answer::Answer(const char* pText, bool xferCorrect, const char* pSndFile, int xferOrder)
{
	strncpy(answer, pText, MAXANSWERSIZE);
	answer[MAXANSWERSIZE - 1] = '\0';
	correct = xferCorrect;
	strncpy(sndFile, pSndFile, MAXSNDFILESIZE);
	sndFile[MAXANSWERSIZE - 1] = '\0';			
	selected = false;
	porder = xferOrder;
}

void Answer::select(){selected = true;}
void Answer::deselect(){selected = false;}
bool Answer::isCorrect(){return correct;}
bool Answer::isSelected(){return selected;}
const char* Answer::text(){return answer;}
const char* Answer::soundFile(){return sndFile;}
int Answer::order(){return porder;}
