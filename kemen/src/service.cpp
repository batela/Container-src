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


#include "../include/service.h"
#include <string>
bool verbose=true;
using namespace std;

service_resource::service_resource()
{}

service_resource::~service_resource()
{}

void service_resource::render_GET(const http_request &req, http_response** res)
{
	std::cout << "service_resource::render_GET()" << std::endl;

  if (verbose) std::cout << req;
  string response;
  std::cout << "query is:" << req.get_arg("op") <<"\n";
  this->getDDData(response);
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
void service_resource::getDDData(string &data)
{
	DBPesaje db("/home/batela/db/kemen.db");
	db.Open();
	db.ReadHistoricData(data);
	std::cout << data;
	db.Close();
}
/*
void usage()
{
    std::cout << "Usage:" << std::endl
              << "service [-p <port>][-s [-k <keyFileName>][-c <certFileName>]][-v]" << std::endl;
}
*/
