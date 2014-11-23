/*
 * IOEnlace.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#include "../include/IOEnlace.h"

namespace container {
	extern log4cpp::Category &log;
	IOEnlace::IOEnlace() {
	}
	IOEnlace::~IOEnlace() {
		// TODO Auto-generated destructor stub
	}
	/**
	 * @return 0 if OK
	 */
	int IOEnlace::analizaTrama (unsigned short trama[]){
		log.info("%s: %s",__FILE__, "Comienza funcion");
		int res = 0 ;

		log.info("%s: %s",__FILE__, "Fin de funcion");
		return res;
	}


} /* namespace container */
