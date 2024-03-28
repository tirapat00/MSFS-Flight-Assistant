#include <iostream>
#include "Windows.h"
#include "dataStruct.h"
#include "serverConnection.h"
#include "flags.h"
#include "calcStruct.h"

char airClass;


void calculateFlightPath(simData calcData) {
	double correction = calcData.bearing - calcData.heading;
	std::cout << "\nCorrect Flight Path for " << correction << " degrees" << std::endl;
}

void calculateAirspace(simData calcData) {
	if (calcData.latitude < 29.0657 && calcData.latitude > 29.0010 && calcData.longitude > -81.0061 && calcData.longitude < -80.5329 && calcData.altitude < 1200) {
		airClass = 'D';
		std::cout << "\nCurrent Air Class " << airClass << std::endl;
	}
	else if (calcData.latitude < 29.0657 && calcData.latitude > 29.0010 && calcData.longitude > -81.0061 && calcData.longitude < -80.5329 && calcData.altitude > 1200) {
		airClass = 'C';
		std::cout << "\nCurrent Air Class " << airClass << std::endl;
	}
	else if (calcData.latitude < 29.2096 && calcData.latitude > 29.0100 && calcData.longitude > -81.1478 && calcData.longitude < -80.5204 && calcData.altitude < 4000) {
		airClass = 'C';
		std::cout << "\nCurrent Air Class " << airClass << std::endl;
	}
	else if (calcData.latitude < 29.3218 && calcData.latitude > 29.2371 && calcData.longitude > -81.1734 && calcData.longitude < -81.0770 && calcData.altitude < 1500) {
		airClass = 'D';
		std::cout << "\nCurrent Air Class " << airClass << std::endl;
	}
	else {
		airClass = 'E';
		std::cout << "\nCurrent Air Class " << airClass << std::endl;
	}
}

void flightMode() {
	requestDataFromServer();
	simData calcData = getSimData();
	calculateAirspace(calcData);
	calculateFlightPath(calcData);

	std::cout

		<< "\rAltitude: " << calcData.altitude
		<< " \n- Latitude: " << calcData.latitude
		<< " \n- Longitude: " << calcData.longitude
		<< " \n- Bearing to Waypoint: " << calcData.bearing
		<< " \n- Heading: " << calcData.heading
		<< " \n- Speed(knots): " << calcData.speed
		<< " \n- RPM: " << calcData.RPM
		<< " \n- Vertical Speed: " << calcData.verticalSpeed

		<< std::flush;
	setProgress(25);
}
