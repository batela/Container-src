/*
 * kemen.h
 *
 *  Created on: Dec 8, 2014
 *      Author: root
 */

#ifndef KEMEN_H_
#define KEMEN_H_

#include <httpserver.hpp>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "service.h"

#include "RS232Puerto.h"
#include "MODBUSPuerto.h"
#include "IOEnlace.h"
#include "BSCLEnlace.h"
#include "Explorador.h"
#include "MODBUSExplorador.h"
#include "DBPesaje.h"
using namespace std;
using namespace container;
enum ESTADO {LOCK_ABIERTO, LOCK_CERRADO, PESADO, ATRAPADO, SUBIENDO, SOLTADO,ERROR,FIN };


#endif /* KEMEN_H_ */
