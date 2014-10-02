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
	log4cpp::PropertyConfigurator::configure( Env::getInstance("/home/borja/Prj/Container/saio.cnf")->GetValue("logproperties") );

	GPSEnlace *gps = new GPSEnlace ();
	RS232Puerto *gpsPort = new RS232Puerto("/dev/ttyUSB0", 9600);
	Explorador *exGps 		= new Explorador (gps,gpsPort,false);
	exGps->LanzarExplorador();

	IOEnlace *brj = new IOEnlace();
	I2CPuerto *i2cPort = new I2CPuerto();
	Explorador *exAnalog = new Explorador (brj,i2cPort,false);
	exAnalog->LanzarExplorador();

	while (true){
		switch (estado){

		}
		sleep (100);
	}
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
