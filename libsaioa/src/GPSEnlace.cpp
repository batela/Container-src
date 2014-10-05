/*
 * GPSEnlace.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#include "../include/GPSEnlace.h"


namespace container {
extern log4cpp::Category &log;

GPSEnlace::GPSEnlace() {
	// TODO Auto-generated constructor stub
	log.info("ddd");
}

GPSEnlace::~GPSEnlace() {
	// TODO Auto-generated destructor stub
}
/**
 * Devuelve: -1 si la trama es desconcocida, 1 si el tratamiento de la trama es erroneo, 0 si va bine
 *
 */
int GPSEnlace::analizaTrama(char buffer[]){
	int res = -1;
	std::vector<std::string> items = split(buffer,',');
	if (strcmp(items[0].data(),"$GPGGA")== 0)
		res = completaGPS (items , gps);

	return res;
}

int GPSEnlace::completaGPS (vector<std::string> items, GPS &gps){
	int res = 1;
	if (items.size() == GPSEnlace::LONGITUD_GPGGA){
		gps.setFecha(atoi(items[1].data()));
		gps.setLatitud(atof(items[2].data()));
		gps.setCLatitud(items[3].data()[0]);
		gps.setLongitud(atof(items[4].data()));
		gps.setCLongitud(items[5].data()[0]);
		gps.setSatelites(atoi(items[7].data()));
		gps.setCalidad(atoi(items[6].data()));
		gps.setAltitud(atof(items[9].data()));
		res =  0 ;
	}
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
