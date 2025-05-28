#include "X27168Driver.h"
#include <MappingUtils.h>

X27168Driver::X27168Driver(unsigned int steps, unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4)
    : _pin1(pin1), _pin2(pin2), _pin3(pin3), _pin4(pin4), _steps(steps), _motor(steps, pin1, pin2, pin3, pin4)
{
}

void X27168Driver::reference()
{
    _motor.setPosition(_steps);
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

void X27168Driver::setTargetAngle(float angle) // Parameter ist jetzt float
{
    // ACHTUNG: Hier wird MappingUtils::boostToDegree() verwendet.
    // Da MappingUtils 'mappingUtils' ein GLOBALES Objekt im Hauptsketch ist,
    // kann es hier nicht direkt als '_mappingUtils' aufgerufen werden,
    // es sei denn, es ist ein Member der X27168Driver Klasse (was es nicht ist).
    // Wenn 'boostToDegree' eine statische Methode von MappingUtils wäre, ginge 'MappingUtils::boostToDegree'.
    //
    // Da 'degree' schon vom Hauptsketch kommt (nach der Umwandlung durch mappingUtils),
    // sollte 'angle' hier bereits der fertige "Gradwert" sein, den der Motor verwenden kann.
    // Die Konvertierung in Schritte * 3.0f ist dein Skalierungsfaktor für den Motor.

    int targetStep = static_cast<int>(angle * 3.0f); // Konvertiere float-Winkel in int-Schritte

    // Stelle sicher, dass der Zielschritt innerhalb des gültigen Bereichs liegt
    // (nicht kleiner als 0 und nicht größer als _steps - 1)
    if (targetStep < 0)
        targetStep = 0;
    if (targetStep >= _steps) // Muss <= _steps - 1 sein, wenn _steps die Anzahl der Schritte ist
        targetStep = _steps - 1; // Die SwitecX25 ist 0-basiert bis steps-1

    _motor.setPosition(targetStep); // Setzt das Ziel für den SwitecX25-Motor
    // WICHTIG: KEIN _motor.updateBlocking() oder delay() hier!
    // Die Bewegung wird durch regelmäßige Aufrufe von update() im loop() gesteuert.
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
