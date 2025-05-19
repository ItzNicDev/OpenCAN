#include "X27168Driver.h"
#include <MappingUtils.h>

X27168Driver::X27168Driver(unsigned int steps, unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4)
    : _pin1(pin1), _pin2(pin2), _pin3(pin3), _pin4(pin4), _steps(steps), _motor(steps, pin1, pin2, pin3, pin4)
{
}

void X27168Driver::reference()
{
    _motor.setPosition(945);
    _motor.updateBlocking();
    _motor.setPosition(0);
    _motor.updateBlocking();
}

void X27168Driver::moveToAngle(int angle)
{
    _motor.setPosition(angle * 3);
    _motor.updateBlocking();
    delay(1);
}

void X27168Driver::zero()
{
    _motor.zero();
}

void X27168Driver::update()
{
    _motor.update();
}

void X27168Driver::test()
{
    reference();
    for (float i = -1.0; i <= 2.0; i = i + 0.5)
    {
        moveToAngle(_mappingUtils.boostToDegree(i));
        delay(1000);
    }
    for (float i = 2.0; i >= -1.0; i = i - 0.5)
    {
        moveToAngle(_mappingUtils.boostToDegree(i));
        delay(1000);
    }

    for (float i = -1.0; i <= 2.0; i = i + 0.1)
    {
        moveToAngle(_mappingUtils.boostToDegree(i));
        delay(50);
    }

    for (float i = 2.0; i >= -1.0; i = i - 0.1)
    {
        moveToAngle(_mappingUtils.boostToDegree(i));
        delay(50);
    }

    for (float i = -1.0; i <= 2.0; i = i + 0.1)
    {
        moveToAngle(_mappingUtils.boostToDegree(i));
        delay(10);
    }

    for (float i = 2.0; i >= -1.0; i = i - 0.1)
    {
        moveToAngle(_mappingUtils.boostToDegree(i));
        delay(10);
    }

    for (float i = -1.0; i <= 2.0; i = i + 0.1)
    {
        moveToAngle(_mappingUtils.boostToDegree(i));
        delay(5);
    }

    for (float i = 2.0; i >= -1.0; i = i - 0.1)
    {
        moveToAngle(_mappingUtils.boostToDegree(i));
        delay(5);
    }
}