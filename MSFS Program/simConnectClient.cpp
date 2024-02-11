// MSFS Program.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "SimConnect.h" //SimConnect Library
#include "Controller.h"
#include "serverConnection.h"

int main()
{
    connectToServer();
    initSimEvents();
  
    return 0;
}

