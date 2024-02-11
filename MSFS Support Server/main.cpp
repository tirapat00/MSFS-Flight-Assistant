#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "../MSFS Flight Assistant/dataStruct.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;


simData currentSimData;

DWORD WINAPI handleEvents(LPVOID lpParam) {
	cout << "Thread started" << endl;

	SOCKET currentClient = (SOCKET)lpParam;

	char buf[4096];

	char sendData[4096];

	while (true) {
		int bytesReceived = recv(currentClient, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cout << "Error in recv(). Quitting" << endl;
			return 0;
		}

		if (bytesReceived == 0)
		{
			cout << "Client disconnected " << endl;
			return 0;
		}
		decideStruct* determineStruct = (decideStruct*)&buf;

		cout << char(determineStruct->flag) << endl;

		if (determineStruct->flag == 0) {
			sendStruct* demoData = (sendStruct*)&buf;
			currentSimData = demoData->data;
			cout

				<< "\rAltitude: " << currentSimData.altitude
				<< " - Heading: " << currentSimData.heading
				<< " - Speed(knots): " << currentSimData.speed
				<< " - Vertical Speed: " << currentSimData.verticalSpeed

				<< std::flush;
		}

		else if (determineStruct->flag == 1) {
			send(currentClient, (const char*)&currentSimData, sizeof(currentSimData), 0);
		}
	}
}


int main()
{
	//master Socket
	SOCKET sock;

	//for multi Threading
	DWORD thread;

	// Initialze winsock
	WSADATA wsaData;
	sockaddr_in server;

	// start winsock
	int ret = WSAStartup(0x101, &wsaData);
	if (ret != 0) {
		return 0;
	}

	// Create a socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		return 0;
	}

	// Bind the ip address and port to a socket
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	server.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	if (bind(sock, (sockaddr*)&server, sizeof(server)) != 0) {
		return 0;
	}

	// Tell Winsock the socket is for listening 
	if (listen(sock, 5) != 0) {
		return 0;
	}
	cout << "listening to port" << endl;

	// Wait for a connection
	SOCKET clientSocket;
	sockaddr_in client;
	int clientSize = sizeof(client);


	// While loop: accept and echo message back to client

	while (true) {
		clientSocket = accept(sock, (struct sockaddr*)&client, &clientSize);
		cout << "Client connected!" << endl;

		CreateThread(NULL, 0, handleEvents, (LPVOID)clientSocket, 0, &thread);
	}

	// Close the socket
	closesocket(sock);

	// Cleanup winsock
	WSACleanup();

	return 0;
}
