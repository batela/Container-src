/*
 * BSCLEnlace.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#include "../include/BSCLEnlace.h"

namespace container {
extern log4cpp::Category &log;

BSCLEnlace::BSCLEnlace() {
	SetStartByte(0x02);
	SetEndByte(0x03);

}

BSCLEnlace::~BSCLEnlace() {
	// TODO Auto-generated destructor stub
}

int BSCLEnlace::analizaTrama(char buffer[]){
	int res = -1;
	char peso[10];
	char data[10];
	if (VerificaTrama(buffer) == 0){
		memset (peso,0,10);
		memcpy (&buffer[3],peso,5);
		vector<std::string> items;
		items.push_back(&buffer[2]);
		items.push_back(&buffer[3]);
		items.push_back(peso);
		completaBSCL(items,this->bascula);
	}
	else {
		log.error("%s: %s",__FILE__, "Trama Bascula incorrecta");
	}
	return res;
}

int BSCLEnlace::VerificaTrama (char buffer[])
{
	log.info("%s: %s",__FILE__, "Comenzando funcion..");
	log.info("%s: %s",__FILE__, "Terminando funcion!!");
	return 0;
}

int BSCLEnlace::completaBSCL (vector<std::string> items, Bascula &bsc){
	log.info("%s: %s",__FILE__, "Comenzando funcion..");
	bsc.SetPeso(atoi(items[2].data()));
	//bsc.SetSigno((char)items[1].data());
	log.info("%s: %s",__FILE__, "Terminando funcion!!");
	return 0;
}

} /* namespace container */
