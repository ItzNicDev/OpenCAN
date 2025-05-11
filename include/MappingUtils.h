#pragma once

class MappingUtils
{

public:
    MappingUtils();

    float floatMap(float x, float in_min, float in_max, float out_min, float out_max);

    int boostToDegree(float pressure);

private:
};