#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#define BUF_SIZE 100

// #include <iostream>
// #include <Winsock2.h>
// #pragma comment(lib,"WS2_32")
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>

class TCP_client{
public:
	TCP_client(char* , int);
	~TCP_client();
	void recv_data();
	void recvall(char*, int len);
	void reconnect();
	int width;
	int height;
	int channel;
	char* info;
	int len;
	char* ip;
	int host_num;
private:
	int fd;
	struct sockaddr_in addr;
};

#endif

