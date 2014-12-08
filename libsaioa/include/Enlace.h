/*
 * Enlace.h
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#ifndef ENLACE_H_
#define ENLACE_H_
#include <vector>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "Env.h"
using namespace std;
namespace container {

class Enlace {
public:
	Enlace();
	virtual ~Enlace();
	virtual int analizaTrama(char * buffer) {return 0;};
	char txbuffer[256];
	char rxbuffer[256];
protected:
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) ;
	std::vector<std::string> split(const std::string &s, char delim);
};

} /* namespace container */
#endif /* ENLACE_H_ */
