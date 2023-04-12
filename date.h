#ifndef DATE_H
#define DATE_H

#include <string>
#include <ctime>
#include <cstring>

namespace Date
{
// returns a formatted string
// (works like the strftime)
std::string getCurrentDate(const char* formatType);


}; // namespace Date

#endif
