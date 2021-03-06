//      sqlite3.cxx
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

#include "log.h"
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <sstream>
#include <sqlite3.h>
#include <exception>
#include "TestModel.h"
#include <vector>
#include <iterator>
#include <stdio.h>
#include "QuestionModel.h"
#include "CategoryModel.h"
#include "SectionModel.h"
#include "LanguageModel.h"
#include <time.h>

using namespace std;

class DBError: public exception {
	string errormsg;
	string sql;
	
	public:
	string getMsg() { return errormsg; }
	string getSQL() { return sql; }

	virtual const char* what() const throw()
	{
		string msg;
		if ( sql == "")
			msg = "DB error:" + errormsg;
		else
			msg = "DB error:" + errormsg + "Last SQL Query:"+"`" + sql+"`";
		return msg.c_str();
	}

	DBError() throw()
		{

		}

	DBError(string msg)
	{
		errormsg = msg;
		sql = "";
		//cout << "DB error:" << msg << endl;
	}
	
	DBError(string msg, string lsql)
	{
		errormsg = msg;
		sql = lsql;
		//cout << "DB error:" << msg << endl <<"Last SQL Query:"<<endl<<"`" << lsql<<"`"<<endl;
	}
	
	~DBError() throw() {
		// dso
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
  int default_locale_id_;
//  int qNo, tTime, tCategory;

public:


  SQLITE3 (string tablename="init.db"): zErrMsg(0), rc(0),db_open(0) {

    rc = sqlite3_open_v2(tablename.c_str(),&db,SQLITE_OPEN_READONLY,NULL);
    if( rc ){
      //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      throw DBError(string(sqlite3_errmsg(db))+": "+tablename);
      sqlite3_close(db);
    }
    
    db_open=1;
    default_locale_id_ = 1;
  }
  
  void setDefaultLocale(int localeid) { default_locale_id_ = localeid; }

  int random_range(int lowest=1, int highest=10 )
  {
	  int random_integer = (rand()%highest)+lowest;
	  FILE_LOG(logDEBUG3) << "low=" << lowest << " high=" <<highest<< " : " << random_integer;
	  return random_integer;
	}
  
int *createRandomTestFromTemplate ( int cid, vector<int> *v) {
	int qNo = getCategory(cid)->getAmountOfTestQuestions();
	int *array = new int[qNo];
	srand((unsigned int)time(NULL));
	for (int i=0;i<qNo;i++) {
		array[i] = v[i].at(random_range(0,v[i].size()));
	}
	return array;
	  
  }
  
int getTestTemplateNOQ (int category, int language) {
	char buffer[1024];
	int qNo = -1;
	sprintf(buffer,"Select COUNT(DISTINCT(Qpag)) FROM Quest, Numbs WHERE KCod = %d and PCod = Qpag and KCod = QKateg and qlang = %d order by qpag;",category,language);
	string s_exe(buffer);
	FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;

	rc = sqlite3_get_table(db,s_exe.c_str(),&result,&nrow,&ncol,&zErrMsg);
	qNo = atoi(result[1]);
	sqlite3_free_table(result);
	if( rc == SQLITE_OK )
		return qNo;
	else
		throw -1;
}

int getTestTime (int category) {
	char buffer[1024];
	int tTime = 0;
	sprintf(buffer,"Select KTime FROM Kateg WHERE KCod = %d ;",category);
	string s_exe(buffer);
	FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;

	rc = sqlite3_get_table(db,s_exe.c_str(),&result,&nrow,&ncol,&zErrMsg);
	tTime = atoi(result[1]);
	sqlite3_free_table(result);
	if( rc == SQLITE_OK )
		return tTime;
	else
		throw -1;
}

vector<CategoryModel*> getAllCategories() {
	char buffer[1024];
	sprintf(buffer,
	"SELECT C.id, CL.name, C.questionnaireNo, C.testQuestionsAmount, C.time, C.image  "
	"FROM Category C "
	"	INNER JOIN CategoryLocale CL ON CL.categoryID = C.id AND CL.localeID = %d;", default_locale_id_);

	vector<CategoryModel*> categories;
	string s_exe(buffer);
	FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;

	rc = sqlite3_get_table(db,s_exe.c_str(),&result,&nrow,&ncol,&zErrMsg);

	if ( rc == SQLITE_OK )
	{
		for (int i=1; i <= nrow; i++)
		{
			// int cid, string label, int questionnaireNo, int amountOfTestQuestions, int time, string image
			categories.push_back(new CategoryModel(atoi(result[ncol*i+0]),string(result[ncol*i+1]), atoi(result[ncol*i+2]),atoi(result[ncol*i+3]), atoi(result[ncol*i+4]), string(result[ncol*i+5])));
			FILE_LOG(logDEBUG3) << "sqlite3::getAllCategories():" << __LINE__ << ": result[]:" << result[ncol*i+0] << "|" <<  result[ncol*i+1] << "|" << result[ncol*i+2] << "|" << result[ncol*i+2] << endl;
		}
		sqlite3_free_table(result);
	}else{
		throw DBError(string(sqlite3_errmsg(db)),s_exe);
		sqlite3_free_table(result);
	}
	return categories;

}

CategoryModel* getCategory(int cid) {
	vector<CategoryModel*> categories = getAllCategories();

	for (unsigned int i=0;i<categories.size();i++)
		if ( categories[i]->getCID() == cid) return categories[i];

	return NULL;
}

vector<SectionModel*> getCategorySections(int category_id) {
	char buffer[1024];
	sprintf(buffer,
	"SELECT S.id, CL.name, SL.name, SL.description "
	"FROM Section S "
	"	INNER JOIN SectionLocale SL ON S.id = SL.sectionID and SL.localeID = %d "
	"	INNER JOIN CategoryLocale CL ON S.categoryID = CL.categoryID and CL.localeID = SL.localeID "
	"WHERE S.categoryID = %d", default_locale_id_, category_id);

	vector<SectionModel*> sections;
	CategoryModel* category;
	category = getCategory(category_id);
	string s_exe(buffer);
	FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;

	rc = sqlite3_get_table(db,s_exe.c_str(),&result,&nrow,&ncol,&zErrMsg);

	if ( rc == SQLITE_OK )
	{
		for (int i=1; i <= nrow; i++)
		{
			// int cid, string label, int questionnaireNo, int amountOfTestQuestions, int time, string image
			sections.push_back(new SectionModel(atoi(result[ncol*i+0]),category, string(result[ncol*i+2]),string(result[ncol*i+3])));
			FILE_LOG(logDEBUG3) << "sqlite3::getCategorySections():" << __LINE__  << ": result[]:" << result[ncol*i+0] << "|" <<  result[ncol*i+1] << "|" << result[ncol*i+2] << "|" << result[ncol*i+2] << endl;
		}
		sqlite3_free_table(result);
	}else{
		throw DBError(string(sqlite3_errmsg(db)),s_exe);
		sqlite3_free_table(result);
	}
	return sections;

}

vector<LanguageModel*> getAllLanguages()
{
	char buffer[1024];
	sprintf(buffer,
	"SELECT L.id, L.code, L.shortCode, LL.name "
	"FROM Locale L "
	"	INNER JOIN LocaleLocale LL ON LL.localeID = L.id AND LL.localeNameID = L.id;");

	vector<LanguageModel*> languages;
	string s_exe(buffer);
	FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;
	rc = sqlite3_get_table(db,s_exe.c_str(),&result,&nrow,&ncol,&zErrMsg);

	if ( rc == SQLITE_OK )
	{
		for (int i=1; i <= nrow; i++)
		{
			languages.push_back(new LanguageModel(atoi(result[ncol*i+0]),string(result[ncol*i+1]), string(result[ncol*i+2]),string(result[ncol*i+3])));
			FILE_LOG(logDEBUG3) << "sqlite3::getAllLanguages():" << __LINE__  << ": result[]:" << result[ncol*i+0] << "|" <<  result[ncol*i+1] << "|" << result[ncol*i+2] << "|" << result[ncol*i+2] << endl;
		}
		sqlite3_free_table(result);
			//languages.push_back(new LanguageModel(atoi(result[nrow*i+1])));
	}else{
		throw DBError(string(sqlite3_errmsg(db)),s_exe);
		sqlite3_free_table(result);
	}
	return languages;


}

vector<int> availableLanguages (int category) {
	char buffer[1024];
	sprintf(buffer,"SELECT DISTINCT(qlang) FROM Quest WHERE QKateg = %d ;",category);
	string s_exe(buffer);
	FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;
	
	if( rc == SQLITE_OK )
	{
		rc = sqlite3_get_table(db,s_exe.c_str(),&result,&nrow,&ncol,&zErrMsg);
		vector<int> plang;
		//printf("lang size: %d\nnrow=%d\n",(int)plang.size(),nrow);
		if (nrow > 0) for (int i=1;i<=nrow;i++) plang.push_back(atoi(result[i])) ;
		//printf("lang size: %d\nnrow=%d\n",plang.size(),nrow);
		// else probably wrong category id
		sqlite3_free_table(result);
		return plang;
	}
	else
	{
		throw DBError(string(sqlite3_errmsg(db)),s_exe);
		sqlite3_free_table(result);
	}
}

vector<int> *testTemplate ( int category, int language ) {
	
	  int qNo = getTestTemplateNOQ(category, language);
	  //tTime = getTestTime(category);
	  //tCategory = category;
	  
	  char buffer[1024];
	  sprintf(buffer,"SELECT Qpag,qcod "
			  "FROM Quest, Numbs "
			  "WHERE "
			  "KCod = %d and PCod = Qpag and KCod = QKateg and qlang = %d "
			  "ORDER BY qpag;",
			  category,language);
	  string s_exe(buffer);
	  FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;
	  rc = sqlite3_get_table(db,s_exe.c_str(),&result,&nrow,&ncol,&zErrMsg);

	  if( rc == SQLITE_OK )
	  {
		  vector<int> *v = new vector<int>[qNo+1];
		  assert(nrow != 0);
		  for(int i=1; i <= nrow;i++)
			 v[atoi(result[ncol*i])-1].push_back(atoi(result[ncol*i+1]));
		 
		 sqlite3_free_table(result);
		 return v;

	  } else { throw DBError(sqlite3_errmsg(db),s_exe.c_str()); }
	  
	  
	  return NULL;
  }
  
  QuestionModel *getQuestionArray(int cid, int *array) {
	  int qNo = getCategory(cid)->getAmountOfTestQuestions();
	  QuestionModel *q = new QuestionModel[qNo];

	  for (int i=0; i<qNo; i++)
		q[i] = getQuestion(array[i]);
		
	  return q;
  }

  TestModel* getTest(int cid, int *array) {
	  int qNo = getCategory(cid)->getAmountOfTestQuestions();
	  return new TestModel(getQuestionArray(cid, array),qNo, getCategory(cid));
  }

  TestModel* getTest(int catid,int langid) {
	  default_locale_id_ = langid;
	  vector<int> *v = testTemplate(catid,langid);
	  int *array = createRandomTestFromTemplate(catid, v);
	  //getQuestions(catid, array);
	  return getTest(catid, array);
  }

  QuestionModel getQuestion(int qid) {
	  char buffer[1024];
	  sprintf(buffer,"SELECT qlect, QPhoto, QSound, QBook, alect, ACorr, ASound, AAA "
			  "FROM Quest,answer "
			  "WHERE qcod = aqcod and qcod = %d "
			  "ORDER BY RANDOM();",
			  qid);
	  string s_exe(buffer);
	  FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;
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
		 QuestionModel q =  QuestionModel(result[ncol],result[ncol+1],result[ncol+2],result[ncol+3],a,nrow);
		 sqlite3_free_table(result);
		 return q;	 
     }else {throw DBError(sqlite3_errmsg(db),s_exe.c_str());}
     
     sqlite3_free_table(result);
     return QuestionModel();
  }

