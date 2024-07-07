#include "tools.h"

int newS(char* ip,int port){
	//创建一个socket()套接字
	int socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if(socket_fd<0)
	{
		perror("socket error");
		return -1;
	}
	printf("socket ok!\n");
	//绑定本机的ip和port
	//定义一个地址结构体变量，保存服务器自己的ip和port
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=inet_addr(ip);

	int res=bind(socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(res<0)
	{
		perror("bind error");
		return -1;
	}
	printf("bind ok!\n");
	//监听是否有人来连接
	res=listen(socket_fd,5);
	if(res<0)
	{
		perror("listen error");
		return -1;
	}
	printf("listen ok!\n");
	return socket_fd;
}
//Creat Client
int newC(char* ip,int port){
	//创建一个socket()套接字
	int socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if(socket_fd<0)
	{
		perror("socket error");
		return -1;
	}
	printf("socket ok!\n");
	//绑定本机的ip和port
	//定义一个地址结构体变量，保存服务器自己的ip和port
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family=AF_INET;
	client_addr.sin_port=htons(port);
	client_addr.sin_addr.s_addr=inet_addr(ip);

	int res=connect(socket_fd,(struct sockaddr*)&client_addr,sizeof(client_addr));
	if(res<0)
	{
		perror("connect error");
		return -1;
	}
	printf("connect ok!\n");
	return socket_fd;
}
