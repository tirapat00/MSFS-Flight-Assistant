#include <iostream>
#include <Windows.h>
#include "SimConnect.h"
#include "handle.h"
#include "../MSFS Flight Assistant/dataStruct.h"
#include "serverConnection.h"

//Add various definitions of data structs
static enum DATA_DEFINE_ID {
    DEFINITION_1,
};

//Data request IDs, you can sort various data requests if you haave more than one request
static enum DATA_REQUEST_ID {
    REQUEST_1,
};


//Structure that holds all data
struct SimResponse {
    double altitude;
    double latitude;
    double longitude;
    double bearing;
    double heading;
    double speed;
    double RPM;
    double vertical_speed;
};

int quit = 0; //0 = keep running - 1 = Exit App


void defineData() {
    HRESULT hR;
    //#IMPORTANT: the request order must correspond with the declaration of the response struct
    //SimConnect_AddToDataDefinition takes : HANDLE, enum DEFINITION_ID, const char* UNIT, DATATYPE, Default is FLOAT64
    hR = SimConnect_AddToDataDefinition(handle, DEFINITION_1, "INDICATED ALTITUDE", "feet");
    hR = SimConnect_AddToDataDefinition(handle, DEFINITION_1, "PLANE LATITUDE", "degrees");
    hR = SimConnect_AddToDataDefinition(handle, DEFINITION_1, "PLANE LONGITUDE", "degrees");
    hR = SimConnect_AddToDataDefinition(handle, DEFINITION_1, "GPS WP BEARING", "degrees");
    hR = SimConnect_AddToDataDefinition(handle, DEFINITION_1, "HEADING INDICATOR", "degrees");
    hR = SimConnect_AddToDataDefinition(handle, DEFINITION_1, "AIRSPEED INDICATED", "knots");
    hR = SimConnect_AddToDataDefinition(handle, DEFINITION_1, "GENERAL ENG RPM:1", "rpm");
    hR = SimConnect_AddToDataDefinition(handle, DEFINITION_1, "VERTICAL SPEED", "feet/second");
}

void requestData() {
    HRESULT hR;
    hR = SimConnect_RequestDataOnSimObject(handle, REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);
}

void CALLBACK DispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
    switch (pData->dwID)
    {
        //CASE we receive data from MSFS
    case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
    {
        //Retrieve Simulation data and cast it to SIMCONNECT_RECV_SIMOBHECT_DATA Pointer
        SIMCONNECT_RECV_SIMOBJECT_DATA* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

        //Switch to find right request(if there is more than 1 request add case here)
        switch (pObjData->dwRequestID)
        {
        case REQUEST_1:
            //Cast the request data to a SimResponse (defined struct)
            SimResponse* pS = (SimResponse*)&pObjData->dwData;

            //use data here for now print to console
            std::cout

                << "\rAltitude: " << pS->altitude
                << " \n- Latitude: " << pS->latitude
                << " \n- Longitude: " << pS->longitude
                << " \n- Bearing to Waypoint: " << pS->bearing
                << " \n- Heading: " << pS->heading
                << " \n- Speed(knots): " << pS->speed
                << " \n- RPM: " << pS->RPM
                << " \n- Vertical Speed: " << pS->vertical_speed

                << std::flush;
            sendToServer(pS->altitude, pS->latitude, pS->longitude, pS->bearing, pS->heading, pS->speed, pS->RPM, pS->vertical_speed);
            break;
        }

        break;
    }

    //CASE quit MSFS
    case SIMCONNECT_RECV_ID_QUIT:
    {
        quit = 1; // Application will quit if MSFS is closed

        break;

    }

    //Insert other events here (breaking,landing and so on)
    default:

        break;
    }
}

void handleEvent() {
    SimConnect_CallDispatch(handle, DispatchProc1, NULL);
    Sleep(1);
}

int getQuit() {
    return quit;
}

void closeHandle() {
    HRESULT hR;
    hR = SimConnect_Close(handle);
}
