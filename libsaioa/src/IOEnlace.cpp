/*
 * IOEnlace.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#include "../include/IOEnlace.h"

namespace container {

IOEnlace::IOEnlace(string port) {
		bauds = 9600;
		this->port = port;

}

IOEnlace::IOEnlace(string port, int bauds) {
	this->bauds = bauds;
	this->port = port;
}

IOEnlace::~IOEnlace() {
	// TODO Auto-generated destructor stub
}
/**
 * @return 0 if OK
 */
int IOEnlace::conectar (){
	int res = 1 ;
	if ((ctx = modbus_new_rtu(port.data(), bauds, 'N', 8, 1)) != NULL){
		if (modbus_connect(ctx) == -1) {
			//modbus_strerror(errno);
			modbus_free(ctx);
		  res = 1;
		}
		else res = 0 ;
	}

	return res;
}

int IOEnlace::cerrar (){
	modbus_close(ctx);
	modbus_free(ctx);
}

int IOEnlace::leerBytes (int a , unsigned short int data[]){
	int res = modbus_read_registers(ctx, UT_REGISTERS_ADDRESS,a, data);
}


} /* namespace container */
