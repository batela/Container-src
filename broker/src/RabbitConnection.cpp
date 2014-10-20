/*
 * RabbitConnection.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: root
 */

#include "../include/RabbitConnection.h"

namespace Container {

RabbitConnection::RabbitConnection(string host) {
	hostname = host;
	conn = amqp_new_connection();
	socket = amqp_tcp_socket_new(conn);

}

RabbitConnection::RabbitConnection() {
	hostname = "localhost";
}

RabbitConnection::~RabbitConnection() {
	// TODO Auto-generated destructor stub
}

/**
 * @return 0 if OK
 */
int RabbitConnection::initialize (){
	int status = amqp_socket_open(socket, hostname.data(), port);
	if (status) {
		return status;
	}

	status = errorHandler.handleError(amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest"),"login function");
	amqp_channel_open(conn, 1);
	status = errorHandler.handleError( amqp_get_rpc_reply(conn),"rpc_reply function");
	if (status) close();
	return status ;

}

void RabbitConnection::close (){
	///FIXME Sin implementar.
}

/**
 * @return 0 if OK
 */
int RabbitConnection::publicar (char message){
	int res = 1;
	amqp_bytes_t message_bytes;
	message_bytes.len = sizeof(message);
	message_bytes.bytes = message;
	if (AMQP_STATUS_OK==amqp_basic_publish(conn,1, amqp_cstring_bytes("a2pbeer.topic"),
	                                      amqp_cstring_bytes("HOLA.MUNDO"),
	                                      0,
	                                      0,
	                                      NULL,
	                                      message_bytes)) res = 0 ;

}
/**
 * @return 0 if OK
 */
int RabbitConnection::escuchar (char message){
	amqp_bytes_t  queuename ;
	amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1,amqp_empty_table);
	errorHandler.handleError(amqp_get_rpc_reply(conn), "Declaring queue");
	queuename = amqp_bytes_malloc_dup(r->queue);
	if (queuename.bytes == NULL) {
		fprintf(stderr, "Out of memory while copying queue name");
	  return 1;
	}

	amqp_queue_bind(conn, 1, queuename, amqp_cstring_bytes("a2pbeer.topic"), amqp_cstring_bytes("HOLA.MUNDO.SOY"),
	                    amqp_empty_table);
	errorHandler.handleError(amqp_get_rpc_reply(conn), "Binding queue");
	amqp_basic_consume(conn, 1, queuename, amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	return 0 ;

}
} /* namespace Container */
