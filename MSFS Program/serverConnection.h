#pragma once
void connectToServer();
void sendToServer(double altitude, double latitude, double longitude, int32_t heading, int32_t speed, int32_t verticalSpeed, int32_t RPM);