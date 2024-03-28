#include <iostream>


bool flightCheckList = false;
bool landing = false;
bool flight = false;
bool exitFlight = false;
bool flagFinish = false;


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

bool getFlight() {
	return flight;
}

void setFlightTrue(){
	flight = true;
}

bool getExitFlight() {
	return exitFlight;
}

void setExitFlightTrue() {
	exitFlight = true;
}

bool getFlagFinish() {
	return flagFinish;
}

void setFlagFinishTrue() {
	flagFinish = true;
}