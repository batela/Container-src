/*
 * MODBUSExplorador.h
 *
 *  Created on: Dec 17, 2014
 *      Author: root
 */

#ifndef MODBUSEXPLORADOR_H_
#define MODBUSEXPLORADOR_H_

#include "Explorador.h"
#include "MODBUSPuerto.h"
namespace container {

class MODBUSExplorador: public Explorador {
public:
	MODBUSExplorador(Enlace* e, Puerto* p);
	virtual ~MODBUSExplorador();
	int Explora ();
};

} /* namespace container */

#endif /* MODBUSEXPLORADOR_H_ */
