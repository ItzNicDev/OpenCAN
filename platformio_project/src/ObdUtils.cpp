#include "ObdUtils.h"
#include "StringUtils.h"

float ObdUtils::hexToDecimal(const char *hex)
{
    return (float)strtol(hex, NULL, 16);
}

float ObdUtils::decodeSensorValue(char dataBytes[64], ObdSensorType obdSensorType)
{
    const char *responseWithoutWhitespace = StringUtils::str_rm_ws(dataBytes);

    constexpr size_t RESPONSE_OFFSET = 11;
    char high[3];
    char low[3];
    const char *extractedValue = nullptr;
    float parsedValue = 0;

    switch (obdSensorType)
    {
    case ObdSensorType::Boost:
        strncpy(low, &responseWithoutWhitespace[RESPONSE_OFFSET - 2], 2);
        low[2] = '\0';
        return hexToDecimal(low) / 100;
        break;

    case ObdSensorType::Rpm:
        strncpy(low, &responseWithoutWhitespace[RESPONSE_OFFSET - 2], 2);
        low[2] = '\0';
        strncpy(high, &responseWithoutWhitespace[RESPONSE_OFFSET - 4], 2);
        high[2] = '\0';
        return ((256 * hexToDecimal(high)) + hexToDecimal(low)) / 4;
        break;

    default:
        return 0;
        break;
    }
}