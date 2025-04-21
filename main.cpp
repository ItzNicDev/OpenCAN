#include <cstring>
#include <stdlib.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

enum SENSOR
{
  RPM,
  BOOST
};

struct OBD_REQUEST
{
  OBD_REQUEST(const char *pResponseByte, SENSOR pSensor)
  {
    strncpy(responseBytes, pResponseByte, sizeof(responseBytes) - 1);
    responseBytes[sizeof(responseBytes) - 1] = '\0';
    sensor = pSensor;
  }

  char responseBytes[8]; // max 6 Bytes + Nullterminator
  SENSOR sensor;

  char high[3];
  char low[3];

  int parsedValue()
  {
    switch (sensor)
    {
    case RPM:
      return (
          ((256 * hexToDecimal(getBytesHigh())) +
           hexToDecimal(getBytesLow())) /
          4);
    default:
      return 0;
    }
  }

  const char *getBytesHigh()
  {
    strncpy(high, responseBytes, 2);
    high[2] = '\0';
    return high;
  }

  const char *getBytesLow()
  {
    strncpy(low, responseBytes + 2, 2);
    low[2] = '\0';
    return low;
  }

  static int hexToDecimal(const char *pHex)
  {
    return strtol(pHex, NULL, 16);
  }
};

// Globale Instanz
OBD_REQUEST rpmRequest("0000", RPM);

// Fester Puffer für Antwort
char responseBuffer[16];

uint8_t obdAddress[] = {0x00, 0x1D, 0xA5, 0x07, 0x52, 0x39};
String obdMAC = "00:1D:A5:07:52:39";

const char *sendOBDRequest(const char *pPID)
{
  SerialBT.println(pPID);
  delay(1000);

  if (SerialBT.available())
  {
    String response = SerialBT.readString();
    // String response = "010C41 0C 10 A2";
    Serial.println("Antwort erhalten: " + response);

    response.replace(" ", "");
    response.replace("010C", "");
    response.replace("410C", "");

    strncpy(responseBuffer, response.c_str(), sizeof(responseBuffer) - 1);
    responseBuffer[sizeof(responseBuffer) - 1] = '\0';
    return responseBuffer;
  }

  return "";
}

int executeOBDCall(SENSOR pSensorType)
{
  const char *response;

  switch (pSensorType)
  {
  case RPM:
    response = sendOBDRequest("010C");
    rpmRequest = OBD_REQUEST(response, pSensorType);
    return rpmRequest.parsedValue();
  default:
    return 0;
  }
}

void setupBluetoothComunication()
{
  int attempts = 1;
  bool connectionSuccessful = false;

  Serial.println("ESP32 Bluetooth Client startet...");

  if (!SerialBT.begin("ESP32_Client", true))
  {
    Serial.println("Bluetooth konnte nicht gestartet werden.");
    while (1)
      ;
  }

  Serial.println("Bluetooth als Client gestartet");

  while (!connectionSuccessful)
  {
    if (SerialBT.connect(obdAddress))
    {
      Serial.println("Verbindung erfolgreich zu: " + obdMAC);
      connectionSuccessful = true;
    }
    else
    {
      Serial.println("Verbindung fehlgeschlagen zu: " + obdMAC);
      Serial.println("Versuch " + String(attempts));
      delay(3000);
    }
    attempts++;
  }
}

void setup()
{
  Serial.begin(115200);
  setupBluetoothComunication();
  int rpmValue = executeOBDCall(RPM);
  Serial.println("Drehzahl: " + String(rpmValue));
}

void loop()
{
}
