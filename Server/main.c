#include "tools.h"
#include "serial.h"

#define devpath "/dev/ttyATH0"
int main(int argc,char *argv[]){
	if(argc<3)
	{
		printf("请输入ip和port\n");
		return -1;
	}
	int fd=serial_init(devpath);
	if(fd<0){
		perror("serial init:");
	}
	int socket_fd = newS(argv[1],atoi(argv[2]));
	if(socket_fd == -1)
		return -1;	
	unsigned char buf[256];
	int res;
	//接收连接，得到一个新的套接字
	struct sockaddr_in client_addr;
	while(1){
		bzero(&client_addr,sizeof(client_addr));
		int len=sizeof(client_addr);
		int client_fd=accept(socket_fd,(struct sockaddr*)&client_addr,&len);
		if(client_fd<0)
		{
			perror("accept error");
			return -1;
		}
		printf("accept ok! [user:%s:%d]\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_port);
		//收发消息
		while(1)
		{
			res=read(client_fd,buf,sizeof(buf));
			if(res<0)
			{
				perror("recv error");
				return -1;
			}else if(res == 0){
				char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
				serial_send_data(fd,a,sizeof(a));
				break;		
			}else{
				if(res == 5)
					printf("recv data[%d]:%X,%X,%X,%X,%X\n",res,buf[0],buf[1],buf[2],buf[3],buf[4]);
				serial_send_data(fd,buf,res);
			}
			res=0;
		}
	}
	//断开连接
	close(socket_fd);
	return 0;
}
