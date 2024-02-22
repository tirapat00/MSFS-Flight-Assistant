#include <iostream>
#include <Windows.h>
#include "dataStruct.h"
#include "serverConnection.h"

simData currentData;

void initSimMode() {
	while (!GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
		requestDataFromServer();
		currentData = getSimData();

		std::cout

			<< "\rAltitude: " << currentData.altitude
			<< " - Latitude: " << currentData.latitude
			<< " - Longitude: " << currentData.longitude
			<< " - Heading: " << currentData.heading
			<< " - Speed(knots): " << currentData.speed
			<< " - Vertical Speed: " << currentData.verticalSpeed

			<< std::flush;
		Sleep(500);
	}

}