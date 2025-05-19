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

void motorMiddlePosition(X27168Driver _motor)
{
  _motor.moveToAngle(158);
}

MappingUtils mappingUtils;
X27168Driver motor(945, 14, 16, 17, 18);
uint8_t obdAddress[] = {0x00, 0x1D, 0xA5, 0x07, 0x52, 0x39};
ELM327Driver elm327(obdAddress);

void setup()
{
  Serial.begin(9600);
  // elm327.setupBluetoothComunication();
  motor.reference();
  delay(1000);
  motor.test();


  delay(1000);

  float boost = 0;
  float degree = 0;
  float smoothedDegree = 0;    // Zwischenspeicher für geglätteten Winkel
  float smoothingFactor = 0.7; // Wie stark geglättet wird (0 = sehr smooth, 1 = direkt)

  // for (;;)
  // {
  //   boost = elm327.getResponse(ObdSensorType::Boost);

  //   degree = boostToDegree(boost);

  // smoothedDegree += (degree - smoothedDegree) * smoothingFactor;

  //   motor.moveToAngle(degree);

  //   delay(60);
  // }
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
