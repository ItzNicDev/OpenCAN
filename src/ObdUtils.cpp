#include "ObdUtils.h"

float ObdUtils::hexToDecimal(const char *hex)
{
    return (float)strtol(hex, NULL, 16);
}