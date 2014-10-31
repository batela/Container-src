/*
 * IOEnlace.h
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#ifndef IOENLACE_H_
#define IOENLACE_H_
#include <inttypes.h>
#include <unistd.h>
#include "Env.h"
#include "modbus.h"
#include "modbus-ct.h"

#include "Enlace.h"

namespace container {

class IOEnlace: public container::Enlace {
public:
	IOEnlace(string port, int bauds);
	IOEnlace(string port);
	virtual ~IOEnlace();
	int conectar();
	int cerrar();
	int leerBytes (int a , unsigned short int data[]);
private:
	modbus_t *ctx;
	string port;
	int bauds;
};

} /* namespace container */
#endif /* IOENLACE_H_ */
