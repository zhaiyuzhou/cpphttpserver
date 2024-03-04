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
};

