#include <iostream>


bool flightCheckList = false;
bool landing = false;


bool getFlightChecklist() {
	return flightCheckList;
}

void setFlightChecklistTrue() {
	flightCheckList = true;
}

bool getLanding() {
	return landing;
}

void setLandingTrue() {
	landing = true;
}