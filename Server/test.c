#include "serial.h"

#define devpath "/dev/ttyATH0"
int main(int argc,char *argv[]){

	int fd=serial_init(devpath);
	if(fd<0){
		perror("serial init:");
	}
	char a[]={(char)0xFF,(char)0x00,(char)0x00,(char)0x00,(char)0xFF};
	perror(a);
	serial_send_data(fd,a,sizeof(a));
}
