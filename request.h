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

    // 获取函数
    map<string, string> getHeader() const;

    // 设置函数
    void setHeader(const map<string, string>& header);

    // 添加或修改 header 中的一个元素
    void setHeaderElement(const string key, const string value);

    // 获取 header 中的一个元素
    string getHeaderElement(const string key) const;

    // 从 header 中删除一个元素
    void removeHeaderElement(const string key);

    // 获取函数
    map<string, string> getValue() const;

    // 设置函数
    void setValue(const map<string, string>& value);

    // 添加或修改 header 中的一个元素
    void setValueElement(const string key, const string value);

    // 获取 header 中的一个元素
    string getValueElement(const string key) const;

    // 从 header 中删除一个元素
    void removeValueElement(const string key);


};

