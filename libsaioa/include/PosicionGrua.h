/*
 * PosicionGrua.h
 *
 *  Created on: Oct 4, 2014
 *      Author: root
 */

#ifndef POSICIONGRUA_H_
#define POSICIONGRUA_H_
#include "Env.h"
namespace container {
class PosicionGrua {
public:
	PosicionGrua();
	virtual ~PosicionGrua();

	float getGlat() const {		return glat;	}
	float getGlon() const {		return glon;	}
	const string& getLat() const {		return lat;	}
	const string& getLon() const {		return lon;	}
	float getNorting() const {	return norting;	}
	float getEasting() const { return easting; 	}
	float getXrelativo() const {return Xrelativo;	}
	float getYrelativo() const {return Yrelativo;	}
	const string& getBloque() const {		return bloque;}
	const int getCalle() const { return calle;	}
	float getYNOATUM (){ return Xrelativo ;} ;
	float getXNOATUM (){ return Yrelativo ;} ;
	float getXsobreCalle() const {		return XsobreCalle;	}
	float getYsobreCalle() const {		return YsobreCalle;	}

	void setEasting(float easting) {		this->easting = easting;	}
	void setGlat(float glat) {		this->glat = glat;	}
	void setGlon(float glon) {		this->glon = glon;	}
	void setLat(const string& lat) {		this->lat = lat;	}
	void setLon(const string& lon) {		this->lon = lon;	}
	void setNorting(float norting) { this->norting = norting;	}
	void setXrelativo(float xrelativo) {Xrelativo = xrelativo;}
	void setYrelativo(float yrelativo) {	Yrelativo = yrelativo;	}
	void setBloque(const string& bloque) {this->bloque = bloque;	}
	void setCalle(int calle) { this->calle = calle;	}
	void setXsobreCalle(float xsobreCalle) {		XsobreCalle = xsobreCalle;	}
	void setYsobreCalle(float ysobreCalle) {		YsobreCalle = ysobreCalle;	}

private:
	string lat;
	string lon;
	float glat;
	float glon;
	float norting;
	float easting;
	float Yrelativo;
	float Xrelativo;
	float YsobreCalle;
	float XsobreCalle;

	int calle;
	string bloque;
};
}
#endif /* POSICIONGRUA_H_ */
