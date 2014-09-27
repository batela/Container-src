/*
 * GPSEnlace.h
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#ifndef GPSENLACE_H_
#define GPSENLACE_H_
#include <vector>
#include <string>
#include <sstream>
#include "Enlace.h"
#include "GPS.h"
using namespace std;
namespace container {

class GPSEnlace: public container::Enlace {
public:
	GPSEnlace();
	virtual ~GPSEnlace();
	GPS analizaTrama (char buffer []);
private:
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) ;
	std::vector<std::string> split(const std::string &s, char delim);
	int completaGPS (vector<std::string> items, GPS &gps);
};

} /* namespace container */
#endif /* GPSENLACE_H_ */
