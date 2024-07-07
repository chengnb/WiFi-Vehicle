#ifndef TOOLS_H
#define TOOLS_H
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int newS(char* ip,int port);
int newC(char* ip,int port);
#endif
