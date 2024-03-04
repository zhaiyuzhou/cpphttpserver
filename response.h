#pragma once
#include"request.h"
class Response
{
private:
	int code;
	map<string, string> header;
	string body;
public:
	Response();

	int getCode();
	map<string,string> getHeader();
	string getBody();

	void setCode(int code);
	void setBody(string body);
	void setBodyFromCharArray(const char* body);

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
};

