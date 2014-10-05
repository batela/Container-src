/*
 * Campa.cpp
 *
 *  Created on: Oct 2, 2014
 *      Author: borja
 */


#include "../include/Campa.h"

namespace container {
extern log4cpp::Category &log;

Campa::Campa() {
	Inicializa();
}
Campa::~Campa() {
	// TODO Auto-generated destructor stub
}

void Campa::Inicializa (){
	elipsoide= atoi (Env::getInstance()->GetValue("elipsoide").data());
	float latbase = atof (Env::getInstance()->GetValue("latbase").data());
	float lonbase = atof (Env::getInstance()->GetValue("lonbase").data());
	umbralCalle = atof (Env::getInstance()->GetValue("umbralcalle").data());
	LLtoUTM(elipsoide, latbase,lonbase, UTMNorthingBase, UTMEastingBase, UTMZoneBase);
}
/**
 * Devuelve el numero de calles cargadas con exito
 */
int Campa::CargarCalles(string a)
{
	log.info("%s: %s %s",__FILE__, "Comienza carga de calles..",a.data());
		string id, eq, val,line;
    ifstream cfgfile (a.data());
    int count = 0 ;
    while(getline((std::istream&)cfgfile, line)){
    	log.info("%s: %s %s",__FILE__, "Leida linea: ",line.data());
      if ((line[0] == '#') || (line[0] == '0')) continue;  // skip comments and lline with 0
      vector<string> items = this->split (line,' ');
      if (items.size() == 11 )
      	if (CrearCalle (items) == 0 ) count++;
    }
    log.info("%s: %s %d",__FILE__, "Finalizada carga de calles con: ",count);
    return count ;
}

int Campa::CrearCalle (vector<string> items){
	int res = 0 ;
	Calle *cc = new Calle();
	cc->setId(atoi(items[0].data()));
	cc->setYi(atof(items[1].data()));
	cc->setXi(atof(items[2].data()));
	cc->setYf(atof(items[3].data()));
	cc->setXf(atof(items[4].data()));
	/// TODO flata el resto
	cc->CrearRecta();
	calles.push_back(cc);
	return res;
}

vector<std::string> &Campa::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::istringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
  	//cout << "Config Item .." << item << "\n";
  	if (!item.empty() )elems.push_back(item);
  }
    return elems;
}


vector<std::string> Campa::split(const std::string &s, char delim) {
	vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

void Campa::CalcularPosicion(float lat, float lon, PosicionGrua &pg) {

	log.info("%s: %s %f %f",__FILE__, "Inicia CalcularPosicion con latitud y longitud: ", lat,lon);


	double UTMNorthing;
	double UTMEasting;
	char UTMZone[4];
	double Y; //posiciones relativas a la referencia
	double X; //posiciones relativa a la referenciaLL2XY::
	LL2XY ll2xy;


	// 1.-Pasar lat y lon a UTM.
	log.info("%s: %s %f %f",__FILE__, "Calculando Posicion para: ",lat ,lon);
	LLtoUTM(elipsoide , lat, lon, UTMNorthing, UTMEasting, UTMZone);

	// 2.-Calcular posicion relativa a 0-0 en UTM.
  Y = UTMNorthing - UTMNorthingBase;
  X = UTMEasting - UTMEastingBase;

  pg.setGlat(lat);
  pg.setGlon(lon);
  pg.setEasting(UTMEasting);
  pg.setNorting(UTMNorthing);
  pg.setYrelativo(Y);
  pg.setXrelativo(X);

  /* SOLO PARA PRUEBAS*/ ///FIXME ooojojjoojoj!!
  Y=lat;
  X=lon;

  // 3.-Con el norting/easting relativos calcular la distanci a las rectas
  int indice = 1 ;
  float refDistancia = 999999999999;
  pg.setCalle(-1);
  double linePY= 0;
  double linePX= 0;
  for(std::vector<Calle*>::iterator it = calles.begin(); it != calles.end(); ++it) {
  	Calle *cc = *it;
    //float distancia = ll2xy.findDistanceToSegment(cc->getYi(),cc->getXi(),cc->getYf(),cc->getXf(),Y,X);
  	float distancia = ll2xy.findDistanceToSegment(cc->getXi(),cc->getYi(),cc->getXf(),cc->getYf(),X,Y,linePX,linePY);
    log.debug("%s: %s %d %s %f",__FILE__, "Analizada calle: ",indice," distancia: ",distancia);
    if (distancia < refDistancia && distancia <= umbralCalle){
    	refDistancia = distancia;
    	pg.setYsobreCalle(linePY);
    	pg.setXsobreCalle(linePY);
    	pg.setCalle(indice);
    	pg.setBloque("");
    }
    indice++;
  }

  // 4.-Una vez que tenemos la recta situarnos en el origen y ver cuantos contendore hay

  log.info("%s: %s",__FILE__, "Termina CalcularPosicion");
}

}
