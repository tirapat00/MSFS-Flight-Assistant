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
	while (getFlagFinish) {
		requestDataFromServer();

		currentData = getSimData();

		std::cout

			<< "\nAltitude: " << currentData.altitude
			<< " \n- Latitude: " << currentData.latitude
			<< " \n- Longitude: " << currentData.longitude
			<< " \n- Bearing to Waypoint: " << currentData.bearing
			<< " \n- Heading: " << currentData.heading
			<< " \n- Speed(knots): " << currentData.speed
			<< " \n- RPM: " << currentData.RPM
			<< " \n- Vertical Speed: " << currentData.verticalSpeed

			<< std::flush;
		calculateAirspace(currentData);
		calculateFlightPath(currentData);
		Sleep(1000);
	}
	std::cout << "\n THANK YOU FOR USING OUR PILOT SUPPORT DEVICE" << std::endl;
	Sleep(20000);
}