  QuestionModel* getQuestions(int cid, int* qid) {

	  int qNo = getCategory(cid)->getAmountOfTestQuestions();
	  //string s_exe(buffer);
	  QuestionModel *question = new QuestionModel[qNo];

	  stringstream ss;
	  string ss_exe("SELECT qlect, QPhoto, QSound, QBook, alect, ACorr, ASound, AAA, AQCOD "
			  "FROM Quest,answer "
			  "WHERE qcod = aqcod and qcod IN ( ");

	  ss << ss_exe;
	  for (int i=0; i<qNo; i++)
	  {
		  ss << qid[i];
		  if (i != qNo -1) ss << ", ";
		  else ss << " )";
	  }

	  ss << " ORDER BY RANDOM();";

	  string s_exe(ss.str());
	  FILE_LOG(logDEBUG1) << __FUNCTION__<<":" << __FILE__ << ":"<<  __LINE__ <<" Query: " << s_exe;

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
		 QuestionModel q =  QuestionModel(result[ncol],result[ncol+1],result[ncol+2],result[ncol+3],a,nrow);
		 sqlite3_free_table(result);
		 return question;
     }else {throw DBError(sqlite3_errmsg(db),s_exe.c_str());}

     sqlite3_free_table(result);
     return question;
  }


  ~SQLITE3(){
      sqlite3_close(db);
  } 
};

