#include <iostream>
#include <Windows.h>
#include <SimConnect.h>

bool checklistFlag = false;

void setChecklistFlagPositive() {
	checklistFlag = true;
	std::cout << "Checklist Flag set positive" << std::endl;
}

void setChecklistFlagNegative() {
	checklistFlag = false;
}

bool getChecklistFlag() {
	return checklistFlag;
}

bool flightFlag = false;

void setFlightFlagPositive() {
	flightFlag = true;
}

void setFlightFlagNegative() {
	flightFlag = false;
}

bool getFlightFlag() {
	return flightFlag;
}

bool landingFlag = false;

void setLandingFlagPositive() {
	landingFlag = true;
}

void setLandingFlagNegative() {
	landingFlag = false;
}

bool getLandingFlag() {
	return landingFlag;
}