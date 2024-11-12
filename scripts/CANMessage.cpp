#include "CANMessage.h"

const char* CANMessage::getPID(MessageType messageType) {
  for (int i = 0; i < sizeof(obdMap) / sizeof(obdMap[0]); ++i) {
    if (obdMap[i].key == messageType) {
      return obdMap[i].value;  // Return the const char* directly
    }
  }
  return nullptr; // Return nullptr if the MessageType is not found
}
