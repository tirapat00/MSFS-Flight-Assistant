#pragma once
#include <iostream>
#include <Windows.h>

struct simData {
	double altitude;
	int32_t heading;
	int32_t speed;
	int32_t verticalSpeed;

};

struct sendStruct {
	const char flag = 0;
	simData data;
};

struct requestStruct {
	const char flag = 1;
};