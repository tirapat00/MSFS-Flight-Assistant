#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "calcStruct.h"
#include <vector>
#include "flightChecklist.h"
#include "landingMode.h"
#include "flightMode.h"
#include "flags.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

//Start thread with this task for every client
DWORD WINAPI commWithPi(LPVOID lpParam) {
	cout << "Thread started" << endl;

	SOCKET currentClient = (SOCKET)lpParam;

	// create the buffer with space for the data
	const unsigned int MAX_BUF_LENGTH = 4096;
	vector<char> buffer(MAX_BUF_LENGTH);
	string rcv;

	char sendData[4096];

	while (true) {

		int bytesReceived = 0;
			bytesReceived = recv(currentClient, &buffer[0], buffer.size(), 0);
			// append string from buffer.
			if (bytesReceived == -1) {
				// error 
			}
			else {
				rcv.append(buffer.cbegin(), buffer.cend());
			}
		// At this point we have the available data (which may not be a complete
		// application level message). 

			int programProgress = stoi(rcv);

			switch (programProgress) {
			case '0' :
				startScreen();
				break;
			case '1' :
				cabin();
				break;
			case '2':
				rightWing();
				break;
			case '3':
				nose();
				break;
			case '4':
				leftWing();
				break;
			case '5':
				preStartEngine();
				break;
			case '6':
				startEngine();
				break;
			case '9':
				taxi();
				break;
			case '11':
				preTakeoff();
				break;
			case '15':
				takeoff();
				break;
			case '19':
				climb();
				break;
			case '24':
				cruse();
				break;
			case '25':
				flightMode();
				break;
			case '26':
				beforeLanding();
				break;
			case '27':
				landing();
				break;
			case '31':
				afterLanding();
				break;
			case '32':
				shutdown();
				break;
			case '37':
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