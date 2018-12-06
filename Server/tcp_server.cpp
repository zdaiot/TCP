#include<iostream>
#include <Winsock2.h>
#include "tcp_server.h"
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#pragma comment(lib,"WS2_32")
using namespace std;

TCP_server::TCP_server(char *ip, int host_num){
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {
			WSACleanup( );
			return;
	}
	
	fd=socket(AF_INET,SOCK_STREAM,0); //´´½¨¼àÌýÌ×½Ó×Ö
	addr_server.sin_family=AF_INET;
	addr_server.sin_addr.S_un.S_addr=inet_addr(ip);
	addr_server.sin_port=htons(host_num);
	bind(fd,(sockaddr *)&addr_server,sizeof(addr_server));
	listen(fd,5);
	int len=sizeof(sockaddr);
	fd_client=accept(fd,(sockaddr *)&addr_client,&len);

}

void TCP_server::run(){
	while (1)
	{
		SOCKET tmp = fd_client; 
		int len=sizeof(sockaddr);
		fd_client=accept(fd,(sockaddr *)&addr_client,&len);
		closesocket(tmp);
		//send_data();
	}
}

void TCP_server::send_start_msg(){
	int b=1;
	send(fd_client, (const char*)&b, 4, 0);
}

void TCP_server::send_img(char *img, int width, int height, int channel=3){
	send(fd_client, (const char*)&width, 4, 0); //·¢ËÍÍ¼Æ¬¿í¶È
	send(fd_client, (const char*)&height, 4, 0);//·¢ËÍÍ¼Æ¬³¤¶È
	int len = width * height * channel;
	sendall(img, len); //·¢ËÍÍ¼Æ¬
}

void TCP_server::sendall(char* str, int len)
{
	while (len > 0)
	{
		if (len > BUF_SIZE)
		{
			if (send(fd_client, (const char*)str, BUF_SIZE, 0) == SOCKET_ERROR)
			{
				closesocket(fd_client);
			}
			else
				len -= BUF_SIZE;
			str += BUF_SIZE;

		}
		else
		{
			if (send(fd_client, (const char*)str, len, 0) == SOCKET_ERROR)
			{
				closesocket(fd_client);
			}
			else
				len -= len;
			str += BUF_SIZE;
		}
	}
}

TCP_server::~TCP_server(){
	closesocket(fd_client);
}