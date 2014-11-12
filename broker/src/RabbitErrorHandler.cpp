/*
 * RabbitErrorHandler.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: root
 */

#include "../include/RabbitErrorHandler.h"

namespace container {

RabbitErrorHandler::RabbitErrorHandler() {


}

RabbitErrorHandler::~RabbitErrorHandler() {

}
/**
 * @return 0 if OK
 */
int RabbitErrorHandler::handleError(amqp_rpc_reply_t x, char const *context){
	int res = 0;
	switch (x.reply_type) {
	  case AMQP_RESPONSE_NORMAL:
	  return res;

	  case AMQP_RESPONSE_NONE:
	    fprintf(stderr, "%s: missing RPC reply type!\n", context);
	    break;

	  case AMQP_RESPONSE_LIBRARY_EXCEPTION:
	    fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
	    break;

	  case AMQP_RESPONSE_SERVER_EXCEPTION:
	    switch (x.reply.id) {
	    case AMQP_CONNECTION_CLOSE_METHOD: {
	      amqp_connection_close_t *m = (amqp_connection_close_t *) x.reply.decoded;
	      fprintf(stderr, "%s: server connection error %d, message: %.*s\n",
	              context,
	              m->reply_code,
	              (int) m->reply_text.len, (char *) m->reply_text.bytes);
	      break;
	    }
	    case AMQP_CHANNEL_CLOSE_METHOD: {
	      amqp_channel_close_t *m = (amqp_channel_close_t *) x.reply.decoded;
	      fprintf(stderr, "%s: server channel error %d, message: %.*s\n",
	              context,
	              m->reply_code,
	              (int) m->reply_text.len, (char *) m->reply_text.bytes);
	      break;
	    }
	    default:
	      fprintf(stderr, "%s: unknown server error, method id 0x%08X\n", context, x.reply.id);
	      break;
	    }
	    break;
	 }
	return 1;
	}

} /* namespace Container */
