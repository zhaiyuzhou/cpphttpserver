#pragma once
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
#include<map>
#include <string.h>
#include <thread>

#define SERVER_PORT 80
#define CLIENT_IP_SIZE 64
#define BUF_SIZE 1024
#define METHOD_SIZE 64
#define URL_SIZE 256
#define debug true
#define PATH_SIZE 512
#define SERVER_NAME "Centos8 Server"
#define CONTENTTYPE_DEFAULT "text/plain"
#define HTTP_VERSION "HTTP/1.1"

using namespace std;

const string htmlpath = "./htmlfile";

//200 404 500
