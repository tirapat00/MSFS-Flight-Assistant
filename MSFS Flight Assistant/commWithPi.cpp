#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "calcStruct.h"
#include <vector>
#include "flightChecklist.h"
#include "landingMode.h"
#include "flightMode.h"
#include "flags.h"
#include "convertToString.h"

#pragma comment (lib, "ws2_32.lib")
#define DEFAULT_BUFLEN 512

using namespace std;

//Start thread with this task for every client
DWORD WINAPI commWithPi(LPVOID lpParam) {
	cout << "Thread started" << endl;

	SOCKET currentClient = (SOCKET)lpParam;

	// create the buffer with space for the data
	char recvbuf[DEFAULT_BUFLEN];

	char sendData[4096];
	string rcv;

	while (true) {

		int bytesReceived = 0;
		int programProgress;
			bytesReceived = recv(currentClient, recvbuf, DEFAULT_BUFLEN, 0);
			// append string from buffer.

		// At this point we have the available data (which may not be a complete
		// application level message). 
			rcv = convertToString(recvbuf, sizeof(recvbuf));
			try {
				programProgress = stoi(rcv);
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what() << "\n";
			}


			switch (programProgress) {
			case 0 :
				startScreen();
				break;
			case 1 :
				cabin();
				break;
			case 2 :
				tailSection();
				break;
			case 3:
				rightWing();
				break;
			case 4:
				nose();
				break;
			case 5:
				leftWing();
				break;
			case 6:
				preStartEngine();
				break;
			case 7:
				startEngine();
				break;
			case 11:
				taxi();
				break;
			case 14:
				preTakeoff();
				break;
			case 18:
				takeoff();
				break;
			case 22:
				climb();
				break;
			case 28:
				cruse();
				break;
			case 29:
				flightMode();
				break;
			case 30:
				beforeLanding();
				break;
			case 31:
				landing();
				break;
			case 35:
				afterLanding();
				break;
			case 36:
				shutdown();
				break;
			case 41:
				setFlagFinishTrue();
				break;
			default:
				std::cout << "Number not known" << std::endl;
			}


		int currentSystemStep = getProgress();
		std::string dataToSend = std::to_string(currentSystemStep);

		send(currentClient, dataToSend.c_str(), sizeof(currentSystemStep), 0);
		Sleep(1000);
	}
}


DWORD WINAPI startPiServer(LPVOID lpParam) {

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
	server.sin_port = htons(55000);
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

		CreateThread(NULL, 0, commWithPi, (LPVOID)clientSocket, 0, &thread);
	}

	// Close the socket
	closesocket(sock);

	// Cleanup winsock
	WSACleanup();

	return 0;
}