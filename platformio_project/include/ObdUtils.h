#pragma once
#include <stdlib.h>
#include <Arduino.h>
#include <cstring>

class ObdUtils
{

public:
    ObdUtils()
    {
    }

    float hexToDecimal(const char *hex);

private:
};