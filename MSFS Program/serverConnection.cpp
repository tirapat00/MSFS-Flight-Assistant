#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "../MSFS Flight Assistant/dataStruct.h"

using namespace std;

SOCKET sock;

void connectToServer(){
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

void sendToServer(double altitude, double latitude, double longitude, int32_t heading,int32_t speed, int32_t verticalSpeed,int32_t RPM) {
	simData demoData;
	demoData.altitude = altitude;
	demoData.latitude = latitude;
	demoData.longitude = longitude;
	demoData.heading = heading;
	demoData.speed = speed;
	demoData.verticalSpeed = verticalSpeed;
	demoData.RPM = RPM;

	sendStruct packet;
	packet.data = demoData;

	send(sock, (const char*)&packet, sizeof(packet), 0);
}