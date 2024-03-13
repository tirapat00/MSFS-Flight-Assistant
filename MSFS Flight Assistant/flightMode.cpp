#include <iostream>
#include "Windows.h"
#include "dataStruct.h"
#include "serverConnection.h"
#include "flags.h"


simData flightData;
char airClass;


void calculateFlightPath(simData calcData) {

}

void calculateAirspace(simData calcData) {
	if (calcData.latitude < 29.0657 && calcData.latitude > 29.0010 && calcData.longitude > -81.0061 && calcData.longitude < 80.5329 && calcData.altitude < 1200) {
		airClass = 'D';
		std::cout << "\nCurrent Air Class " << airClass << std::endl;
	}
	else if (calcData.latitude < 29.0657 && calcData.latitude > 29.0010 && calcData.longitude > -81.0061 && calcData.longitude < 80.5329 && calcData.altitude > 1200) {
		airClass = 'C';
		std::cout << "\nCurrent Air Class " << airClass << std::endl;
	}
	else {
		airClass = 'E';
		std::cout << "\nCurrent Air Class " << airClass << std::endl;
	}
}
