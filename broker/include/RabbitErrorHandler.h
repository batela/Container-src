/*
 * RabbitErrorHandler.h
 *
 *  Created on: Oct 20, 2014
 *      Author: root
 */

#ifndef RABBITERRORHANDLER_H_
#define RABBITERRORHANDLER_H_
#include <string>
#include <stdio.h>
#include <librabbitmq/amqp_tcp_socket.h>
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>

using namespace std;
namespace container {

class RabbitErrorHandler {
public:
	RabbitErrorHandler();
	virtual ~RabbitErrorHandler();
	int handleError(amqp_rpc_reply_t x, char const *context);
};

} /* namespace Container */

#endif /* RABBITERRORHANDLER_H_ */
