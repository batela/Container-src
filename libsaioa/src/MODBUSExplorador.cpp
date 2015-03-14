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
}

MODBUSExplorador::~MODBUSExplorador() {
	// TODO Auto-generated destructor stub
}


int MODBUSExplorador::Explora (){
	log.info("%s: %s",__FILE__, "Comienza exploracion MODBUS");
	int res = 1 ;
	char buffer[256];
	res = 0 ;
	memset (buffer,0,256);

	if (this->getPuerto()->getIsOpen() == false) {
		this->Cerrar();
		this->Abrir();
	}
	else {
		if (((MODBUSPuerto*)getPuerto())->leer(0x01,0,4,buffer) > 0) res = (getEnlace())->analizaTrama(buffer);
	}


	log.info("%s: %s",__FILE__, "Termina exploracion MODBUS");
	return res;
}
} /* namespace container */
