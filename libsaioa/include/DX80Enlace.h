/*
 * DX80Enlace.h
 *
 *  Created on: May 1, 2015
 *      Author: root
 */

#ifndef DX80ENLACE_H_
#define DX80ENLACE_H_

#include "configini.h"
#include "Enlace.h"
#include "DX80.h"

namespace container {

class DX80Enlace: public Enlace {
public:
	DX80Enlace();
	virtual ~DX80Enlace();
	int analizaTrama (char *buffer);
	int VerificaTrama (char *buffer);
	void Configure (string a);

	DX80 * getDX () {return &dx;} ;
private:
	int CalculaPeso();
	DX80 dx;
	Config *cfg;

};

} /* namespace container */

#endif /* DX80ENLACE_H_ */
