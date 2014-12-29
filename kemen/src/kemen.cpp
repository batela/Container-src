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
    	std::cout << "Key: " << key << " Certificate: " << cert << std::endl;
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

int PesaContainer (MODBUSExplorador * exBascula){
	int res = 0;
	int contador = 0;
	((BSCLEnlace*)exBascula->getEnlace())->getBSCL()->SetEstable(false);
	while (((BSCLEnlace*)exBascula->getEnlace())->getBSCL()->GetEstable()==false){
		exBascula->Explora();
		sleep (1);
		if (contador++ >= 30) break;
	}
	if (((BSCLEnlace*)exBascula->getEnlace())->getBSCL()->GetEstable()==false) res = 1;
	return res;
}

int main(int argc, char **argv) {
	pthread_t idThLector;
	ESTADO estado;
	DBPesaje db("/home/batela/db/kemen.db");

	log4cpp::Category &log  = log4cpp::Category::getRoot();
	log4cpp::PropertyConfigurator::configure( Env::getInstance("/home/batela/cnf/saio.cnf")->GetValue("logproperties") );
	log.info("%s: %s",__FILE__, "Iniciando aplicacion de gruas...");

	/*
	int iret1 = pthread_create( &idThLector, NULL, httpservermanager, NULL);
	BSCLEnlace *bscl = new BSCLEnlace ();
	RS232Puerto *bsclPort = new RS232Puerto(Env::getInstance()->GetValue("puertobascula"), 9600);
	Explorador 	*exBSCL 		= new Explorador (bscl,bsclPort,true);
*/
	IOEnlace *io = new IOEnlace();
	MODBUSPuerto *moxaPort = new MODBUSPuerto(Env::getInstance()->GetValue("puertomoxa"), 9600);
	MODBUSExplorador *exGarra = new MODBUSExplorador (io,moxaPort);

	while (true){
		if (exGarra->Explora() == 0){
			log.info("%s: %s",__FILE__, "Entrando en bucle de garra");
			estado=LOCK_ABIERTO;
			for (int i= 0 ;i < 4 && estado !=FIN ; i++){
				int res = io->GetLocks()->GetLock(i+1);
				switch(estado){
					case LOCK_ABIERTO:
						if (res == 0)
							estado = FIN;
						else{
							log.info("%s: %s",__FILE__, "LOCKS CERRADO");
							estado = LOCK_CERRADO;
						}
					break;
					case LOCK_CERRADO:
						if (res == 0){
							log.info("%s: %s",__FILE__, "CONTAINER NO ATRAPADO..SALIENDO");
							estado = FIN;
						}
						else{
							log.info("%s: %s",__FILE__, "CONTAINER ATRAPADO");
							estado = ATRAPADO;
						}
					break;
					case ATRAPADO:
								/*
								if (PesaContainer(exBascula) == 0)
									estado = PESADO;
								else
									estado = ERROR;
								*/

							log.info("%s: %s",__FILE__, "CONTAINER PESADO");
							estado = PESADO;
					break;
					case PESADO:
							db.Open();
							db.InsertData(1,12.4);
							db.Close();
							estado = FIN;
					break;
					case ERROR:
						estado = FIN;
					break;
					case FIN:
						log.info("%s: %s",__FILE__, "Saliendo de bucle");
					break;
				}//swtich
			} //for
		}//if
		sleep (10);
	}
	return 0;
}
