#include "../include/kemen.h"
extern bool verbose;

BSCLEnlace *bscl = new BSCLEnlace (17,10);
log4cpp::Category &log  = log4cpp::Category::getRoot();
void * httpservermanager(void * p)
{
	uint16_t port=8080;
	BSCLEnlace *bscl = (BSCLEnlace *)p;
  const char *key	="key.pem";
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

int PesaContainer (Explorador * exBascula){
	int res = 0;
	int contador = 0;
	log.info("%s: %s",__FILE__, "Comienza pesaje");
	((BSCLEnlace*)exBascula->getEnlace())->getBSCL()->SetEstable(false);
	sleep (atoi(Env::getInstance()->GetValue("esperapeso").data()));
	while (((BSCLEnlace*)exBascula->getEnlace())->getBSCL()->GetEstable()==false){
		sleep (1);
		if (contador++ >= 10) break;
	}
	if (((BSCLEnlace*)exBascula->getEnlace())->getBSCL()->GetEstable()==false) res = 1;
	return res;
}

int main(int argc, char **argv) {

	pthread_t idThLector;

	log4cpp::PropertyConfigurator::configure( Env::getInstance("/home/batela/bascula/cnf/bascula.cnf")->GetValue("logproperties") );

	ESTADO estado;
	DBPesaje db("/home/batela/bascula/db/kemen.db");
	log.info("%s: %s",__FILE__, "Iniciando aplicacion de gruas...");

	bscl->Configure(Env::getInstance()->GetValue("pesajescorrectos"), Env::getInstance()->GetValue("margenpesajes"));

	Env::getInstance()->GetValue("puertobascula");
  //baudrate,char_size,parity,stopbits
	int baudios 		= atoi(Env::getInstance()->GetValue("baudiosbascula").data());
	int bitsdatos 	= atoi(Env::getInstance()->GetValue("bitsbascula").data());
	int bitsparada 	= atoi(Env::getInstance()->GetValue("bitsparadabascula").data());
	RS232Puerto *bsclPort = new RS232Puerto(Env::getInstance()->GetValue("puertobascula"), baudios,bitsdatos,0,bitsparada);
	Explorador 	*exBSCL		= new Explorador (bscl,bsclPort,true);

	//Configuramos el lecto IO
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = atoi(Env::getInstance()->GetValue("ioperiod").data()) * 1000000L;

	int isCarro = 0;
	int isPalpa = 0;
	int isTwisl = 0;
	int isSubir = 0;
	int ioCarro  = atoi(Env::getInstance()->GetValue("iocarroenvia").data()); //restamos 1 para referencia en 0
	int ioPalpa  = atoi(Env::getInstance()->GetValue("iopalpadores").data());
	int ioTwisl  = atoi(Env::getInstance()->GetValue("iotwislock").data());
	int ioSubir  = atoi(Env::getInstance()->GetValue("iomandosubir").data());
	IOEnlace *io = new IOEnlace();
	MODBUSPuerto *moxaPort = new MODBUSPuerto(Env::getInstance()->GetValue("puertomoxa"), 9600);
	MODBUSExplorador *exGarra = new MODBUSExplorador (io,moxaPort);
	bool pesajeHecho = false ;

	//Finalmente lanzamos el thread http
	int iret1 = pthread_create( &idThLector, NULL, httpservermanager,NULL);
	estado = ESPERA_CARRO_ENVIA ;
	while (true){
		log.debug("%s: %s",__FILE__, "Lanzando lectura de módulo IO");
		if (exGarra->Explora() == 0){
			isCarro = io->GetLocks()->GetLock(ioCarro);
			isPalpa = io->GetLocks()->GetLock(ioPalpa);
			isTwisl = io->GetLocks()->GetLock(ioTwisl);
			isSubir = io->GetLocks()->GetLock(ioSubir);
			log.info("%s: %s: %d-%d-%d-%d",__FILE__, "Leido: ", isCarro, isPalpa,isTwisl,isSubir);

			switch (estado){
				case ESPERA_CARRO_ENVIA:
					log.info("%s: %s",__FILE__, "Proceso de pesaje en: ESPERA_CARRO_VIA");

					if (isCarro && isPalpa && isTwisl) estado = ESPERA_PALPADORES_NO_APOYO;
					else estado = ESPERA_CARRO_ENVIA;
					pesajeHecho = false;
				break;
				case ESPERA_PALPADORES_NO_APOYO:
					log.info("%s: %s",__FILE__, "Proceso de pesaje en: ESPERA_PALPADORES_NO_APOYO");

					if (isCarro && !isPalpa && isTwisl && isSubir && !pesajeHecho){
						if (PesaContainer(exBSCL) == 0){
							db.Open();
							db.InsertData(1,bscl->getBSCL()->GetPeso());
							db.Close();
							pesajeHecho = true;
							estado = ESPERA_SOLTAR;

							log.info("%s: %s",__FILE__, "Proceso de pesaje en: Pesaje Hecho");
						}
						else estado = ESPERA_CARRO_ENVIA;
					}
					else if (!isTwisl) estado = ESPERA_CARRO_ENVIA;
					else estado = ESPERA_PALPADORES_NO_APOYO;
				break;
				case ESPERA_SOLTAR:
					log.info("%s: %s",__FILE__, "Proceso de pesaje en: ESPERA_SOLTAR");

					if (!isTwisl) estado = ESPERA_CARRO_ENVIA;
					else estado = ESPERA_SOLTAR;
				break;
				default:
					estado = ESPERA_CARRO_ENVIA;
				break;
			}
		}
		nanosleep(&tim , &tim2);
	}
	return 0;
}
