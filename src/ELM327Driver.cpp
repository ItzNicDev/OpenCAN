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

void str_replace(char *src, char *oldchars, char *newchars)
{
    char *p = strstr(src, oldchars);
    char buf[64];
    do
    {
        if (p)
        {
            memset(buf, '\0', strlen(buf));
            if (src == p)
            {
                strcpy(buf, newchars);
                strcat(buf, p + strlen(oldchars));
            }
            else
            {
                strncpy(buf, src, strlen(src) - strlen(p));
                strcat(buf, newchars);
                strcat(buf, p + strlen(oldchars));
            }
            memset(src, '\0', strlen(src));
            strcpy(src, buf);
        }
    } while (p && (p = strstr(src, oldchars)));
}

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
                }
            }

            // test
            //  strcpy(response, "010B41 0B 1D");

            str_replace(response, " ", ""); // removing white spaces
            ObdUtils obdUtils;
            size_t len = strlen(response);
            char high[3];
            char low[3];

            const char *extractedValue = nullptr;
            float parsedValue = 0;

            if (obdSensorType == ObdSensorType::Boost)
            {
                // save last du byte in low
                strncpy(low, &response[len - 2], 2);
                low[2] = '\0';
                return obdUtils.hexToDecimal(low) / 100;
            }
            else if (obdSensorType == ObdSensorType::Rpm)
            {
                // Für RPM: Die letzten 2 Zeichen in "low" und die ersten 2 in "high"
                strncpy(low, &response[len - 2], 2);
                low[2] = '\0';
                strncpy(high, &response[len - 4], 2);
                high[2] = '\0';
                return ((256 * obdUtils.hexToDecimal(high)) + obdUtils.hexToDecimal(low)) / 4;
            }
            else
            {
                return 0;
            }
        }
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
