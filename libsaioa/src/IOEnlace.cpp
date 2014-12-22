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
	int IOEnlace::analizaTrama (char * trama){
		log.info("%s: %s",__FILE__, "Comienza funcion");
		int res = 0 ;
		locks.SetLock01(trama[0]);
		locks.SetLock02(trama[1]);
		locks.SetLock03(trama[2]);
		locks.SetLock04(trama[3]);
		log.info("%s: %s",__FILE__, "Fin de funcion");
		return res;
	}


} /* namespace container */
