/*
 * GPSEnlace.h
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#ifndef CATOSENLACE_H_
#define CATOSENLACE_H_
#include <vector>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "Enlace.h"
#include "Env.h"
#include "GPS.h"
using namespace std;
namespace container {

class CATOSEnlace: public container::Enlace {
public:
	static const int LONGITUD_GPGGA = 15;

	CATOSEnlace();
	virtual ~CATOSEnlace();
	int analizaTrama (char buffer []);
	int crearTrama (char buffer []);
private:
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) ;
	std::vector<std::string> split(const std::string &s, char delim);
};

} /* namespace container */
#endif /* GPSENLACE_H_ */
