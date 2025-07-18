
#include "StringUtils.h"

char * StringUtils::str_rm_ws(char *str)
{
    if (str == nullptr)
    {
        return nullptr;
    }

    int i = 0;
    int j = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ')
        {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
    return str;
}