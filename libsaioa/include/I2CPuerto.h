/*
 * I2CPuerto.h
 *
 *  Created on: Sep 21, 2014
 *      Author: borja
 */

#ifndef I2CPUERTO_H_
#define I2CPUERTO_H_

#include "Puerto.h"

namespace container {

class I2CPuerto: public container::Puerto {
public:
	I2CPuerto();
	virtual ~I2CPuerto();
	void cerrar();
};

} /* namespace container */
#endif /* I2CPUERTO_H_ */
