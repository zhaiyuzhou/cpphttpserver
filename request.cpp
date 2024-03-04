#include "request.h"

Request::Request()
{
    client_port = 0;
}

// Getters

const char* Request::getClientIP() { return client_ip; }

int Request::getClientPort() { return client_port; }

const string Request::getURL() { return url; }

const char* Request::getMethod() { return method; }

const string Request::getURLValue() { return url_value; }

const string Request::getPath() { return path; }

// Setters

void Request::setClientIP(const char* ip) { strncpy(client_ip, ip, CLIENT_IP_SIZE); }

void Request::setClientPort(int port) { client_port = port; }

void Request::setURL(string url) { this->url = url; }

void Request::setMethod(char* method) { strncpy(this->method, method, METHOD_SIZE); }

void Request::setURLValue(string url_value) { this->url_value = url_value; }

void Request::setPath(string path) { this->path = path; }

void Request::setURLFromConstCharArray(const char* urlCharArray) {
    this->url = string(urlCharArray);
}

void Request::setURLValueFromConstCharArray(const char* urlValueCharArray) {
    this->url_value = string(urlValueCharArray);
}

void Request::setPathFromConstCharArray(const char* pathCharArray) {
    this->path = string(pathCharArray);
}

void Request::setURLFromCharArray(char* urlCharArray) {
    this->url = string(urlCharArray);
}

void Request::setURLValueFromCharArray(char* urlValueCharArray) {
    this->url_value = string(urlValueCharArray);
}

void Request::setPathFromCharArray(char* pathCharArray) {
    this->path = string(pathCharArray);
}

// 获取函数

map<string, string> Request::getHeader() const {
    return this->header;
}

// 设置函数

void Request::setHeader(const map<string, string>& header) {
    this->header = header;
}

// 添加或修改 header 中的一个元素

void Request::setHeaderElement(const string key, const string value) {
    this->header[key] = value;
}

// 获取 header 中的一个元素

string Request::getHeaderElement(const string key) const {
    auto it = this->header.find(key);
    if (it != this->header.end()) {
        return it->second;
    }
    else {
        return "";
    }
}

// 从 header 中删除一个元素

void Request::removeHeaderElement(const string key) {
    this->header.erase(key);
}

map<string, string> Request::getValue() const
{
    return this->value;
}

void Request::setValue(const map<string, string>& value)
{
    this->value = value;
}

void Request::setValueElement(const string key, const string value)
{
    this->value[key] = value;
}

string Request::getValueElement(const string key) const
{
    auto it = this->value.find(key);
    if (it != this->value.end()) {
        return it->second;
    }
    else {
        return "";
    }
}

void Request::removeValueElement(const string key)
{
    this->value.erase(key);
}
