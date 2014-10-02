/*
 * Campa.h
 *
 *  Created on: Oct 2, 2014
 *      Author: borja
 */

#ifndef CAMPA_H_
#define CAMPA_H_
#include <iostream>
# include <list>
#include "../include/Calle.h"
using namespace std;
class Campa {
public:
	Campa();
	virtual ~Campa();

private:
	list <Calle>	calles;
};

#endif /* CAMPA_H_ */
