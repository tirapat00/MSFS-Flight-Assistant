#include <iostream>
#include "Windows.h"
#include "dataStruct.h"
#include "serverConnection.h"
#include "flags.h"
#include "calcStruct.h"

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
	setProgress(26);
}

void landing() {
		requestDataFromServer();
		landingData = getSimData();
		if (landingData.speed < 70) {
			std::cout << "\n Speed too low" << std::endl;
			setProgress(29);
		}
		else if (landingData.speed > 70 && landingData.speed < 80) {
			std::cout << "\n Hold speed" << std::endl;
			setProgress(28);
		}
		else if (landingData.speed > 80) {
			std::cout << "\n Speed too high" << std::endl;
			setProgress(30);
		}
		std::cout
			<< "\n Wing Flaps AS DESIRED"
			<< "\n Touchdown MAINS FIRST"
			<< "\n Landing Roll LOWER NOSE WHEEL GENTLY"
			<< "\n Braking MINIMUM REQUIRED"
			<< std::endl;
}

void afterLanding() {
	std::cout
		<< "\n Wing Flaps UP"
		<< "\n Carburetor Heat COLD"
		<< "\n Transponder STANDBY"
		<< "\n Lights AS REQUIRED"
		<< std::endl;
	setProgress(31);
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
		setProgress(33);
	}
	else if (landingData.RPM < 1000) {
		std::cout << "\n Hold RPM under 1000" << std::endl;
		setProgress(34);
	}
	std::cout
		<< "\n Mixture IDLE CUT-OFF"
		<< "\n Ignition Switch OFF"
		<< "\n Master Switch OFF"
		<< std::endl;
		requestDataFromServer();
		landingData = getSimData();
		if (landingData.RPM > 0) {
			std::cout << "Master Switch OFF" << std::endl;
			setProgress(35);
			Sleep(3000);
		}
		else if (landingData.RPM == 0) {
			setProgress(36);
	}
	std::cout
		<< "\n Control Lock INSTALL"
		<< "\n Hobbs&Tach RECORD"
		<< "\n Aircraft SECURE"
		<< std::endl;
}