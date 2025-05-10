#include <SwitecX25.h>

SwitecX25 motor1(945, 14, 16, 17, 18);

void moveToAngle(int angle) {
  int targetSteps = angle * 3;
  motor1.setPosition(targetSteps);

  while (!motor1.stopped) {
    motor1.update();
    delay(1);
  }
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int boostToDegree(float pressure) {
  return floatMap(pressure, -1, 1, 0, 180);
}

void reference() {
  int targetSteps = -200 * 3; 
  motor1.setPosition(targetSteps);

  while (!motor1.stopped) {
    motor1.update();
    delay(1);  
  }
}


void setup() {
  Serial.begin(9600);

  reference();
  delay(1000);

  moveToAngle(boostToDegree(0));
  delay(1000);

  moveToAngle(boostToDegree(0.5));

  delay(1000);
  moveToAngle(boostToDegree(1));
}

void loop() {
}
