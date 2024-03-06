#pragma once
#include <iostream>
#include <Windows.h>

struct simData {
	double altitude;
	double latitude;
	double longitude;
	int32_t heading;
	int32_t speed;
	double RPM;
	int32_t verticalSpeed;

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