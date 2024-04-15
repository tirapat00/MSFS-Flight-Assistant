#include <iostream>
#include <Windows.h>
#include "dataStruct.h"
#include "serverConnection.h"
#include "calcStruct.h"
#include "flightMode.h"

simData checklistData;

void startScreen() {
	requestDataFromServer();
	checklistData = getSimData();
	calculateAirspace(checklistData);
	calculateFlightPath(checklistData);

	std::cout

		<< "\rAltitude: " << checklistData.altitude
		<< " \n- Latitude: " << checklistData.latitude
		<< " \n- Longitude: " << checklistData.longitude
		<< " \n- Bearing to Waypoint: " << checklistData.bearing
		<< " \n- Heading: " << checklistData.heading
		<< " \n- Speed(knots): " << checklistData.speed
		<< " \n- RPM: " << checklistData.RPM
		<< " \n- Vertical Speed: " << checklistData.verticalSpeed

		<< std::flush;
	setProgress(0);
}

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
	setProgress(1);
}

void tailSection() {
	std::cout
		<< "Tail Tie-Down/Rudder Gust Lock REMOVE\n"
		<< "Elevator and Rudder CHECK FREEDOM & SECURE\n"
		<< "Nav. Lights UNBROKEN\n"

		<< std::endl;

	setProgress(2);
}

void rightWing() {
	std::cout << "right Wing CHECK\n" << std::endl;
	setProgress(3);
}

void nose() {
	std::cout << "nose CHECK\n" << std::endl;
	setProgress(4);
}

void leftWing() {
	std::cout << "left Wing CHECK\n" << std::endl;
	setProgress(5);
}

void preStartEngine() {
	std::cout << "preStart Engine CHECK\n" << std::endl;
	setProgress(6);
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
		requestDataFromServer();
		checklistData = getSimData();
		if (checklistData.RPM >= 800 && checklistData.RPM <= 1200) {
			std::cout << "Hold RPM!\n" << checklistData.RPM << std::endl;
			setProgress(10);
			
		}
		else if (checklistData.RPM < 800) {
			std::cout << "Engine RPM too low must be between 800-1200!\n" << std::endl;
			setProgress(9);
			
		}
		else if (checklistData.RPM > 1200) {
			std::cout << "Engine RPM too high must be between 800-1200!\n" << std::endl;
			setProgress(8);		
		}
	std::cout
		<< "Fuel Pump OFF\n"
		<< "Mixture LEAN FOR TAXI\n"
		<< std::endl;

}

void taxi() {
		requestDataFromServer();
		checklistData = getSimData();
		if (checklistData.speed == 0) {
			std::cout << "Gain Speed! Speed: \n" <<checklistData.speed << std::endl;
			setProgress(12);
			
		}
		else if (checklistData.speed > 0) {
			std::cout << "BRAKE!\n" << std::endl;
			requestDataFromServer();
			checklistData = getSimData();
			//double brakeCheckSpeed = checklistData.speed;
			//std::cout << "Requested Data Speed: \n" << brakeCheckSpeed << std::endl;
			//Sleep(6000);
			//std::cout << "BRAKE checked!\n" << std::endl;
			//requestDataFromServer();
			//checklistData = getSimData();
			//double brakeCheckSpeed2 = checklistData.speed;
			//std::cout << "BRAKE check speed comparison! Speed 1 : " << brakeCheckSpeed << "Speed 2 : " << brakeCheckSpeed2 << std::endl;
			//if (brakeCheckSpeed2 < brakeCheckSpeed) {
			//	std::cout << "BRAKE check speed comparison! Speed 1 : " << brakeCheckSpeed << "Speed 2 : " << brakeCheckSpeed2 << std::endl;
			//	setProgress(13);
			//}
			setProgress(13);
		}
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
			requestDataFromServer();
			checklistData = getSimData();
			if (checklistData.RPM > 1700 && checklistData.RPM < 1800) {
				setProgress(17);
			}
			else if (checklistData.RPM < 1700){
				std::cout << "Bring RPM between 1700 - 1800\n" << std::endl;
				setProgress(16);
			}
			else if (checklistData.RPM > 1800) {
				setProgress(15);
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
		requestDataFromServer();
		checklistData = getSimData();
		if (checklistData.RPM < 2500 && checklistData.speed < 75) {
			std::cout
				<< "Throttle FULL OPEN\n"
				<< "Climb Speed 75-85 MPH\n"
				<< std::endl;
			setProgress(20);
		} 
		else if (checklistData.RPM > 2500 && checklistData.speed > 75 && checklistData.altitude < 1000) {
			std::cout << "Hold Speed and RPM!\n" << std::endl;
			setProgress(21);
		}
		else if (checklistData.RPM < 2500 && checklistData.speed > 85) {
			std::cout
				<< "Throttle FULL OPEN\n"
				<< "Climb Speed 75-85 MPH\n"
				<< std::endl;
			setProgress(19);
		}
}

void climb() {
		requestDataFromServer();
		checklistData = getSimData();
		if (checklistData.speed < 80 && checklistData.altitude < 3000) {
			std::cout << "gain Speed!\n Gain Altitude\n" << std::endl;  
			setProgress(24);
		}
		else if (checklistData.speed >= 80 && checklistData.speed <= 90 && checklistData.altitude < 3000) {
			std::cout << "Maintain Speed!\n Gain Altitude!\n" << std::endl;
			setProgress(23);
		}
		else if (checklistData.speed > 90 && checklistData.altitude < 3000) {
			std::cout << "Decrease Speed!\n Gain Altitude!\n" << std::endl;
			setProgress(25);
		}
		else if (checklistData.speed > 95 && checklistData.altitude < 3000) {
			std::cout << "Decrease Speed!\n Gain Altitude!\n" << std::endl;
			setProgress(26);
		}
		else if (checklistData.speed >= 80 && checklistData.speed <= 90 && checklistData.altitude >= 3000) {
			std::cout << "Maintain Speed!\n Cruising Altitude of 3000 Feet reached!\n" << std::endl;
			setProgress(27);
		}
}

void cruse() {
	std::cout
		<< "Power 2200 - 2700 RPM\n"
		<< "Elevator ADJUST\n"
		<< "Mixture LEAN\n"
		<< std::endl;
	requestDataFromServer();
	simData cruiseData = getSimData();
	calculateAirspace(cruiseData);
	if (getAirclass() == 'C') {
		setProgress(29);
	}
	else if (getAirclass() == 'D')
	{
		setProgress(30);
	}
	else if (getAirclass() == 'E')
	{
		setProgress(31);
	}
	
}



