#pragma once
#include"request.h"
#include"response.h"
class Httpservermethod
{
	int code = 200;
	char httpserver[4];
public:
	int get_line(int client_sock, string& buf, int size);
	Request do_http_Request(int sock,int &client_sock);
	Response do_http_Response(Request request);
	void sendhtml(int client_sock, Response response);
};

