/*
 * MODBUSPuerto.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: root
 */

#include "../include/MODBUSPuerto.h"
using namespace std;
namespace container {
	extern log4cpp::Category &log;
	MODBUSPuerto::MODBUSPuerto (string id, int br):Puerto(id,RS232) {
		this->baudrate = br ;
		ctx = NULL ;
	}

	MODBUSPuerto::~MODBUSPuerto() {
		if (ctx != NULL ) cerrar();
	}

	int MODBUSPuerto::abrir(){
		log.info("%s: %s %s",__FILE__, "Comienza abrir puerto..",this->getName().data());
		int res = 1 ;
		struct timeval response_timeout;
		response_timeout.tv_sec = 1;
		response_timeout.tv_usec = 0;
		if ((ctx = modbus_new_rtu(this->getName().data(), baudrate, 'N', 8, 1)) != NULL){
			modbus_set_slave(ctx, 0x01);
			modbus_set_response_timeout(ctx, &response_timeout);
			if (modbus_connect(ctx) == -1) {
				//modbus_strerror(errno);
				modbus_free(ctx);
				res = 1;
			}
			else res = 0 ;
		}
		log.info("%s: %s",__FILE__, "Puerto abierto!!");
		return res ;
	}

	void MODBUSPuerto::cerrar(){
		modbus_close(ctx);
		modbus_free(ctx);
	}

	int MODBUSPuerto::reabrir(){
		this->cerrar();
		return ( this->abrir() );
	}
	/**
	 * Devuelve -1 si hay error.
	 */
	int MODBUSPuerto::leer (unsigned short  buffer[]){
		log.info("%s: %s",__FILE__, "Inicio funcion leer");
		int count = 0 ;
		if ((count =  modbus_read_input_registers(ctx,0x0048,2, buffer)) == -1){
				//log.error("%s\n", modbus_strerror(errno));
		}
		log.info("%s: %s",__FILE__, "Fin funcion leer modbus!!");
		return count;
	}

	int MODBUSPuerto::escribir (char buffer[], int count){
		log.warn("%s: %s",__FILE__, "Funcion sin implementar");
		return 0;
	}

} /* namespace Container */
