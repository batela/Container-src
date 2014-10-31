//============================================================================
// Name        : saio.cpp
// Author      : Batela
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "../include/saio.h"

using namespace std;
using namespace container;
int main() {
	log4cpp::Category &log  = log4cpp::Category::getRoot();
	log4cpp::PropertyConfigurator::configure( Env::getInstance("/home/batela/cnf/saio.cnf")->GetValue("logproperties") );
	log.info("%s: %s",__FILE__, "Iniciando aplicacion de gruas...");

	PosicionGrua pg;
	Campa campa ;
	campa.CargarCalles("/home/batela/cnf/YARD2.ASC");

	GPSEnlace *gps = new GPSEnlace ();
	RS232Puerto *gpsPort = new RS232Puerto("/dev/ttyUSB0", 9600);
	Explorador *exGps 		= new Explorador (gps,gpsPort,true);


	IOEnlace *brj = new IOEnlace("/dev/ttyUSB0", 9600);
	I2CPuerto *i2cPort = new I2CPuerto();
	Explorador *exAnalog = new Explorador (brj,i2cPort,false);

	CATOSEnlace *cts 			= new CATOSEnlace();
	RS232Puerto *ctsPort 	= new RS232Puerto("/dev/ttyUSB1", 9600);
	Explorador *exCatos 	= new Explorador (cts,ctsPort,false);
	float gLat = -1;
	float gLon = -1;
	while (true){
		if (gps->getGPS()->getCalidad() > 0){

			if (gLat != gps->getGPS()->getLatitud() || gLon != gps->getGPS()->getLongitud() ){
				gLat = gps->getGPS()->getLatitud();
				gLon = gps->getGPS()->getLongitud();
				campa.CalcularPosicion(gLat,gLon,pg);
				//cts->crearTrama(1,pg,cts->txbuffer);
				//exCatos->Enviar(strlen(cts->txbuffer),cts->txbuffer);
			}
		}
		log.info("%s: %s",__FILE__, "Esperando lectura correcta..");
		sleep (1);

	}
	return 0;
}
