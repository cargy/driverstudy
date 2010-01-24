//      test.cpp
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


#include <iostream>
#include "sqliteExerBase.cxx"

int main(int argc, char **argv){
	
	
	clock_t start,finish;
	double time;
	
  start = clock();
  cout << "Connecting to db...";
  SQLITE3 sql("ExerBase.db");
  finish = clock();
  time = (double(finish)-double(start))/CLOCKS_PER_SEC;
  cout << time << endl;
  
  start = clock(); 
  vector<int> *v = sql.testTemplate(1,1);
  /*
  for(int i=0; i < 30;i++) {
			cout << endl << "v[" << i << "]=";
			copy(v[i].begin(),v[i].end(),ostream_iterator<int>(cout,","));
  }	
  */
  finish = clock();
  time = (double(finish)-double(start))/CLOCKS_PER_SEC;
  cout <<endl << "Time:"<< time << endl;
  
  int *array = sql.createRandomTestFromTemplate(v);
  //for (int i=0; i < 30; i++) cout << "array[" << i << "]=" << array[i] << endl;

  cout <<endl<< "Allocatin memory for Question objects...";
  //Question q = sql.getQuestion(15);
  Question *q; // = new Question [30];
  //q[0] = sql.getQuestion(36);
  //q[1] = sql.getQuestion(37);

  
  start = clock();
  cout << "Retrieving question from db..." ;
  //for (int i=0; i< 30; i++) q[i] = sql.getQuestion(i+36);
  q = sql.getQuestionArray(array);
  finish = clock();
  time = (double(finish)-double(start))/CLOCKS_PER_SEC;
  cout << time << endl;
  //q.show();
  

  //for(int i=0;i<30;i++) q[i].showAnswers();
  
  cout << "Creating new Test object...";
  Test *t = new Test(q,30);

  cout << "Answering Questions randomly...";
  t->answerRandomly();
  t->showResults();
  t->getCorrect();
  
  
  
  //t->showResults();

  //for (int i=0; i< 15; i++) q[i].show();
  //pause(); 	
  /*
  sql.exe("SELECT qlect, alect, ACorr from Quest,answer where qcod = aqcod and qcod = 16;");

  if( sql.vcol_head.size() > 0 )
    {
      //cout << "Headings" << endl;
      //copy(sql.vcol_head.begin(),sql.vcol_head.end(),ostream_iterator<string>(cout,"\t"));
      //cout << endl << endl;
      //cout << "Data" << endl;
      //copy(sql.vdata.begin(),sql.vdata.end(),ostream_iterator<string>(cout,"\t"));
      //cout << endl;
      cout << "sql.vdata.size(): " <<  sql.vdata.size() << endl;
      for(int i=0; i < sql.vdata.size(); i++) 
      {
		  cout << "sql.vdata.at(" << i << "): " << sql.vdata.at(i) << endl;
		  cout << (sql.vdata.size() % (i+1)) << endl;
		  
	  }
    }
*/
  return 0;
}
