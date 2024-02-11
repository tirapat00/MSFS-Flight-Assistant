#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include "dataStruct.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
SOCKET sock;
char buf[4096];
simData currentSimData;

void connectToServer() {
	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	std::cout << "Connected to Server!" << std::endl;
}


void requestDataFromServer() {
	requestStruct packet;
	send(sock, (const char*)&packet, sizeof(packet), 0);
	recv(sock, buf, 4096, 0);
	simData* demoData = (simData*)&buf;
	currentSimData = *demoData;
}

simData getSimData() {
	return currentSimData;
}