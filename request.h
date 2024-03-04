#pragma once
#include"inchand.h"

class Request
{
private:
    char client_ip[CLIENT_IP_SIZE] = { 0 };
	int client_port;
    string url;
    char method[METHOD_SIZE] = { 0 };
    string url_value;
    map<string, string> value;
    string path;
    map<string, string> header;
public:
    Request();
    // Getters
    const char* getClientIP();
    int getClientPort();
    const string getURL();
    const char* getMethod();
    const string getURLValue();
    const string getPath();

    // Setters
    void setClientIP(const char* ip);
    void setClientPort(int port);
    void setURL(string url);
    void setMethod(char* method);
    void setURLValue(string url_value);
    void setPath(string path);

    void setURLFromConstCharArray(const char* urlCharArray);
    void setURLValueFromConstCharArray(const char* urlValueCharArray);
    void setPathFromConstCharArray(const char* pathCharArray);

    void setURLFromCharArray(char* urlCharArray);
    void setURLValueFromCharArray(char* urlValueCharArray);
    void setPathFromCharArray(char* pathCharArray);

    // ��ȡ����
    map<string, string> getHeader() const;

    // ���ú���
    void setHeader(const map<string, string>& header);

    // ��ӻ��޸� header �е�һ��Ԫ��
    void setHeaderElement(const string key, const string value);

    // ��ȡ header �е�һ��Ԫ��
    string getHeaderElement(const string key) const;

    // �� header ��ɾ��һ��Ԫ��
    void removeHeaderElement(const string key);

    // ��ȡ����
    map<string, string> getValue() const;

    // ���ú���
    void setValue(const map<string, string>& value);

    // ��ӻ��޸� header �е�һ��Ԫ��
    void setValueElement(const string key, const string value);

    // ��ȡ header �е�һ��Ԫ��
    string getValueElement(const string key) const;

    // �� header ��ɾ��һ��Ԫ��
    void removeValueElement(const string key);


};

