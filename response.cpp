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

// 获取函数

map<string, string> Response::getHeader() const {
    return this->header;
}

// 设置函数

void Response::setHeader(const map<string, string>& header) {
    this->header = header;
}

// 添加或修改 header 中的一个元素

void Response::setHeaderElement(const string key, const string value) {
    this->header[key] = value;
}

// 获取 header 中的一个元素

string Response::getHeaderElement(const string key) const {
    auto it = this->header.find(key);
    if (it != this->header.end()) {
        return it->second;
    }
    else {
        return "";
    }
}

// 从 header 中删除一个元素

void Response::removeHeaderElement(const string key) {
    this->header.erase(key);
}
