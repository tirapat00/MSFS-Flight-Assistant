#include <iostream>
#include <Windows.h>
#include "dataStruct.h"
#include "serverConnection.h"

simData checklistData;

void cabin() {
	std :: cout

		<< "Certificates / Documents ARROW\n"
		<< "Parking Brake SET\n"
		<< "Control Wheel Lock REMOVE\n"
		<< "Igntion Switch OFF\n"
		<< "Master Switch ON\n"
		<< "Fuel Quntity Indicators CHECK QUANTITY\n"
		<< "Anti-Collision/Strobe Lights CHECK OPERATION\n"
		<< "Flaps DOWN FOR INSPECTION\n"
		<< "Master Switch OFF\n"
		<< "Fuel Selector BOTH\n"
		<< "Baggage Door CHECK SECURE\n"

		<< std :: endl;
	Sleep(5000);
}

void tailSection() {
	std::cout
		<< "Tail Tie-Down/Rudder Gust Lock REMOVE\n"
		<< "Elevator and Rudder CHECK FREEDOM & SECURE\n"
		<< "Nav. Lights UNBROKEN\n"

		<< std::endl;

	Sleep(5000);
}

void rightWing() {
	std::cout << "right Wing CHECK\n" << std::endl;
	Sleep(5000);
}

void nose() {
	std::cout << "nose CHECK\n" << std::endl;
	Sleep(5000);
}

void leftWing() {
	std::cout << "left Wing CHECK\n" << std::endl;
	Sleep(5000);
}

void preStartEngine() {
	std::cout << "preStart Engine CHECK\n" << std::endl;
	Sleep(5000);
}

void startEngine() {
	std::cout
		<< "Mixture RICH\n"
		<< "Carburetor Heat COLD\n"
		<< "Prime AS REQUIRED\n"
		<< "Primer IN&LOCKED\n"
		<< "Master Switch ON\n"
		<< "Anti-collision/Strobe Lights CHECK OPERATION\n"
		<< "Propeller Area CLEAR\n"
		<< "Ignition Switch START\n"
		<< "Oil Pressure CHECK\n"
		<< "Engine Warm-Up THROTTLE 800-1200 RPM\n"

		<< std::endl;
	bool engineWarmUpSuccessful = false;
	int engineWarmUpTimer = 0;
	while (!engineWarmUpSuccessful) {
		requestDataFromServer();
		checklistData = getSimData();
		if (checklistData.RPM >= 800 || checklistData.RPM <= 1200) {
			++engineWarmUpTimer;
			if (engineWarmUpTimer >= 10) {
				engineWarmUpSuccessful = true;
			}
			Sleep(5000);
		}
		else if (checklistData.RPM < 800) {
			engineWarmUpTimer = 0;
			std::cout << "Engine RPM too low must be between 800-1200!\n" << std::endl;
			Sleep(5000);
		}
		else if (checklistData.RPM > 1200) {
			engineWarmUpTimer = 0;
			std::cout << "Engine RPM too high must be between 800-1200!\n" << std::endl;
			Sleep(5000);
		}
	}
	std::cout
		<< "Fuel Pump OFF\n"
		<< "Mixture LEAN FOR TAXI\n"
		<< std::endl;

}

void taxi() {
	std::cout << "taxi CHECK\n" << std::endl;
	Sleep(5000);
}

void preTakeoff() {

}

void takeoff() {

}

void climb() {

}

void cruse() {

}

void descent() {

}

void startTakeoff() {

}

void startPreFlightInspection() {
	cabin();
	tailSection();
	rightWing();
	nose();
	leftWing();
	preStartEngine();
	startEngine();
	taxi();
}

void startChecklist() {
	startPreFlightInspection();
}



