#include "ELM327BT.h"

ELM327BT elm327 = ELM327BT("ab:cd:ef:12:34:56");

void setup() {
  elm327.init();
  elm327.requestValue(EngineLoad);
}

void loop() {  
}
