#pragma once

#include "ObdResponse.h"
#include "ObdSensorType.h"
#include <stdint.h>
#include <BluetoothSerial.h>

class ELM327Driver
{

public:
    ELM327Driver(uint8_t adress[6]);

    void setupBluetoothComunication();
    float getResponse(ObdSensorType obdSensorType);

private:
    uint8_t _adress[6];
    BluetoothSerial _serialBT;
    std::map<ObdSensorType, char*> _obdSensorHexMap{
        {ObdSensorType::Boost, "010B"},
        {ObdSensorType::Rpm, "010C"},
    };
};
