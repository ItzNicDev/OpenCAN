#ifndef ELM_327_BT_H
#define ELM_327_BT_H

#include <Arduino.h>
#include "CANMessage.h"


class ELM327BT {

public:
  //constructor
  ELM327BT(char* bluetoothAdr);

  //methods
  void init();
  char* requestValue(MessageType messageType);


private:
  char* _bluetoothAdr;
  MessageType _messageType;  
};



#endif
