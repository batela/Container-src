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

#include <librabbitmq/amqp_tcp_socket.h>
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>
#include "../include/RabbitErrorHandler.h"
using namespace std;
namespace Container {

class RabbitConnection {
public:
	RabbitConnection(string host);
	RabbitConnection();
	virtual ~RabbitConnection();
	int initialize ();
	void close ();
	int publicar (char message);
	int escuchar (char message);
private:
	string hostname;
	int port, status; //port = 5672
	int rate_limit;
	int message_count;
	amqp_connection_state_t conn 	= NULL;
	amqp_socket_t *socket 				= NULL;
	RabbitErrorHandler errorHandler;


};

} /* namespace Container */

#endif /* RABBITCONNECTION_H_ */
