
///////////////////////////////////////клиент 

#include "pch.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#pragma warning(disable: 4996)
#include <opencv2/opencv.hpp>
#include <opencv/cv.hpp>

#include <opencv2/highgui.hpp>
#include <stdlib.h>

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;


#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";



	DWORD dwBytesWritten;
	TCHAR stdPath[30] = TEXT("client.png");

	HANDLE hFile; hFile = CreateFile(stdPath,
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);




	int size_t;

	recv(Connection, (char*)&size_t, sizeof(int), NULL);
	char *bufer = new char[size_t];
	
	int nbytes = recv(Connection, bufer, size_t, NULL);
	if (nbytes == 0)
	{
		std::cout << "Disconnected.\n";

	}
	if (nbytes < 0)
	{
		std::cout << "Error: " << WSAGetLastError() << std::endl;
	}
	if (nbytes==size_t)
	{
		std::cout << "Ok\n ";
	}

	WriteFile(hFile, bufer, nbytes, &dwBytesWritten, NULL);

	delete[] bufer;
    CloseHandle(hFile);
	Mat image = imread("client.png");

	// Check for failure
	if (image.empty())
	{
		std::cout << "Could not open or find the image\n";
		return -1;
	}

	String windowName = "CAMERA";  //Name of the window

	namedWindow(windowName);  // Create a window

	imshow(windowName, image); // Show our image inside the created window.
	waitKey(0);

	return 0;
}