#include <iostream>
#include <Windows.h>
#include "SimConnect.h"
#include "dataHandler.h"
#include "connectionHandler.h"
#include "handle.h"

HANDLE handle;

bool initSimEvents() {
    HRESULT hr = NULL;
    
    //If successfully connected display success message
    if (establishConnection()){
        //Request Data
        defineData();
        //Request Data every second on the current user aircraft (SIMCONNECT_OBJECT_ID_USER)
        requestData();

        //Process incoming SimConnect Server messages while the app is runing 
        while (getQuit() == 0) {
            // Call SimConnect_CallDispatch every second while the program is running. DispatchProc1 will handle simulation events
            handleEvent();
        }

        //When we are finished with the App we can close the SimConnect Handle
        closeHandle();
        return true;

    }
    //Display failes message when connection failed
    else {
        return false;
    }
}