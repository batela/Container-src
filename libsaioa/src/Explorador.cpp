/*
 * Explorador.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#include "../include/Explorador.h"


namespace container {
extern log4cpp::Category &log;

void* lector (void * explorador){
	Explorador * exp = (Explorador*)explorador;
	char buffer[256];
	while (exp->sigue){
		buffer[0]= 0;
		if (exp->getPuerto()->leer(buffer)>0){
			printf ("Leido %s\n",buffer);
			exp->getEnlace()->analizaTrama(buffer);
			buffer[0]= 0;
		}
		printf ("..");
		sleep (1);
	}
	printf ("Salimos");
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
	log.info("%s: %s", __FILE__, "Abriendo puerto");
	if (puerto->abrir() != 0) log.error("%s: %s", __FILE__, "Error abriendo puerto!!");
	//int res = puerto->abrir() ;
	sigue = true;
	int iret1 = pthread_create( &idThLector, NULL, lector, this);

}
int Explorador::Enviar (int longitud, Orden orden ){
	return 0 ;
}

} /* namespace container */
