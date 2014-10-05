/*
 * Enlace.h
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#ifndef ENLACE_H_
#define ENLACE_H_

namespace container {

class Enlace {
public:
	Enlace();
	virtual ~Enlace();
	virtual int analizaTrama(char * buffer) {return 0;};
};

} /* namespace container */
#endif /* ENLACE_H_ */
