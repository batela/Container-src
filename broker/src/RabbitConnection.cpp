/*
 * RabbitConnection.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: root
 */

#include "../include/RabbitConnection.h"

namespace container {
extern log4cpp::Category &log;

void* lectorcolas (void * p){
	log.info("%s: %s",__FILE__, "Iniciando thread lector...");
	RabbitConnection * exp = (RabbitConnection*)p;
  while (1) {
  	int res = exp->leer (exp->rxBuffer,0);
  }
	log.info("%s: %s",__FILE__, "Terminando thread lector.");
	return NULL;
}

RabbitConnection::RabbitConnection(string host, string c, string t) {
	hostname 	= host;
	port = 5672;
	sigue			= true;
	conn 			= amqp_new_connection();
	socket 		= amqp_tcp_socket_new(conn);
	ultimaAct = time (NULL);
	canal = c;
	topic = t;

}

RabbitConnection::RabbitConnection(string c, string t) {
	hostname = "localhost";
	port = 5672;
	sigue= true;
	ultimaAct = time (NULL);
	canal = c;
	topic = t;
}

RabbitConnection::~RabbitConnection() {
	// TODO Auto-generated destructor stub
}

/**
 * @return 0 if OK
 */
int RabbitConnection::initialize (){
	log.info("%s: %s",__FILE__, "Comenzado funcion initialize..");
	conn = amqp_new_connection();
	socket = amqp_tcp_socket_new(conn);


	int status = amqp_socket_open(socket, hostname.data(), port);
	if (status) {
		return status;
	}

	status = errorHandler.handleError(amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest"),"login function");
	amqp_channel_open(conn, 1);
	status = errorHandler.handleError( amqp_get_rpc_reply(conn),"rpc_reply function");
	if (status) close();
	log.info("%s: %s",__FILE__, "Finalizando funcion initialize..");
	preparaEscuchar ();
	return status ;

}

void RabbitConnection::close (){
	///FIXME Sin implementar.
}

/**
 * @return 0 if OK
 */
int RabbitConnection::publicar (char* message){
	log.info("%s: %s",__FILE__, "Comenzado funcion publicar...");
	int res = 1;
	amqp_bytes_t message_bytes;
	message_bytes.len = strlen(message);
	message_bytes.bytes = (void*)message;
	if (AMQP_STATUS_OK==amqp_basic_publish(conn,1, amqp_cstring_bytes(canal.data()),
	                                      amqp_cstring_bytes(topic.data()),
	                                      0,
	                                      0,
	                                      NULL,
	                                      message_bytes)) res = 0 ;
	usleep(500);//Timer para pausar la publicación y dar tiempo
	log.debug ("%s: %s %d",__FILE__, "0=OK, Publicar termina con codigo: ", res);
	log.info("%s: %s",__FILE__, "Finalizando funcion publicar...");
	return res;
}
/**
 * @return 0 if OK
 */
int RabbitConnection::preparaEscuchar (){
	log.info("%s: %s",__FILE__, "Comenzado funcion escuchar...");
	amqp_bytes_t  queuename ;
	amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1,amqp_empty_table);
	int status = errorHandler.handleError(amqp_get_rpc_reply(conn), "Declaring queue");
	queuename = amqp_bytes_malloc_dup(r->queue);
	if (queuename.bytes == NULL) {
		log.error("%s: %s",__FILE__, "No se pudo inicializar la cola");
	  return status;
	}

	amqp_queue_bind(conn, 1, queuename, amqp_cstring_bytes(canal.data()), amqp_cstring_bytes(topic.data()),
	                    amqp_empty_table);
	status  = errorHandler.handleError(amqp_get_rpc_reply(conn), "Binding queue");
	amqp_basic_consume(conn, 1, queuename, amqp_empty_bytes, 0, 1, 0, amqp_empty_table);

	log.info("%s: %s",__FILE__, "Lanzando thread lector...");
	return status;
}

int RabbitConnection::escuchar (){
	return (pthread_create( &idThLector, NULL, lectorcolas, this)) ;
}
/**
 * @return -1 mensaje demasiado largo, 0 no mensaje  >0 OK
 */
int RabbitConnection::leer (char * mensaje, int to ){
	int result = 0;
	amqp_rpc_reply_t res;
	amqp_envelope_t envelope;

	amqp_maybe_release_buffers(conn);

	struct timeval timeout;
	timeout.tv_sec =  to;
	timeout.tv_usec =  0 ;
	if (to != 0)
		res = amqp_consume_message(conn, &envelope, &timeout, 0);
	else
		res = amqp_consume_message(conn, &envelope, NULL, 0);

	if (AMQP_RESPONSE_NORMAL != res.reply_type) {
		if (AMQP_RESPONSE_LIBRARY_EXCEPTION == res.reply_type) return 0;
		else return -1;
	}

	log.debug("Delivery %u, exchange %.*s routingkey %.*s\n",
			(unsigned) envelope.delivery_tag,
	    (int) envelope.exchange.len, (char *) envelope.exchange.bytes,
	    (int) envelope.routing_key.len, (char *) envelope.routing_key.bytes);
	if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG) {
		log.debug("Content-type: %.*s\n",
	  (int) envelope.message.properties.content_type.len,
	  (char *) envelope.message.properties.content_type.bytes);
	 }
	 if (envelope.message.body.len < 255){
		 memcpy (mensaje,envelope.message.body.bytes, envelope.message.body.len);
		 result = envelope.message.body.len;
	 }
	 else {
		 log.error("%s: %s %s",__FILE__, "Mensaje recibido por canal demasiado largo: " , envelope.message.body.bytes);
		 mensaje[0]=0;
		 result = -1;
	 }

	 amqp_destroy_envelope(&envelope);
	 setTime(time(NULL));
	 return result;
}
void RabbitConnection::setTime (uint64_t a){
	ultimaAct = a;
}
} /* namespace Container */
