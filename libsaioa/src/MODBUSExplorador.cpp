/*
 * MODBUSExplorador.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: root
 */

#include "../include/MODBUSExplorador.h"
#include "../include/IOEnlace.h"
namespace container {
extern log4cpp::Category &log;
MODBUSExplorador::MODBUSExplorador(Enlace* e, Puerto* p) : Explorador (e,p,false){
	Abrir();
	Explora();
}

MODBUSExplorador::~MODBUSExplorador() {
	// TODO Auto-generated destructor stub
}

int MODBUSExplorador::Explora (){
	log.info("%s: %s",__FILE__, "Comienza exploracion MODBUS");
	int res = 0 ;
	char buffer[256];
	if (((MODBUSPuerto*)getPuerto())->leer(0x01,1,4,buffer) > 0)
		(getEnlace())->analizaTrama(buffer);

	log.info("%s: %s",__FILE__, "Termina exploracion MODBUS");
}
} /* namespace container */
