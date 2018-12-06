#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#define BUF_SIZE 100
#include <opencv2/opencv.hpp>
#include <Winsock2.h>
class TCP_server{
	public:
		TCP_server(char *ip, int host_num);
		~TCP_server();
		void send_img(char *img, int width, int height, int channel);
		void send_start_msg();
		void sendall(char* str, int len); // ·¢ËÍËùÓĞ
		SOCKET fd, fd_client;
		virtual void run();
	private:
		struct sockaddr_in addr_server,addr_client;
		char buf[100];
};

#endif