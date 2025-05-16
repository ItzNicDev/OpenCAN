#pragma once

#include <SwitecX25.h>

class X27168Driver
{
public:
    X27168Driver(unsigned int steps, unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4);

    void reference();
    void moveToAngle(int angle);
    void zero();
    void update();

private:
    unsigned char _pin1, _pin2, _pin3, _pin4;
    unsigned int _steps;
    SwitecX25 _motor;
};