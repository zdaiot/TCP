#include<opencv2\opencv.hpp>
#include "tcp_server.h"
#include <windows.h>
using namespace cv;
using namespace std;  

int main()

{
	TCP_server *server = new TCP_server("127.0.0.1", 6666);

	Mat img = imread("1.png"); //读取图片

	while(1)
	{
		//首先发送一个标志位
		server->send_start_msg();
		printf("cols:%d\nrows:%d\nchannels:%d\n", img.rows, img.cols, img.channels());
		cout << "type:" << img.type() << endl;

		/*
		char c[4];
		memcpy(c, &img.cols, 4);
		send(server->fd_client, (const char*)c, sizeof(c), 0);

		char b[4];
		memcpy(b, &img.rows, 4);
		send(server->fd_client, (const char*)b, sizeof(b), 0);
		*/
	
		/*
		send(server->fd_client, (const char*)&img.rows, 4, 0);
		Sleep(1000);
		send(server->fd_client, (const char*)&img.cols, 4, 0);
		Sleep(1000);
		*/

		/*
		char a[8];
		memcpy(a, &img.rows, 4);
		memcpy(a + 4, &img.cols, 4);
		send(server->fd_client, (const char*)a, sizeof(a), 0);
		printf("%d\n%d", img.rows , img.cols);
		*/

		//使用函数
		server->send_img((char*)img.data, img.cols, img.rows, 3);
	}

}


