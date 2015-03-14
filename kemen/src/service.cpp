/*
     This file is part of libhttpserver
     Copyright (C) 2014 Sebastiano Merlino

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free Software
     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
     USA
*/


#include <string>
#include "../include/service.h"


bool verbose=true;
using namespace std;
using namespace std;
extern BSCLEnlace *bscl;
service_resource::service_resource()
{}

service_resource::~service_resource()
{}

void service_resource::render_GET(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render_GET()" << std::endl;
	map <string , string,arg_comparator> queryitems;

  if (verbose) std::cout << req;
  string response= "";
  string operation = req.get_arg("op");
  req.get_args(queryitems);

  //Tratamiento  de la query
  if (operation.compare("historico")==0)
  	this->getDBHistoricData(queryitems.find("startdate")->second,queryitems.find("enddate")->second,response);
  else if (operation.compare("max") == 0)
  	this->getDBMaxDayData(queryitems.find("startdate")->second,queryitems.find("enddate")->second,queryitems.find("count")->second,response);
  else if(operation.compare("ultimo") == 0)
  	this->getLastData(response);
  else if(operation.compare("ultimosdiez") == 0)
    	this->getLastTenData(response);
  else std::cout << "Operacion: " << req.get_arg("op") << " no localizada."<<"\n";

  *res = new http_response(http_response_builder(response, 200).string_response());
   if (verbose) std::cout << **res;
}



void service_resource::render_PUT(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render_PUT()" << std::endl;	

    if (verbose) std::cout << req;
    
	*res = new http_response(http_response_builder("PUT response", 200).string_response());

    if (verbose) std::cout << **res;
}


void service_resource::render_POST(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render_POST()" << std::endl;	

    if (verbose) std::cout << req;
    
	*res = new http_response(http_response_builder("POST response", 200).string_response());
    if (verbose) std::cout << **res;    
}
void service_resource::render(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render()" << std::endl;	

    if (verbose) std::cout << req;

	*res = new http_response(http_response_builder("generic response", 200).string_response());

    if (verbose) std::cout << **res;    
}


void service_resource::render_HEAD(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render_HEAD()" << std::endl;

    if (verbose) std::cout << req;
    
	*res = new http_response(http_response_builder("HEAD response", 200).string_response());

    if (verbose) std::cout << **res;    
}

void service_resource::render_OPTIONS(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render_OPTIONS()" << std::endl;

    if (verbose) std::cout << req;
    
	*res = new http_response(http_response_builder("OPTIONS response", 200).string_response());

    if (verbose) std::cout << **res;    
}

void service_resource::render_CONNECT(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render_CONNECT()" << std::endl;	

    if (verbose) std::cout << req;
    
	*res = new http_response(http_response_builder("CONNECT response", 200).string_response());

    if (verbose) std::cout << **res;    
}

void service_resource::render_DELETE(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render_DELETE()" << std::endl;	

    if (verbose) std::cout << req;
    
	*res = new http_response(http_response_builder("DELETE response", 200).string_response());

    if (verbose) std::cout << **res;    
}
/*
 * http://192.168.24.109:9898/service?op=max&startdate=2014-12-26&enddate=2014-12-27&count=limit
 */
void service_resource::getDBMaxDayData(string startdate, string enddate,string count,string &data)
{
	std::cout << "getDBMaxDayData today:" << startdate << " end " << enddate << " count " << count << std::endl;

	DBPesaje db("/home/batela/bascula/db/kemen.db");
	db.Open();
	db.ReadMaxDayData(startdate,enddate,count,data);
	std::cout << data;
	db.Close();
}
/**
 * http://192.168.24.109:9898/service?op=historico&startdate=2014-12-26&enddate=2014-12-27
 */
void service_resource::getDBHistoricData(string startdate, string enddate,string &data)
{
	std::cout << "getDBHistoricData start:" << startdate << " end " << enddate << std::endl;

	DBPesaje db("/home/batela/bascula/db/kemen.db");
	db.Open();
	db.ReadHistoricData(startdate,enddate,data);
	std::cout << data;
	db.Close();
}

/**
 * http://192.168.24.109:9898/service?op=ultimosdiez
 */
void service_resource::getLastTenData(string &data)
{
	std::cout << "getLastTenData start:" << std::endl;

	DBPesaje db("/home/batela/bascula/db/kemen.db");
	db.Open();
	db.ReadLastTenData(data);
	std::cout << data;
	db.Close();
}

void service_resource::getLastData(string &data)
{

	std::cout << "getLastData.... "<< std::endl;

	char raw[256];
	char now [20];
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime (now,20,"%F %T",timeinfo);
	char isValido = (bscl->getBSCL()->GetEstable()==true)?'V':'N';
	//sprintf(raw,"%d;%c;%c;%d;%s\n",1,isValido,bscl->getBSCL()->GetSigno(),bscl->getBSCL()->GetPeso(),now);
	sprintf(raw,"%d;%c;%c;%d;%s\n",1,isValido,bscl->getBSCL()->GetSigno(),bscl->getBSCL()->GetPeso(),now);
	data =  raw;
	std::cout << "enviado: " << data << std::endl;
}

/*
void usage()
{
    std::cout << "Usage:" << std::endl
              << "service [-p <port>][-s [-k <keyFileName>][-c <certFileName>]][-v]" << std::endl;
}
*/
