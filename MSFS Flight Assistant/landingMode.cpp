#include <iostream>
#include "Windows.h"
#include "dataStruct.h"
#include "serverConnection.h"
#include "flags.h"

simData landingData;

void beforeLanding() {
	requestDataFromServer();
	landingData = getSimData();
	std::cout
		<< "\n Seats,Belts,Harnesses SECURE"
		<< "\n Fuel Selector BOTH"
		<< "\n Mixture RICH"
		<< "\n Carburetor Heat APPLY FULL HEAT"
		<< "\n Wing Flaps AS DESIRED"
		<< std::endl;
	requestDataFromServer();
	landingData = getSimData();
	if (landingData.speed > 75) {
		std::cout << "\n Flaps UP until Speed round about 70 MPH" << std::endl;
	}
	else if (landingData.speed < 75) {
		std::cout << "\n Flaps DOWN" << std::endl;
	}
	Sleep(5000);
}

void landing() {
	bool landing = false;
	while (!landing) {
		requestDataFromServer();
		landingData = getSimData();
		if (landingData.speed < 70) {
			std::cout << "\n Bring Speed between 70-80 MPH" << std::endl;
		}
		else if (landingData.speed > 80) {
			std::cout << "\n Bring Speed between 70-80 MPH" << std::endl;
		}
		else if (landingData.speed > 70 && landingData.speed < 80) {
			std::cout << "\n Hold speed" << std::endl;
		}
		std::cout
			<< "\n Wing Flaps AS DESIRED"
			<< "\n Touchdown MAINS FIRST"
			<< "\n Landing Roll LOWER NOSE WHEEL GENTLY"
			<< "\n Braking MINIMUM REQUIRED"
			<< std::endl;
		if (landingData.altitude < 13) {
			landing = true;
		}
		Sleep(1000);
	}
}

void afterLanding() {
	std::cout
		<< "\n Wing Flaps UP"
		<< "\n Carburetor Heat COLD"
		<< "\n Transponder STANDBY"
		<< "\n Lights AS REQUIRED"
		<< std::endl;
}

void shutdown() {
	requestDataFromServer();
	landingData = getSimData();
	std::cout
		<< "\n Parking Brake SET"
		<< "\n Radios & Electrical Equipment & Lights OFF"
		<< std::endl;
	if (landingData.RPM > 1000) {
		std::cout << "\n Bring RPM under 1000 RPM" << std::endl;
		Sleep(5000);
	}
	else if (landingData.RPM < 1000) {
		std::cout << "\n Hold RPM under 1000" << std::endl;
		Sleep(5000);
	}
	std::cout
		<< "\n Mixture IDLE CUT-OFF"
		<< "\n Ignition Switch OFF"
		<< "\n Master Switch OFF"
		<< std::endl;
	Sleep(5000);
	bool master = false;
	while (!master) {
		requestDataFromServer();
		landingData = getSimData();
		if (landingData.RPM > 0) {
			std::cout << "Master Switch OFF" << std::endl;
			Sleep(3000);
		}
		else if (landingData.RPM == 0) {
			master = true;
		}
	}
	std::cout
		<< "\n Control Lock INSTALL"
		<< "\n Hobbs&Tach RECORD"
		<< "\n Aircraft SECURE"
		<< std::endl;
}

void startLanding(){
	void beforeLanding();
	void landing();
	void afterLanding();
	void shutdown();
}