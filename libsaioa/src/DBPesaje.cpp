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
	string sql ="SELECT * FROM thistorico;";
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

} /* namespace container */
