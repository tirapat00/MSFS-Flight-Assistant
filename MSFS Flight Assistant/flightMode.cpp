#include <iostream>
#include "Windows.h"
#include "dataStruct.h"
#include "serverConnection.h"
#include "flags.h"


simData flightData;


void calculateFlightPath(simData calcData) {

}

void calculateAirspace(simData calcData) {
	if (calcData.latitude )
}

void startFlightMode() {
	while (getExitFlight() == false) {
		requestDataFromServer();
		flightData = getSimData();
		calculateAirspace(flightData);
		calculateFlightPath(flightData);

	}
}
