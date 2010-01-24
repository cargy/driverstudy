#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "Question.cpp"

class DBError {
	const char* errormsg;
	const char* sql;
	
	public:
	DBError(const char* msg)
	{
		cout << "DB error:" << msg << endl;
	}
	
	DBError(const char* msg, const char* lsql)
	{
		cout << "DB error:" << msg << endl <<"Last SQL Query:"<<endl<<"`" << lsql<<"`"<<endl;
	}
};
	
	

class SQLITE3 {
private:
  sqlite3 *db;
  char *zErrMsg;
  char **result;
  int rc;
  int nrow,ncol;
  int db_open;

public:

  vector<string> vcol_head;
  vector<string> vdata;


  SQLITE3 (string tablename="init.db"): zErrMsg(0), rc(0),db_open(0) {

    rc = sqlite3_open_v2(tablename.c_str(),&db,SQLITE_OPEN_READONLY,NULL);
    if( rc ){
      //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      throw DBError(sqlite3_errmsg(db));
      sqlite3_close(db);
    }
    
    db_open=1;
  }
  
  int random_range(int lowest=1, int highest=10 )
  {
	  srand(time(NULL));
	  int random_integer;
	 // int range=(highest-lowest)+1;
	  
	 // for(int index=0; index<20; index++){
		  //random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));
		  random_integer = (rand()%highest)+lowest;
		  //cout << "low=" << lowest << " high=" <<highest<< " : " << random_integer << endl;
		  return random_integer;
		//}
	}
  
  int *createRandomTestFromTemplate ( vector<int> *v) {
	  int *array = new int[30];
	   for (int i=0;i<30;i++) {
		   array[i] = v[i].at(random_range(0,v[i].size()));
	   }
	   return array;
	  
  }
  
  vector<int> *testTemplate ( int category, int language ) {
	  char buffer[1024];
	  sprintf(buffer,"Select Qpag,qcod FROM Quest, Numbs WHERE KCod = %d and PCod = Qpag and KCod = QKateg and qlang = %d order by qpag;",category,language);
	  string s_exe(buffer);

	  rc = sqlite3_get_table(db,s_exe.c_str(),&result,&nrow,&ncol,&zErrMsg);


	  if( rc == SQLITE_OK )
	  {
		  vector<int> *v = new vector<int>[31];
		  assert(nrow != 0);
		  for(int i=1; i <= nrow;i++)
			 v[atoi(result[ncol*i])-1].push_back(atoi(result[ncol*i+1]));
		 
		 sqlite3_free_table(result);
		 return v;
		 
		 for(int i=0; i < 30;i++) {
			 cout << endl << "v[" << i << "]=";
			 copy(v[i].begin(),v[i].end(),ostream_iterator<int>(cout,","));
		 }		 
	  } else { throw DBError(sqlite3_errmsg(db),s_exe.c_str()); }
	  
	  
	  return NULL;
  }
  
  Question *getQuestionArray(int *array) {
	  Question *q = new Question[30];
	  
	  for (int i=0; i<30; i++)
		q[i] = getQuestion(array[i]);
		
	  return q;
  }

  Question getQuestion(int qid) {
	  char buffer[1024];
	  sprintf(buffer,"SELECT qlect, QPhoto, QSound, QBook, alect, ACorr, ASound, AAA from Quest,answer where qcod = aqcod and qcod = %d ;",qid);
	  string s_exe(buffer);
	  
      rc = sqlite3_get_table(
			db,              /* An open database */
			s_exe.c_str(),       /* SQL to be executed */
			&result,       /* Result written to a char *[]  that this points to */
			&nrow,             /* Number of result rows written here */
			&ncol,          /* Number of result columns written here */
			&zErrMsg          /* Error msg written here */
			);

     if( rc == SQLITE_OK ){
		 int i=0;
		 Answer *a = new Answer[nrow];
		 
		 // question string
		 //cout << result[ncol] << endl;
		 for(i=1; i <= nrow;i++) {
			 string corr_str = result[ncol*i+5];
			 bool correct = true;
			 if ( corr_str.find ('1') == string::npos ) correct = false;
			 a[i-1] = Answer(result[ncol*i+4], correct, result[ncol*i+6],atoi(result[ncol*i+7]));

		 }
		 Question q =  Question(result[ncol],result[ncol+1],result[ncol+2],result[ncol+3],a,nrow);
		 sqlite3_free_table(result);
		 return q;	 
     }else {throw DBError(sqlite3_errmsg(db),s_exe.c_str());}
     
     sqlite3_free_table(result);
     return Question();
  }


  ~SQLITE3(){
      sqlite3_close(db);
  } 
};
