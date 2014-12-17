/*
 * MODBUSExplorador.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: root
 */

#include "../include/MODBUSExplorador.h"

namespace container {
extern log4cpp::Category &log;
MODBUSExplorador::MODBUSExplorador(Enlace* e, Puerto* p) : Explorador (e,p,false){
	// TODO Auto-generated constructor stub
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
	res= ((MODBUSPuerto*)getPuerto())->leer(0x01,0,4,buffer);
	log.info("%s: %s",__FILE__, "Termina exploracion MODBUS");
}
} /* namespace container */
