#include "httpservermethod.h"

int Httpservermethod::get_line(int client_sock, string& buf, int size)
{
	int count = 0;
	char ch = '\0';
	int len = 0;
	buf.clear();

	while (count < size - 1 && ch != '\n')
	{
		len = read(client_sock, &ch, 1);

		if (len == 1)
		{
			if (ch == '\r')
				continue;
			else if (ch == '\n')
			{
				buf.push_back('\0');
				break;
			}

			buf.push_back(ch);
			count++;
		}
		else if (len == -1)
		{
			code = 500;
			cout << stderr << "读取失败" << endl;
			count = -1;
			return count;
		}
		else
		{
			cout << stderr << "连接断开" << endl;
			count = -1;
			return count;
		}
	}
	buf.push_back('\0');
	return count;
}

Request Httpservermethod::do_http_Request(int sock,int &client_sock)
{
	struct sockaddr_in client;
	int len;
	char client_ip[CLIENT_IP_SIZE];
	socklen_t client_addr_len = sizeof(client);

	//*************************接受请求*****************************//
	client_sock = accept(sock, (struct sockaddr*)&client, &client_addr_len);

	if (client_sock == -1)
	{
		cout << stderr << "accept" << "error,reason:" << strerror(errno) << endl;
		close(sock);
		exit(1);
	}
	cout << "----------------------- 接受到的请求----------------------- " << endl;
	//IP和PORT
	Request request;
	request.setClientIP(inet_ntop(AF_INET, &client.sin_addr.s_addr, client_ip, sizeof(client_ip)));
	request.setClientPort(ntohs(client.sin_port));

	cout << "client ip: \t port :" << endl;
	cout << request.getClientIP() << " \t ";
	cout << request.getClientPort() << endl;

	string buf;
	string url;
	string urlvalue;
	string path;
	char method[METHOD_SIZE];

	//读取请求
	len = get_line(client_sock, buf, BUF_SIZE);
	int i = 0;
	int j = 0;
	if (len > 0)
	{
		cout << buf << endl;
		while (!isspace(buf[j]) && i < METHOD_SIZE - 1)
		{
			method[i] = buf[j];
			i++;
			j++;
		}

		method[i] = '\0';
		request.setMethod(method);
	}
	else if (len == 0)
	{
		code = 400;
		cout << "请求行为空行" << endl;
		return request;
	}
	else
	{
		cout << "读取出错" << endl;
		return request;
	}

	//获取url
	while (!isspace(buf[j++]));
	i = 0;
	while (!isspace(buf[j]) && i < URL_SIZE - 1)
	{
		url.push_back(buf[j]);
		i++;
		j++;
	}
	url.push_back('\0');
	request.setURL(url);
	//获取url中的值(urlvalue)和路径（path）
	bool isWH = false;
	i = 0;
	for (int inofurl = 0; inofurl < URL_SIZE - 1; inofurl++)
	{

		if (isWH)
		{
			urlvalue.push_back(url[inofurl]);
			i++;
			if (url[inofurl] == '\0')
				break;
		}		
		if (url[inofurl] == '\0')
			break;
		if (url[inofurl] == '?')
		{
			isWH = true;
			path.push_back('\0');
		}
		if (!isWH)
		{
			path.push_back(url[inofurl]);
		}
	}

	request.setURLValue(urlvalue);
	//******************处理url中的值*************************//
	string key;
	string value;
	i = 0;
	isWH = true;
	while (urlvalue.size() > 0 && urlvalue[i] == '\0')
	{
		if (urlvalue[i] == '&')
		{
			request.setValueElement(key, value);
			key.clear();
			value.clear();
			i++;
			isWH = true;
			continue;
		}
		if (urlvalue[i] == '=')
		{
			isWH = false;
			i++;
		}
		if (isWH)
			key.push_back(urlvalue[i]);
		if (!isWH)
			value.push_back(urlvalue[i]);
		i++;
	}
	//将剩下的表头存到hashmap
	request.setHeaderElement(key, value);
	//******************定位服务器本地html文件位置******************//
	string htmlfile = htmlpath;
	path = htmlfile.append(path);
	request.setPath(path);

	//继续读取并分析http头部
	do
	{
		len = get_line(client_sock, buf, BUF_SIZE);
		if (len == -1)
		{
			code = 400;
			cout << "请求出错" << endl;
			return request;
		}
		cout << buf << endl;
		key.clear();
		value.clear();
		isWH = false;
		i = 0;
		j = 0;
		for (int index = 0; index < BUF_SIZE - 1; index++)
		{
			
			if (isWH)
			{
				value.push_back(buf[index]);
				j++;
				if (buf[index] == '\0')
					break;
				continue;
			}
			if (buf[index] == '\0')
				break;
			if (buf[index] == ':')
			{
				isWH = true;
				key.push_back('\0');
			}
			if (!isWH)
			{
				key.push_back(buf[index]);
				i++;
			}
		}
		//将剩下的表头存到hashmap
		request.setHeaderElement(key, value);
	} while (len > 0);
	//返回处理后的请求
	return request;
}

