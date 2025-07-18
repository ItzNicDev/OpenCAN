#pragma once
#include <stdlib.h>
#include <Arduino.h>
#include <cstring>
#include <ObdSensorType.h>
#include "StringUtils.h"

class ObdUtils
{

public:
    ObdUtils()
    {
    }

    float hexToDecimal(const char *hex);
    float decodeSensorValue(char dataBytes[64], ObdSensorType obdSensorType);

private:
    // StringUtils stringUtils;
};