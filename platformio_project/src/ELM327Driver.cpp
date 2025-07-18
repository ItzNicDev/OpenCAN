#include "ELM327Driver.h"
#include "ObdUtils.h"

ELM327Driver::ELM327Driver(uint8_t adress[6])
{
    for (int i = 0; i < 6; i++)
    {
        _adress[i] = adress[i];
    }
}

bool bluetoothConfigured = false;

// char* str_rm_ws(char* str) {
//   if (str == nullptr) {
//     return nullptr;
//   }

//   int i = 0;
//   int j = 0;
//   while (str[i] != '\0') {
//     if (str[i] != ' ') {
//       str[j] = str[i];
//       j++;
//     }
//     i++;
//   }
//   str[j] = '\0';
//   return str;
// }

float ELM327Driver::getResponse(ObdSensorType obdSensorType)
{
    if (bluetoothConfigured)
    {

        ELM327Driver::_serialBT.println(ELM327Driver::_obdSensorHexMap[obdSensorType]);

        if (ELM327Driver::_serialBT.available())
        {
            char response[64];
            size_t index = 0;

            while (true)
            {
                if (ELM327Driver::_serialBT.available())
                {
                    char c = ELM327Driver::_serialBT.read();
                    if (c == '>')
                    {
                        response[index] = '\0';
                        break;
                    }
                    if (index < sizeof(response) - 1)
                    {
                        response[index++] = c;
                    }
                    else
                    {
                        // Buffer full, terminate string and break to avoid overflow
                        response[sizeof(response) - 1] = '\0';
                        Serial.println("Warning: OBD response too long, truncated!");
                        break;
                    }
                }
            }
            ObdUtils obdUtils;

            Serial.println("Before transforming " + String(response));

            float decodedResponse =  obdUtils.decodeSensorValue(response, obdSensorType);
            Serial.println(decodedResponse);

            return decodedResponse; // <-- ADD THIS LINE!
        }
        // If no response available, return 0
        return 0; // <-- ADD THIS LINE!
    }
    else
    {
        Serial.println("Bluetooth needs to be configured. Use 'setupBluetoothComunication' for setup");
        return 0;
    }
}

void ELM327Driver::setupBluetoothComunication()
{
    int attempts = 1;
    bool connectionSuccessful = false;

    Serial.println("ESP32 Bluetooth Client startet...");

    if (!ELM327Driver::_serialBT.begin("ESP32_Client", true))
    {
        Serial.println("Bluetooth konnte nicht gestartet werden.");
        while (1)
            ;
    }

    Serial.println("Bluetooth als Client gestartet");
    bluetoothConfigured = true;
    while (!connectionSuccessful)
    {
        if (ELM327Driver::_serialBT.connect(ELM327Driver::_adress))
        {
            Serial.println("Connection successful");
            connectionSuccessful = true;
        }
        else
        {
            Serial.println("Connection failed!");
            delay(3000);
        }
        attempts++;
    }
}
