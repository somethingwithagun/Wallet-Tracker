#include "date.h"

std::string Date::getCurrentDate(const char* formatType)
{
    std::time_t currentClock = std::time(0);
    char currentDate[std::size("dd.mm.yy") + 1];
    std::strftime(&currentDate[0], std::size(currentDate), formatType, std::localtime(&(currentClock)));
    return std::string(currentDate);
}