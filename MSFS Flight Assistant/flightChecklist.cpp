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
		if (checklistData.RPM >= 800 && checklistData.RPM <= 1200) {
			++engineWarmUpTimer;
			if (engineWarmUpTimer >= 10) {
				engineWarmUpSuccessful = true;
			}
			std::cout << "Hold RPM!\n" << checklistData.RPM << std::endl;
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
	bool brakeCheck = false;
	while (!brakeCheck) {
		requestDataFromServer();
		checklistData = getSimData();
		if (checklistData.speed == 0) {
			std::cout << "Gain Speed! \n" << std::endl;
			Sleep(2000);
		}
		else if (checklistData.speed > 0) {
			std::cout << "BRAKE!\n" << std::endl;
			int brakeCheckSpeed = checklistData.speed;
			Sleep(5000);
			requestDataFromServer();
			checklistData = getSimData();
			int brakeCheckSpeed2 = checklistData.speed;
			if (brakeCheckSpeed2 < brakeCheckSpeed) {
				brakeCheck = true;
			}
		}
	}
	Sleep(5000);
}

void preTakeoff() {
	std::cout
		<< "Parking Brake SET\n"
		<< "Seats, Belt, Harness CHECK SECURE\n"
		<< "Cabin Doors & Windows CLOSED & LOCKED\n"
		<< "Flight Controls FREE & CORRECT\n"
		<< "Fuel Selector BBOTH\n"
		<< "Elevator Trim SET for Takeoff\n"
		<< "Fuel Quantity CHECK\n"
		<< "Mixture RICH\n"
		<< "Throttle 1700RPM\n"
		<< std::endl;
		bool throttleCheck = false;
		while (!throttleCheck) {
			requestDataFromServer();
			checklistData = getSimData();
			if (checklistData.RPM > 1700 && checklistData.RPM < 1800) {
				throttleCheck = true;
			}
			else {
				std::cout << "Bring RPM between 1700 - 1800\n" << std::endl;
			}
		}
		std::cout
			<< "Engine Instruments & Ammeter CHECK\n"
			<< "Throttle Friction Lock ADJUST\n"
			<< "Flight Instruments CHECK & SET\n"
			<< "Radios SET\n"
			<< "Transponder ALTITUDE\n"
			<< "Wing Flaps SET for Takeoff\n"
			<< "Lights AS DESIRED\n"
			<< "Brakes RELEASE\n"
			<< std::endl;
}

void takeoff() {
	std::cout
		<< "Wing Flaps 0 Degrees\n"
		<< "Carburetor Heat COLD\n"
		<< std::endl;
	bool takeoff = false;
	while (!takeoff) {
		requestDataFromServer();
		checklistData = getSimData();
		if (checklistData.RPM < 2500 && checklistData.speed < 75 || checklistData.speed > 85) {
			std::cout
				<< "Throttle FULL OPEN\n"
				<< "Climb Speed 75-85 MPH\n"
				<< std::endl;
			Sleep(1000);
		} 
		else if (checklistData.RPM > 2500 && checklistData.speed > 75 && checklistData.altitude < 1000) {
			std::cout << "Hold Speed and RPM!\n" << std::endl;
			Sleep(1000);
		}
		else if (checklistData.altitude > 1000) {
			takeoff = true;
		}
	}
}

void climb() {
	bool climb = false;
	while (!climb) {
		requestDataFromServer();
		checklistData = getSimData();
		if (checklistData.speed < 80 && checklistData.altitude < 3000) {
			std::cout << "gain Speed!\n Gain Altitude\n" << std::endl;  
			Sleep(2000);
		}
		else if (checklistData.speed >= 80 && checklistData.speed <= 90 && checklistData.altitude < 3000) {
			std::cout << "Maintain Speed!\n Gain Altitude!\n" << std::endl;
			Sleep(2000);
		}
		else if (checklistData.speed > 90 && checklistData.altitude < 3000) {
			std::cout << "Decrease Speed!\n Gain Altitude!\n" << std::endl;
			Sleep(2000);
		}
		else if (checklistData.speed >= 80 && checklistData.speed <= 90 && checklistData.altitude >= 3000) {
			std::cout << "Maintain Speed!\n Cruising Altitude of 3000 Feet reached!\n" << std::endl;
			climb = true;
			Sleep(2000);
		}

	}
}

void cruse() {
	std::cout
		<< "Power 2200 - 2700 RPM\n"
		<< "Elevator ADJUST\n"
		<< "Mixture LEAN\n"
		<< std::endl;
	Sleep(10000);
}

void descent() {

}

void startTakeoff() {
	takeoff();
	climb();
	cruse();
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
	startTakeoff();
}

void startChecklist() {
	startPreFlightInspection();
}



