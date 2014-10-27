/*
 * RabbitConnection.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: root
 */

#include "../include/RabbitConnection.h"

namespace Container {

void* lector (void * p){
	RabbitConnection * exp = (RabbitConnection*)p;
	while (true){
		amqp_envelope_t envelope;
		amqp_frame_t frame;
		amqp_maybe_release_buffers(exp->conn);
		amqp_rpc_reply_t ret = amqp_consume_message(exp->conn, &envelope, NULL, 0);
		if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
		      if (AMQP_RESPONSE_LIBRARY_EXCEPTION == ret.reply_type &&   AMQP_STATUS_UNEXPECTED_STATE == ret.library_error) {
		        if (AMQP_STATUS_OK != amqp_simple_wait_frame(exp->conn, &frame)) {
		        }

		        if (AMQP_FRAME_METHOD == frame.frame_type) {
		          switch (frame.payload.method.id) {
		            case AMQP_BASIC_ACK_METHOD:
		              /* if we've turned publisher confirms on, and we've published a message
		               * here is a message being confirmed
		               */

		              break;
		            case AMQP_BASIC_RETURN_METHOD:
		              /* if a published message couldn't be routed and the mandatory flag was set
		               * this is what would be returned. The message then needs to be read.
		               */
		              {
		                amqp_message_t message;
		                ret = amqp_read_message(exp->conn, frame.channel, &message, 0);
		                if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
		                }

		                amqp_destroy_message(&message);
		              }

		              break;

		            case AMQP_CHANNEL_CLOSE_METHOD:
		              /* a channel.close method happens when a channel exception occurs, this
		               * can happen by publishing to an exchange that doesn't exist for example
		               *
		               * In this case you would need to open another channel redeclare any queues
		               * that were declared auto-delete, and restart any consumers that were attached
		               * to the previous channel
		               */
		              break;

		            case AMQP_CONNECTION_CLOSE_METHOD:
		              /* a connection.close method happens when a connection exception occurs,
		               * this can happen by trying to use a channel that isn't open for example.
		               *
		               * In this case the whole connection must be restarted.
		               */
		            	 break;

		            default:
		              fprintf(stderr ,"An unexpected method was received %d\n", frame.payload.method.id);
		              break;
		          }
		        }
		      }

		    } else {
		      amqp_destroy_envelope(&envelope);
		    }
	}
	printf ("Salimos");
}

RabbitConnection::RabbitConnection(string host) {
	hostname = host;
	sigue= true;
	conn = amqp_new_connection();
	socket = amqp_tcp_socket_new(conn);

}

RabbitConnection::RabbitConnection() {
	hostname = "localhost";
	sigue= true;
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

	return (pthread_create( &idThLector, NULL, lector, this)) ;

}

} /* namespace Container */
