/*
 * RS232Puerto.h
 *
 *  Created on: Sep 21, 2014
 *      Author: borja
 */

#ifndef RS232PUERTO_H_
#define RS232PUERTO_H_


#include "Puerto.h"
#include <iostream>
#include <fstream>
#include <SerialStream.h>
#include "Env.h"

using namespace LibSerial ;
using namespace std;
namespace container {

class RS232Puerto: public container::Puerto {
public:
	RS232Puerto(string id, int br=9600);
	virtual ~RS232Puerto();
	int abrir();
	void cerrar();
	int reabrir();
	int leer (char buffer[]);
	int leerSimple (char &data);
	int escribir (char buffer[], int count);
private:
	int baudrate;
	SerialStream serial_port ;
};

} /* namespace container */
#endif /* RS232PUERTO_H_ */
