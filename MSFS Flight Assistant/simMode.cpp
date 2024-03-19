#include <iostream>
#include <Windows.h>
#include "dataStruct.h"
#include "serverConnection.h"
#include "flags.h"
#include "flightChecklist.h"
#include "flightMode.h"
#include "landingMode.h"
#include "calcStruct.h"

simData currentData;

void initSimMode() {
	while (getFlightChecklist() == false) {
		requestDataFromServer();
		calculateAirspace(currentData);
		calculateFlightPath(currentData);

		currentData = getSimData();

		std::cout

			<< "\rAltitude: " << currentData.altitude
			<< " \n- Latitude: " << currentData.latitude
			<< " \n- Longitude: " << currentData.longitude
			<< " \n- Bearing to Waypoint: " << currentData.bearing
			<< " \n- Heading: " << currentData.heading
			<< " \n- Speed(knots): " << currentData.speed
			<< " \n- RPM: " << currentData.RPM
			<< " \n- Vertical Speed: " << currentData.verticalSpeed

			<< std::flush;
		Sleep(500);
		if (GetKeyState('C') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			increaseProgress();
			setFlightChecklistTrue();
		}
	}
	startChecklist();

	while (getLanding() == false) {
		requestDataFromServer();
		currentData = getSimData();
		calculateAirspace(currentData);
		calculateFlightPath(currentData);

		std::cout

			<< "\rAltitude: " << currentData.altitude
			<< " \n- Latitude: " << currentData.latitude
			<< " \n- Longitude: " << currentData.longitude
			<< " \n- Bearing to Waypoint: " << currentData.bearing
			<< " \n- Heading: " << currentData.heading
			<< " \n- Speed(knots): " << currentData.speed
			<< " \n- RPM: " << currentData.RPM
			<< " \n- Vertical Speed: " << currentData.verticalSpeed

			<< std::flush;
		Sleep(500);
		if (GetKeyState('L') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			setLandingTrue();
			increaseProgress();
		}
	}
	startLanding();
	setProgress(34);
	std::cout << "\n THANK YOU FOR USING OUR PILOT SUPPORT DEVICE" << std::endl;
	Sleep(20000);
}