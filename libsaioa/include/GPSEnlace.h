/*
 * GPSEnlace.h
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#ifndef GPSENLACE_H_
#define GPSENLACE_H_
#include <vector>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "Enlace.h"
#include "Env.h"
#include "GPS.h"
#include "llstr.h"
using namespace std;
namespace container {

class GPSEnlace: public container::Enlace {
public:
	static const int LONGITUD_GPGGA = 14;

	GPSEnlace();
	virtual ~GPSEnlace();
	int analizaTrama (char buffer []);
	GPS * getGPS () {return &gps;} ;
private:
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) ;
	std::vector<std::string> split(const std::string &s, char delim);
	int completaGPS (vector<std::string> items, GPS &gps);
	GPS gps;
};

} /* namespace container */
#endif /* GPSENLACE_H_ */
