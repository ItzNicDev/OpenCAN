#include "X27168Driver.h"

X27168Driver::X27168Driver(unsigned int steps, unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4)
    : _pin1(pin1), _pin2(pin2), _pin3(pin3), _pin4(pin4), _steps(steps), _motor(steps, pin1, pin2, pin3, pin4)
{
}

void X27168Driver::reference()
{
    int targetSteps = -200 * 3;
    _motor.setPosition(targetSteps);

    while (!_motor.stopped)
    {
        _motor.update();
        delay(1);
    }
}

void X27168Driver::moveToAngle(int angle)
{
    _motor.setPosition(angle * 3);

    while (!_motor.stopped)
    {
        _motor.update();
        delay(1);
    }
}