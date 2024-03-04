#include"httpservermethod.h"



void printError(const char* errorNa, int sock)
{
	cout << stderr << errorNa << "error,reason:" << strerror(errno) << endl;
	close(sock);
	exit(1);
}

void httpserver(int sock)
{
	int client_sock;
	Httpservermethod httpservermethod;
	Request request = httpservermethod.do_http_Request(sock, client_sock);
	Response response = httpservermethod.do_http_Response(request);
	httpservermethod.sendhtml(client_sock, response);
	close(client_sock);
}

int main()
{
	//套接字
	int sock;
	int i;
	int ret;
	//创建标签
	struct sockaddr_in server_addr;

	//1.服务器创建套接字
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == -1)
		printError("create sock", sock);

	//2.清空标签，写上地址和端口号
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	//3.将套接字与IP和端口号绑定
	ret = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (ret == -1)
		printError("bind", sock);

	//4.开始监听
	ret = listen(sock, 128);

	if (ret == -1)
		printError("listen", sock);

	cout << "等待客户端的连接" << endl;

	while (true)
	{
		
		thread threadObj(httpserver,sock);
		threadObj.join();
	}
	return 0;
}