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
	log.info("%s: %s %s",__FILE__, "Lanzado thread lector...");

	Explorador * exp = (Explorador*)explorador;
	//char buffer[256];
	int res = 0 ;
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	//tim.tv_nsec = 500000000L;
	tim.tv_nsec = 500000000L;
	while (exp->sigue){
		res = 0;
		if (exp->getPuerto()->getIsOpen()== false) {
			res = exp->getPuerto()->abrir();
		}
		else {
			exp->getEnlace()->rxbuffer[0]= 0;
			res = exp->getPuerto()->leer(exp->getEnlace()->rxbuffer);
		}
		if (res >0){
			log.debug("%s: %s %s",__FILE__, "Trama recibida..", exp->getEnlace()->rxbuffer);
			exp->getEnlace()->analizaTrama(exp->getEnlace()->rxbuffer);
			exp->getEnlace()->rxbuffer[0]= 0;
		}
		else if (res < 0){
			exp->getPuerto()->cerrar();
		}
		log.info("%s: %s",__FILE__, "Esperamos trama un segundo..");
		nanosleep(&tim , &tim2);
		//sleep (1);
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
	if (sigue) LanzarExplorador();
}
Explorador::~Explorador() {
	// TODO Auto-generated destructor stub
	sigue = false ;
}

void Explorador::LanzarExplorador (){
	log.info("%s: %s", __FILE__, "Abriendo puerto");
	if (puerto->abrir() != 0) log.error("%s: %s", __FILE__, "Error abriendo puerto!!");
	int iret1 = pthread_create( &idThLector, NULL, lector, this);

}
int Explorador::Enviar (int longitud, Orden orden ){
	return 0 ;
}

int Explorador::Enviar (int longitud,char *buffer ){
	if (sigue == false) puerto->abrir();
	puerto->escribir(buffer,longitud);
	if (sigue == false) puerto->cerrar();
	return 0 ;
}

bool Explorador::Abrir ( ){
	int res = -1;
	if (this->getPuerto()->getIsOpen()== false) {
				res = this->getPuerto()->abrir();
	}
	return (res==0?true:false);
}

bool Explorador::Cerrar ( ){
	return (true);
}
} /* namespace container */
