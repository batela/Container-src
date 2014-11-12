/*
 * RabbitConnection.h
 *
 *  Created on: Oct 20, 2014
 *      Author: root
 */

#ifndef RABBITCONNECTION_H_
#define RABBITCONNECTION_H_

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <time.h>
#include <librabbitmq/amqp_tcp_socket.h>
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>
#include "../include/RabbitErrorHandler.h"

#include "Env.h"
using namespace std;
namespace container {

class RabbitConnection {
public:
	RabbitConnection(string host,string c, string t);
	RabbitConnection(string c, string t);
	virtual ~RabbitConnection();
	int initialize ();
	void close ();
	int publicar (char* message);
	int leer (char* message, int to);
	int escuchar ();
	friend void *lectorcolasww( void *ptr );
	void setTime (uint64_t a) ;
	uint64_t getUltimaAct (){return ultimaAct ;}

	amqp_connection_state_t conn 	= NULL;
	char rxBuffer[256];
private:
	bool sigue;
	int port; //port = 5672
	int status;
	string hostname;
	string canal;
	string topic;

	amqp_socket_t 			*socket 				= NULL;
	RabbitErrorHandler 	errorHandler;
	pthread_t 					idThLector;

	uint64_t 						ultimaAct;

	int preparaEscuchar ();
};

} /* namespace Container */

#endif /* RABBITCONNECTION_H_ */
