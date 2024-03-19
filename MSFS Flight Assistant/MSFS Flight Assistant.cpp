// MSFS Flight Assistant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "serverConnection.h"
#include "simMode.h"
#include "commWithPi.h"


int main()
{
    DWORD thread;

    connectToServer();
    CreateThread(NULL, 0, startPiServer, (LPVOID)NULL, 0, &thread);
    initSimMode();

    return 0;

}
