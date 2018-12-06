#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#define BUF_SIZE 100

#include<iostream>
#include <Winsock2.h>
#pragma comment(lib,"WS2_32")

class TCP_client{
public:
	TCP_client(char* , int);
	~TCP_client();
	void recv_data();
	void TCP_client::recvall(char*, int len);
	void reconnect();
	int width;
	int height;
	int channel;
	char* info;
	int len;
	char* ip;
	int host_num;
private:
	SOCKET fd;
	struct sockaddr_in addr;
	
};

#endif

