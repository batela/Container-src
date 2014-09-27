/*
 * GPSEnlace.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#include "../include/GPSEnlace.h"


namespace container {

GPSEnlace::GPSEnlace() {
	// TODO Auto-generated constructor stub

}

GPSEnlace::~GPSEnlace() {
	// TODO Auto-generated destructor stub
}

GPS GPSEnlace::analizaTrama(char buffer[]){
	GPS gps;
	std::vector<std::string> items = split(buffer,',');
	int res = completaGPS (items , gps) ;
	return gps;
}

int GPSEnlace::completaGPS (vector<std::string> items, GPS &gps){
	int res = 0 ;
	if (items.size()!= 15) res = -1;
	/*
	(long index=0; index<(long)vectorOne.size(); ++index) {
			16        cout << "Element " << index << ": " << vectorOne.at(index) << endl;
			17
			    }
			*/
	return res;
}
std::vector<std::string> & GPSEnlace::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> GPSEnlace::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
} /* namespace container */
