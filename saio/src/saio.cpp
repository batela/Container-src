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
	float gLat = -1;
	float gLon = -1;

	log4cpp::Category &log  = log4cpp::Category::getRoot();
	log4cpp::PropertyConfigurator::configure( Env::getInstance("/home/batela/cnf/saio.cnf")->GetValue("logproperties") );
	log.info("%s: %s",__FILE__, "Iniciando aplicacion de gruas...");

	//Inicializamos el publcador para el IHM
	RabbitConnection rc(Env::getInstance()->GetValue("logproperties"),Env::getInstance()->GetValue("logproperties"));
	rc.initialize();

	//Inicializamos la brujula
	HMC5883L brj;
	brj.initialize();
	if (brj.testConnection())
		log.info("%s: %s",__FILE__, 	"Conexion en Brujula OK");
	else
		log.error("%s: %s",__FILE__,	"Error en conexion en la Brujula");

	PosicionGrua pg;
	//Inicializamos la lista de calles y campa
	Campa campa ;
	campa.CargarCalles(Env::getInstance()->GetValue("path_calles"));

	//Inicializamos la conexión con el GPS
	GPSEnlace *gps = new GPSEnlace ();
	RS232Puerto *gpsPort = new RS232Puerto(Env::getInstance()->GetValue("puertogps"), 9600);
	Explorador *exGps 		= new Explorador (gps,gpsPort,true);

	//Inicializamos la conexión la MOXA para obtener la posicion del brazo
	IOEnlace *brazo = new IOEnlace();
	MODBUSPuerto *moxaPort = new MODBUSPuerto(Env::getInstance()->GetValue("puertomoxa"), 9600);
	Explorador *exBrazo = new Explorador (brazo,moxaPort,true);

	//Inicializamos la comunicacion con el CATOS
	CATOSEnlace *cts 			= new CATOSEnlace();
	RS232Puerto *ctsPort 	= new RS232Puerto(Env::getInstance()->GetValue("puertocatos"), 9600);
	Explorador *exCatos 	= new Explorador (cts,ctsPort,false);

	while (true){
		float angBrujula = brj.getBearing(); //Leemos lo que nos de la brujula
		if (gps->getGPS()->getCalidad() > 0){

			if (gLat != gps->getGPS()->getLatitud() || gLon != gps->getGPS()->getLongitud() ){
				gLat = gps->getGPS()->getLatitud();
				gLon = gps->getGPS()->getLongitud();
				campa.CalcularPosicion(gLat,gLon,pg);
				//TRAMA GPS  :DATAGPS;LAT;LONG;NUMGPS;CALLE;BLOQUE;DISTX;DISTY;FECHA
				//DATAGPS;45º34'34''N; 03º34'34'' W;8;2;B;499;233;23:14:56
				//TRAMA GRUA :DATAGRUA;LONG;ANGULO;LOCKS;FECHA
				//DATAGRUA;10;13;ABIERTO;23:14:56
				//cts->crearTrama(1,pg,cts->txbuffer);
				//exCatos->Enviar(strlen(cts->txbuffer),cts->txbuffer);
			}
		}
		brazo->getBrazo()->getAngulo();
		brazo->getBrazo()->getAngulo();
		brazo->getBrazo()->isLocks();

		log.info("%s: %s",__FILE__, "Esperando lectura correcta..");
		sleep (1);

	}
	return 0;
}
