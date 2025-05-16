/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"
#include "X27168Driver.h"
#include "MappingUtils.h"
#include "ELM327Driver.h"

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() {}

// Initialize C library
extern "C" void __libc_init_array(void);

void loop()
{
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float boostToDegree(float boost)
{
  return floatMap(boost, -1, 1, 43, 221.2);
}

MappingUtils mappingUtils;
X27168Driver motor(945, 14, 16, 17, 18);
uint8_t obdAddress[] = {0x00, 0x1D, 0xA5, 0x07, 0x52, 0x39};
ELM327Driver elm327(obdAddress);

void setup()
{
  Serial.begin(9600);
  elm327.setupBluetoothComunication();
  motor.reference();
  delay(1000);

  float degree;
  float boost;
  for (;;)
  {
    boost = elm327.getResponse(ObdSensorType::Boost);
    Serial.println(String(boost) + " bar");
    degree = boostToDegree(boost);
    motor.moveToAngle(degree);
    delay(25);
  }
}

/*
 * \brief Main entry point of Arduino application
 */
int main(void)
{
  init();

  __libc_init_array();

  initVariant();

  delay(1);
#if defined(USBCON)
  USBDevice.init();
  USBDevice.attach();
#endif

  setup();

  for (;;)
  {
    loop();
    if (serialEventRun)
      serialEventRun();
  }

  return 0;
}
