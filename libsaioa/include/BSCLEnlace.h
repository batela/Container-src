/*
 * BSCLEnlace.h
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#ifndef BSCLENLACE_H_
#define BSCLENLACE_H_

#include "Enlace.h"
#include "Bascula.h"

namespace container {

class BSCLEnlace: public Enlace {
public:
	BSCLEnlace();
	virtual ~BSCLEnlace();
	int analizaTrama (char buffer []);
	Bascula * getGPS () {return &bascula;} ;

private:
	int completaBSCL (vector<std::string> items, Bascula &gps);
	Bascula bascula;
};

} /* namespace container */

#endif /* BSCLENLACE_H_ */
