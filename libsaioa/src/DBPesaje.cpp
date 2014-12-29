/*
 * DBPesaje.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#include "../include/DBPesaje.h"

namespace container {
extern log4cpp::Category &log ;
DBPesaje::DBPesaje(string path) : DB(path) {

}

DBPesaje::~DBPesaje() {
}

int DBPesaje::ReadHistoricData (string startdate, string enddate,string &data){

	log.info("%s-%s: %s", __FILE__,__FUNCTION__, "Starting function..") ;

	bool res = false ;
	string sql ="SELECT * FROM thistorico WHERE fecha>='" +startdate + "' and fecha<='" + enddate +"';";
	log.debug("%s-%s: %s %s", __FILE__,__FUNCTION__, "Executing query:" , sql.data()) ;

	int idCanal;
	double valor;
	string fecha;
  sqlite3_stmt *statement;
  if ( sqlite3_prepare(db,sql.c_str(),-1,&statement,0) == SQLITE_OK ) {
  	int ctotal = sqlite3_column_count(statement);
    int res = SQLITE_ROW;
    while ( res != SQLITE_DONE && res!=SQLITE_ERROR )  {
    	res = sqlite3_step(statement);
      if ( res == SQLITE_ROW ){
      	for ( int i = 0; i < ctotal; i++ ) {
      		switch (i){
      			case 1: idCanal =((int)sqlite3_column_int(statement, i));break;
      			case 2:	valor 	= ((double)sqlite3_column_double(statement, i)); break;
      			case 3:	fecha 	=((char*)sqlite3_column_text(statement, i)); break;
      		}
        }
      	char raw[256];
      	sprintf(raw,"%d;%f;%s\n",idCanal,valor,fecha.data());
      	data = data + raw;
      }
    }
  }
  log.info("%s-%s: %s", __FILE__,__FUNCTION__, "Ending function..") ;
	return res ;
}

int DBPesaje::ReadMaxDayData (string today, string &data){

	log.info("%s-%s: %s", __FILE__,__FUNCTION__, "Starting function..") ;

	bool res = false ;
	string sql ="SELECT * FROM thistorico WHERE fecha>='" +today + " 00:00:00' and fecha<='" + today +" 23:59:59';";
	log.debug("%s-%s: %s %s", __FILE__,__FUNCTION__, "Executing query:" , sql.data()) ;

	int idCanal;
	double valor;
	string fecha;
  sqlite3_stmt *statement;
  if ( sqlite3_prepare(db,sql.c_str(),-1,&statement,0) == SQLITE_OK ) {
  	int ctotal = sqlite3_column_count(statement);
    int res = SQLITE_ROW;
    while ( res != SQLITE_DONE && res!=SQLITE_ERROR )  {
    	res = sqlite3_step(statement);
      if ( res == SQLITE_ROW ){
      	for ( int i = 0; i < ctotal; i++ ) {
      		switch (i){
      			case 1: idCanal =((int)sqlite3_column_int(statement, i));break;
      			case 2:	valor 	= ((double)sqlite3_column_double(statement, i)); break;
      			case 3:	fecha 	=((char*)sqlite3_column_text(statement, i)); break;
      		}
        }
      	char raw[256];
      	sprintf(raw,"%d;%f;%s\n",idCanal,valor,fecha.data());
      	data = data + raw;
      }
    }
  }
  log.info("%s-%s: %s", __FILE__,__FUNCTION__, "Ending function..") ;
	return res ;
}

int DBPesaje::InsertData (int canal,float valor){

	log.info("%s-%s: %s", __FILE__,__FUNCTION__, "Starting function..") ;

	bool res = false ;

	time_t rawtime;
	struct tm * timeinfo;
	char now [20];
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime (now,20,"%F %T",timeinfo);
	char query[80];

	sprintf (query,"UPDATE tvalores SET valor=%f,fecha='%s' WHERE idCanal=%d",valor,now,canal);
	//string sql ="UPDATE tvalores SET valor=" +buffer+",fecha='" + now +"' WHERE idCanal=" + canal;
	log.debug("%s-%s: %s %s", __FILE__,__FUNCTION__, "Executing query:" , query) ;

  sqlite3_stmt *statement;
  if ( sqlite3_prepare(db,query,-1,&statement,0) == SQLITE_OK ) {
  		res = sqlite3_step(statement);
  		sqlite3_finalize(statement);
  }
  else {
  	log.error("%s-%s: %s", __FILE__,__FUNCTION__, "Error al ejecutar query") ;
  }
  log.info("%s-%s: %s", __FILE__,__FUNCTION__, "Ending function..") ;
	return res ;
}

} /* namespace container */
