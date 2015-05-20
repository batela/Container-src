/*
 * DX80Enlace.cpp
 *
 *  Created on: May 1, 2015
 *      Author: root
 */

#include "../include/DX80Enlace.h"

namespace container {
extern log4cpp::Category &log;
/***
 *
 */
DX80Enlace::DX80Enlace() {
	cfg = NULL;
}
/***
 *
 */
DX80Enlace::~DX80Enlace() {
}
void DX80Enlace::Configure (string a){
	if (ConfigReadFile(a.data(), &cfg) != CONFIG_OK) {
		log.error("%s: %s %s",__FILE__, "Error leyendo fichero de confguracion: ", a.data());
		cfg = NULL;
	}
}
/**
 * res = 0 correcto res != error
 */
int DX80Enlace::analizaTrama (char *buffer){
	log.debug("%s: %s",__FILE__, "Comienza funcion AnalizaTrama");
	int res = 1;
	int peso = VerificaTrama(buffer) ;
	if (peso != -1028) res = 0;
	dx.setPeso(peso);

	log.debug("%s: %s",__FILE__, "Fin de funcion AnalizaTrama");
	return res;

}
/***
 * res = 0, todos los pesos correctos, res =1 un peso erroneo...
 */
int DX80Enlace::VerificaTrama (char *buffer){
	log.debug("%s: %s",__FILE__, "Comienza funcion VerificaTrama");

	dx.setInput1(256*buffer[1] + buffer[0]);
	dx.setInput2(256*buffer[3] + buffer[2]);
	dx.setInput3(256*buffer[5] + buffer[4]);
	dx.setInput4(256*buffer[7] + buffer[6]);

	int res = CalculaPeso();
	log.info("%s: %s %d entradas: %d - %d - %d - %d",__FILE__, "Peso calculado: " , res, dx.getInput1() ,dx.getInput2() , dx.getInput3() ,dx.getInput4());

	log.debug("%s: %s",__FILE__, "Fin de funcion VerificaTrama");
	return res;
}
/**
 *
 */
///TODO Implementar funcion de calculo
int DX80Enlace::CalculaPeso(){
	int rangos[4][4];
	for (int i = 0 ;i < 4; i++){
		for (int j = 0 ;j < 4; j++){
			if (((dx.getValorIdx(i) - dx.getValorIdx(j)) * 100 / dx.getValorIdx(i)) >= atoi(Env::getInstance()->GetValue("toleranciapeso").data()) )
					rangos[i][j] = 1;
			else
				rangos[i][j] = 0;
		}
	}
	return (dx.getInput1() + dx.getInput2() +dx.getInput3() + dx.getInput4());
}
} /* namespace container */
