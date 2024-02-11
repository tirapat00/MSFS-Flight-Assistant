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
			<< " - Heading: " << currentData.heading
			<< " - Speed(knots): " << currentData.speed
			<< " - Vertical Speed: " << currentData.verticalSpeed

			<< std::flush;
		Sleep(500);
	}
}