/*
 * Bascula.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#include "../include/Bascula.h"

namespace container {

	Bascula::Bascula() {
	 pthread_mutex_init(&mtxBascula, NULL);
	}

	Bascula::~Bascula() {
	}
	/***
	 *
	 */
	int Bascula::GetPeso()
	{
		pthread_mutex_lock(&mtxBascula);
		int valor = 0 ;
		valor = this->peso ;
		pthread_mutex_unlock(&mtxBascula);
		return valor;
	}
	/***
	 *
	 */
	char Bascula::GetSigno()
	{
		pthread_mutex_lock(&mtxBascula);
		char valor = 0 ;
		valor = this->signo ;
		pthread_mutex_unlock(&mtxBascula);
		return valor;
	}
	/**
	 *
	 */
	void Bascula::SetPeso(int peso)
	{
		pthread_mutex_lock(&mtxBascula);
		this->peso = peso;
		pthread_mutex_unlock(&mtxBascula);
	}
	/***
	 *
	 */
	void Bascula::SetSigno(char signo)
	{
		pthread_mutex_lock(&mtxBascula);
		this->signo = signo;
		pthread_mutex_unlock(&mtxBascula);
	}

} /* namespace container */