Response Httpservermethod::do_http_Response(Request request)
{
	struct stat st;
	Response response;

	//判断路径是否存在
	int pathL = request.getPath().size();
	char* path = new char[pathL];
	request.getPath().copy(path, pathL, 0);
	path[pathL] = '\0';
	if (stat(path, &st) == -1)
	{
		cout << stderr << "stat" << path << "faild.reason:" << strerror(errno) << endl;
		code = 404;
		response.setCode(code);
		return response;
	}
	else
	{
		if (S_ISDIR(st.st_mode))
			strcat(path, "./index.html");
	}

	//提取文件Content-Type
	string key = "Content-Type";
	char contentType[64] = { 0 };
	bool ispoint = false;
	strcat(contentType, "text/");
	int i = 5;
	for (int j = 1; j < strlen(path); j++)
	{
		if (ispoint)
		{
			contentType[i] = path[j];
			i++;
		}
		if (path[j] == '.')
			ispoint = true;
	}
	contentType[i] = '\0';
	if (strncasecmp(contentType, "js", 3) == 0)
		strcpy(contentType, "javascript");
	response.setHeaderElement(key, string( contentType));

	int len = 0;
	FILE* resource = NULL;

	resource = fopen(path, "r");

	if (resource == NULL)
	{
		code = 404;
		response.setCode(code);
		return response;
	}

	//头部
	int fileid = 0;
	response.setHeaderElement("Connection", "Close");

	fileid = fileno(resource);

	if (fstat(fileid, &st) == -1)
	{
		cout << "服务器内部出错" << endl;
		code = 500;
		response.setCode(code);
		return response;
	}
	response.setHeaderElement("Content-length", to_string(st.st_size));


	//内容
	char ch = getc(resource);
	string body;
	while (!feof(resource))
	{
		body.push_back(ch);
		ch = getc(resource);
	}

	response.setBody(body);
	response.setCode(code);
	return response;
}

void Httpservermethod::sendhtml(int client_sock, Response response)
{
	cout << "-----------------------发送过去的回应-----------------------" << endl;

	//发送头部
	char header[2048] = { 0 };
	string tmp;
	tmp = to_string(response.getCode());
	strcat(header, HTTP_VERSION);
	strcat(header, " ");
	strcat(header, tmp.c_str());
	if (code == 200)
		strcat(header, " OK\r\n");
	strcat(header, " \r\n");

	map<string, string>::iterator it;
	map<string, string> HeaderMap = response.getHeader();
	for (it = HeaderMap.begin(); it != HeaderMap.end(); it++)
	{
		strcat(header, it->first.c_str());
		strcat(header, ": ");
		strcat(header, it->second.c_str());
		strcat(header, "\r\n");
	}
	strcat(header, "\r\n");

	cout << header << endl;
	send(client_sock, header, strlen(header), 0);

	//发送内容
	int len = write(client_sock, response.getBody().c_str(), response.getBody().size());
	if (len == -1)
		cout << "发送内容错误" << endl;
	code = 200;
}
