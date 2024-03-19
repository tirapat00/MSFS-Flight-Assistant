#pragma once
#include <iostream>
#include <Windows.h>

struct simData {
	double altitude;
	double latitude;
	double longitude;
	double bearing;
	double heading;
	double speed;
	double RPM;
	double verticalSpeed;

};

struct sendStruct {
	const char flag = 0;
	simData data;
};

struct requestStruct {
	const char flag = 1;
};

struct decideStruct {
	char flag;
};