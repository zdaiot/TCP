#include <iostream>
#include <stdio.h>
#include "tcp_client.h"
//#include <opencv2/opencv.hpp>
using namespace std;
//using namespace cv;

int main(int argc, char *argv[])
{
	TCP_client *client = new TCP_client("192.168.43.40", 6666);
	//printf("Conected TCP!\n");
	while(true)
	{
		client->recv_data();

		printf("recv!\n");

		// Mat img;
		// //if (client->channel == 1)
		// //	img = Mat(client->width, client->height, CV_8UC1, (uchar*)client->info);//CV_8UC1
		// //else
		// img = Mat(client->height, client->width, CV_8UC3, (uchar*)client->info);

		// imshow("≤‚ ‘≥Ã–Ú",img);
		// waitKey(0);
	}

	return 0;
}
