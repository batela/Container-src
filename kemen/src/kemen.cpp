#include "../include/kemen.h"
extern bool verbose;

void * httpservermanager(void * p)
{
	uint16_t port=8080;
	int c;
  const char *key="key.pem";
  const char *cert="cert.pem";
  bool secure=false;
	port=9898;
	std::cout << "Using port " << port << std::endl;
    if (secure) {
            std::cout << "Key: " << key << " Certificate: " << cert
                      << std::endl;
    }

    //
    // Use builder to define webserver configuration options
    //
    create_webserver cw = create_webserver(port).max_threads(5);

    if (secure) {
        cw.use_ssl().https_mem_key(key).https_mem_cert(cert);
    }

    //

    // Create webserver using the configured options
    //
	webserver ws = cw;

    //
    // Create and register service resource available at /service
    //
	service_resource res;
	ws.register_resource("/service",&res,true);

    //
    // Start and block the webserver
    //
	ws.start(true);

	return 0;
}


int main(int argc, char **argv) {
	pthread_t idThLector;
	int iret1 = pthread_create( &idThLector, NULL, httpservermanager, NULL);
	while (true){
		sleep (10);
	}
	return 0;
}
