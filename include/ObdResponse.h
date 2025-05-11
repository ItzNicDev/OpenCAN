#pragma once

class ObdResponse
{
public:
    ObdResponse(int value);
    void printValue() const;
    char responseBytes[7];
    char high[3];
    char low[3];
    float parsedValue;

private:
    int value_;
};