#include <iostream>
#include <Windows.h>
#include "dataStruct.h"
#include "serverConnection.h"

simData currentData;

void initSimMode() {
	while (true) {
		requestDataFromServer();
		currentData = getSimData();

		std::cout

			<< "\rAltitude: " << currentData.altitude
			<< " - Latitude: " << currentData.latitude
			<< " - Longitude: " << currentData.longitude
			<< " - Heading: " << currentData.heading
			<< " - Speed(knots): " << currentData.speed
			<< " - RPM: " << currentData.RPM
			<< " - Vertical Speed: " << currentData.verticalSpeed

			<< std::flush;
		Sleep(500);
	}

}