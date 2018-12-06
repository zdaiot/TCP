#include <iostream>
#include "tcp_client.h"
// #include <Winsock2.h>
// #pragma comment(lib,"WS2_32")

using namespace std;


TCP_client::TCP_client(char* ip_, int host_num_){
	//变量初始化
	int err;
	width = 1;
	height = 1;
	ip = ip_;
	host_num = host_num_;

	/*
	//wsastartup主要就是进行相应的socket库绑定
	WORD wVersionRequested;
	WSADATA wsaData;
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
	*/

	fd = socket(AF_INET,SOCK_STREAM,0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip); //server IP 
	addr.sin_port = htons(host_num); //server Port
	int ret = connect(fd,( sockaddr *)&addr,sizeof(addr));
	if (ret!=-1)
		printf("Connected!\n");
}

void TCP_client::recv_data(){
	int crash;
	while(1){
		int ret = recv(fd, (char*)&crash, 4, 0);
		if(ret == -1 || ret == 0)
			reconnect();
		else
			break;
	}

	//接收方法一
	/*
	char b[4];
	recv(fd, (char *)b, 4, 0);
	memcpy(&width, b, 4);

	char a[4];
	recv(fd, (char *)a, 4, 0);
	memcpy(&height, a, 4);
	*/

	//接收方法二
	/*
	char a[8];
	recv(fd, (char *)a, sizeof(a), 0);
	memcpy(&width, a, 4);
	memcpy(&height, a+4, 4);
	*/

	recv(fd, (char *)&width, 4, 0);
	recv(fd, (char *)&height, 4, 0);
	printf("clos:%d\nrows:%d\n", width, height);

	len = width*height*3;
	info = (char*)malloc(sizeof(char)*len);
	recvall(info, len);
}
void TCP_client::recvall(char* pPixel, int len){
	char revData[BUF_SIZE];
	int ret = 1;
	while (len>0)
	{
		if (len > BUF_SIZE)
		{
			ret = recv(fd, revData, BUF_SIZE, 0);
			//printf("ret is %d\n", len);
			if ( ret> 0)//recv函数返回其实际copy的字节数。如果recv在copy时出错，那么它返回SOCKET_ERROR；如果recv函数在等待协议接收数据时网络中断了，那么它返回0。
			{
				memcpy(pPixel, revData, BUF_SIZE);
				pPixel += ret;
				len -= ret;
			}
		}
		else
		{
			ret = recv(fd, revData, len, 0);
			//printf("ret is %d\n", ret);
			if ( ret> 0)//recv函数返回其实际copy的字节数。如果recv在copy时出错，那么它返回SOCKET_ERROR；如果recv函数在等待协议接收数据时网络中断了，那么它返回0。
			{
				memcpy(pPixel, revData, len);
				pPixel += ret;
				len -= ret;
			}
		}
	}
}
TCP_client::~TCP_client(){
	close(fd);
}

void TCP_client::reconnect(){
	printf("Reconnect\n");
	close(fd);
	fd = socket(AF_INET,SOCK_STREAM,0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(host_num);
	int ret  = connect(fd,( sockaddr *)&addr,sizeof(addr));
	if (ret != -1){
		printf("Reconnected!~~~\n");
		//socket_tcp_alive(fd);
	}
	else{
		printf("Connect fail.\n");
		sleep(2);
	}
}
