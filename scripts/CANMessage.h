#ifndef CAN_MESSAGE_H
#define CAN_MESSAGE_H

#include <Arduino.h>

enum MessageType {
  EngineLoad,
  CoolantTemperature,
  FuelPressure,
  IntakeManifoldAbsolutePressure,
  EngineSpeed,
  VehicleSpeed,
  IntakeAirTemperature,
};

class CANMessage {

private:
  struct KeyValuePair {
    MessageType key;       // Using MessageType for key
    const char* value;     // PID value as const char*
  };

  // The map of MessageTypes to their corresponding PIDs
  KeyValuePair obdMap[7] = {
    { EngineLoad, "04" },
    { CoolantTemperature, "05" },
    { FuelPressure, "0A" },
    { IntakeManifoldAbsolutePressure, "0B" },
    { EngineSpeed, "0C" },
    { VehicleSpeed, "0D" },
    { IntakeAirTemperature, "0F" }
  };

public:
  const char* getPID(MessageType messageType);  // Declare the method with const char*
};

#endif
