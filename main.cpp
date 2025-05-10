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

  float parsedValue()
  {
    switch (sensor)
    {
    case RPM:
      return (
          ((256 * hexToDecimal(getBytesHigh())) +
           hexToDecimal(getBytesLow())) /
          4);
    case BOOST:
      return ((hexToDecimal(getBytesHigh()) / 100.0f) - 1); // kPa in bar
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

  static float hexToDecimal(const char *pHex)
  {
    return (float)strtol(pHex, NULL, 16);
  }
};

const char *getSimulatedResponse()
{
  const char *x = "010B41 0B 1D";
  return x;
}
// Globale Instanz
OBD_REQUEST rpmRequest("0000", RPM);

// Fester Puffer für Antwort
char responseBuffer[16];

uint8_t obdAddress[] = {0x00, 0x1D, 0xA5, 0x07, 0x52, 0x39};
String obdMAC = "00:1D:A5:07:52:39";

const char *sendOBDRequest(const char *pPID)
{

  SerialBT.println(pPID);

  if (SerialBT.available())
  {
    String response = SerialBT.readStringUntil('>'); // Lese bis zum '>' Zeichen
    Serial.println("Antwort erhalten (roh): " + response);

    response.replace(" ", "");
    response.replace(pPID, "");
    response.replace("410B", "");
    // response.replace("41"+String(pPID).substring(2,3), "");

    // Entferne alle Zeichen außer den Hex-Ziffern
    String hexDigits = "";
    for (char c : response)
    {
      if (isHexadecimalDigit(c))
      {
        hexDigits += c;
      }
    }

    strncpy(responseBuffer, hexDigits.c_str(), sizeof(responseBuffer) - 1);
    responseBuffer[sizeof(responseBuffer) - 1] = '\0';
    Serial.println("Antwort bereinigt: " + String(responseBuffer));
    return responseBuffer;
  }

  return "";
}

// list of all PIDs
float executeOBDCall(SENSOR pSensorType)
{
  const char *response;

  switch (pSensorType)
  {
  case RPM:
    response = sendOBDRequest("010C");
    break;

  case BOOST:
    response = sendOBDRequest("010B");
    break;

  default:
    response = 0;
    break;
    // return 0;
  }

  rpmRequest = OBD_REQUEST(response, pSensorType);
  Serial.println(rpmRequest.getBytesHigh());
  Serial.println(rpmRequest.getBytesLow());

  return rpmRequest.parsedValue();
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

  for (;;)
  {
    float rpmValue = executeOBDCall(BOOST);
    Serial.println("Boost: " + String(rpmValue) + " bar");
    delay(100);
  }
}

void loop()
{
}
