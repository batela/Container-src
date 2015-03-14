/*
 * Bascula.h
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#ifndef BASCULA_H_
#define BASCULA_H_
#include <ctime>
#include <pthread.h>
using namespace std;
namespace container {

class Bascula {
public:
	Bascula();
	virtual ~Bascula();

	int GetPeso() 	;
	char GetSigno()	;
	void SetPeso(int peso)	;
	void SetSigno(char signo) ;

	time_t GetUltimaActualizacion() const {		return ultimaActualizacion;	}
	void GetUltimaActualizacion(time_t ultimaActualizacion) {		this->ultimaActualizacion = ultimaActualizacion;	}
	void SetEstable (bool a) 	{isEstable = a;};
	bool GetEstable () 				{return isEstable ;};
private:
	int peso;
	char signo;
	time_t ultimaActualizacion;
	bool isEstable;
	pthread_mutex_t mtxBascula;
};

} /* namespace container */

#endif /* BASCULA_H_ */
