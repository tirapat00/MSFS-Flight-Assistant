#include <iostream>
#include <Windows.h>
#include "dataStruct.h"
#include "serverConnection.h"
#include "flags.h"
#include "flightChecklist.h"

simData currentData;

void initSimMode() {
	while (getFlightChecklist() == false) {
		requestDataFromServer();
		currentData = getSimData();

		std::cout

			<< "\rAltitude: \n" << currentData.altitude
			<< " - Latitude: \n" << currentData.latitude
			<< " - Longitude: \n" << currentData.longitude
			<< " - Heading: \n" << currentData.heading
			<< " - Speed(knots): \n" << currentData.speed
			<< " - RPM: \n" << currentData.RPM
			<< " - Vertical Speed: \n" << currentData.verticalSpeed

			<< std::flush;
		Sleep(500);
		if (GetKeyState('C') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			setFlightChecklistTrue();
		}
	}
	startChecklist();

}