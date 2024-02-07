#include <iostream>
#include <Windows.h>
#include "SimConnect.h"
#include "handle.h"

bool establishConnection() {
	if (SUCCEEDED(SimConnect_Open(&handle, "ClientEvent", NULL, 0, NULL, 0)))
	{
		std::cout << "SimConnect connected successfully to MSFS! Praise the IT Gods\n" << std::endl;
		return true;
	}
	else 
	{
		std::cout << "SimConnect connection failed! You angered the IT Gods\n" << std::endl;
		return false;
	}
	
}

bool failedConnection() {
	return false;
}