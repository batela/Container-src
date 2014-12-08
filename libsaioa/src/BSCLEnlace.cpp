/*
 * BSCLEnlace.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#include "../include/BSCLEnlace.h"

namespace container {
extern log4cpp::Category &log;

BSCLEnlace::BSCLEnlace() {
	// TODO Auto-generated constructor stub

}

BSCLEnlace::~BSCLEnlace() {
	// TODO Auto-generated destructor stub
}

int BSCLEnlace::analizaTrama(char buffer[]){
	int res = -1;
	std::vector<std::string> items = split(buffer,',');
	return res;
}

int BSCLEnlace::completaBSCL (vector<std::string> items, Bascula &gps){
	log.info("%s: %s",__FILE__, "Comenzando funcion..");

	log.info("%s: %s",__FILE__, "Terminando funcion!!");
	return 0;
}

} /* namespace container */
