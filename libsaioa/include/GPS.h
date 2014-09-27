/*
 * GPS.h
 *
 *  Created on: Sep 26, 2014
 *      Author: borja
 */

#ifndef GPS_H_
#define GPS_H_
#include <string>
#include "time.h"
using namespace std;
namespace container {

class GPS {
public:
	GPS();
	virtual ~GPS();
	int getFecha ()			{return fecha;};
	float getLatitud ()	{return latitud;};
	float getLongitud (){return longitud;};
	int getCLatitud ()	{return clatitud;};
	char getCLongitud (){return clongitud;};
	int getSatelites ()	{return satelites;};
	//time getTFecha () 	{return tfecha;};

	void setFecha 	(int a) 	{ fecha = a;  };
	void setLatitud (int a) 	{ latitud = a; };
	void setLongitud (int a) 	{ longitud = a; };
	void setCLatitud (char a) { clatitud = a; };
	void setCLongitud (char a) { clongitud = a; };
	void setSatelites (int a)  {satelites = a;} ;
private:
	int 	fecha;
	float latitud;
	float longitud;
	char 	clatitud;
	char 	clongitud;
	int 	satelites;
	//time 	tfecha;

};

} /* namespace container */
#endif /* GPS_H_ */
