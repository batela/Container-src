/*
 * Explorador.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#include "../include/Explorador.h"

namespace container {

void* lector (void * explorador){
	Explorador * exp = (Explorador*)explorador;
	while (exp->sigue){
		//exp->getPuerto()->leer();
		//sleep (500);
	}
}

Explorador::Explorador() {
	// Ayyyy que hostia se va a dar mas tarde....
	enlace = NULL;
	puerto = NULL;
	sigue = true ;
}
Explorador::Explorador(Enlace* e, Puerto* p, bool lanzar){
	enlace = e;
	puerto = p;
	sigue = lanzar;
}
Explorador::~Explorador() {
	// TODO Auto-generated destructor stub
	sigue = false ;
}

void Explorador::LanzarExplorador (){
	int iret1 = pthread_create( &idThLector, NULL, lector, this);
}
int Explorador::Enviar (int longitud, Orden orden ){
	return 0 ;
}

} /* namespace container */
