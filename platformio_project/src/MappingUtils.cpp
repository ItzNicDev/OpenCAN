#include "MappingUtils.h"

float MappingUtils::floatMap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int MappingUtils::boostToDegree(float pressure)
{
    return MappingUtils::floatMap(pressure, -1, 1, 20.8, 200.8);
}