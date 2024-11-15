#include "ELM327BT.h"
#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

SoftwareSerial BTSerial(rxPin, txPin);  // RX, TX
CANMessage canMessage;

ELM327BT::ELM327BT(char* bluetoothAdr)
  : _bluetoothAdr(bluetoothAdr) {
}

char* getResponse() {
  if (BTSerial.available()) {
    char* response = (char*)BTSerial.readString().c_str();  // Read the response from HC-05
    Serial.println(response);                               // Print the response in the Serial Monitor
  } else {
    return nullptr;
  }
}

// EngineLoad,
// CoolantTemperature,
// FuelPressure,
// IntakeManifoldAbsolutePressure,
// EngineSpeed,
// VehicleSpeed,
// IntakeAirTemperature,

double convertToUnit(int value, MessageType messageType) {

  switch (messageType) {
    case EngineLoad:
      return value / 2.55;

    case CoolantTemperature:
      return value - 40;

    case FuelPressure:
      return 3 * value;

    case IntakeManifoldAbsolutePressure:
      return value;

    case EngineSpeed:
      return value / 4;
  }
}


void ELM327BT::init() {
  BTSerial.begin(9600);
  BTSerial.println("AT+RESET");                          // Send AT+RESET command
  BTSerial.println("AT+BIND=" + String(_bluetoothAdr));  // AT-Befehl um verbindung auf zu bauen
}

// Platzhalter für die Methode zum Anfragen eines Wertes
char* ELM327BT::requestValue(MessageType messageType) {

  char* pid = canMessage.getPID(messageType);

  char* response = getResponse();

  return response;
}
