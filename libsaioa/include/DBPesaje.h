/*
 * DBPesaje.h
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#ifndef DBPESAJE_H_
#define DBPESAJE_H_

#include "../include/DB.h"

namespace container {

class DBPesaje: public DB {
public:
	DBPesaje(string path);
	virtual ~DBPesaje();
	int ReadHistoricData (string &data);
};

} /* namespace container */

#endif /* DBPESAJE_H_ */