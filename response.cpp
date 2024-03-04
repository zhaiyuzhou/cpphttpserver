#include "response.h"

Response::Response()
{
	code = 200;
	header["Server"] = SERVER_NAME;
    header["Content-Type"] = CONTENTTYPE_DEFAULT;
    header["Connection"] = "Close";
}

int Response::getCode()
{
	return code;
}

map<string, string> Response::getHeader()
{
	return header;
}

string Response::getBody()
{
	return body;
}

void Response::setCode(int code)
{
	this->code = code;
}

void Response::setBody(string body)
{
	this->body = body;
}

void Response::setBodyFromCharArray(const char* body)
{
	this->body = string(body);
}

// ��ȡ����

map<string, string> Response::getHeader() const {
    return this->header;
}

// ���ú���

void Response::setHeader(const map<string, string>& header) {
    this->header = header;
}

// ��ӻ��޸� header �е�һ��Ԫ��

void Response::setHeaderElement(const string key, const string value) {
    this->header[key] = value;
}

// ��ȡ header �е�һ��Ԫ��

string Response::getHeaderElement(const string key) const {
    auto it = this->header.find(key);
    if (it != this->header.end()) {
        return it->second;
    }
    else {
        return "";
    }
}

// �� header ��ɾ��һ��Ԫ��

void Response::removeHeaderElement(const string key) {
    this->header.erase(key);
}
