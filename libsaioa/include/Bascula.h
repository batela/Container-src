/*
 * Bascula.h
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#ifndef BASCULA_H_
#define BASCULA_H_
#include <ctime>

namespace container {

class Bascula {
public:
	Bascula();
	virtual ~Bascula();

	int GetPeso() const {	return peso;	}
	char GetSigno() const {	return signo;	}
	void SetPeso(int peso) {		this->peso = peso;	}
	void SetSigno(char signo) {		this->signo = signo;	}
	time_t GetUltimaActualizacion() const {		return ultimaActualizacion;	}
	void GetUltimaActualizacion(time_t ultimaActualizacion) {		this->ultimaActualizacion = ultimaActualizacion;	}
	void SetEstable (bool a) {isEstable = a;};
	bool GetEstable () {return isEstable ;};
private:
	int peso;
	char signo;
	time_t ultimaActualizacion;
	bool isEstable;

};

} /* namespace container */

#endif /* BASCULA_H_ */
