// MSFS Flight Assistant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "serverConnection.h"
#include "simMode.h"

int main()
{
    connectToServer();
    initSimMode();

    return 0;

}
