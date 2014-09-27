/*
 * IOEnlace.h
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#ifndef IOENLACE_H_
#define IOENLACE_H_

#include "Enlace.h"

namespace container {

class IOEnlace: public container::Enlace {
public:
	IOEnlace();
	virtual ~IOEnlace();
};

} /* namespace container */
#endif /* IOENLACE_H_ */
