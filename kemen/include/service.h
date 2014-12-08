#ifndef HTTPSERVICE_H_
#define HTTPSERVICE_H_

#include <httpserver.hpp>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include "DBPesaje.h"
using namespace std;
using namespace httpserver;
using namespace container;
class service_resource: public http_resource<service_resource> {
public:
	service_resource();

	~service_resource();

	void render_GET(const http_request &req, http_response** res);

	void render_PUT(const http_request &req, http_response** res);

	void render_POST(const http_request &req, http_response** res);

	void render(const http_request &req, http_response** res);

	void render_HEAD(const http_request &req, http_response** res);

	void render_OPTIONS(const http_request &req, http_response** res);

	void render_CONNECT(const http_request &req, http_response** res);

	void render_DELETE(const http_request &req, http_response** res);
	void getDDData(string &data);
private:


};

#endif /* X86MONITOR_H_ */
