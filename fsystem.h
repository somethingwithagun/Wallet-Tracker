#ifndef FSYSTEM_H
#define FSYSTEM_H

#include <string>
#include <QString>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>

class Filesystem
{
public:
    Filesystem();
    static bool writeInto(std::string path,std::string filename, std::string data);
    static bool replaceInto(std::string path,std::string filename, std::string data);
    static bool exists(std::string path);
    static bool rm(std::string path, std::string filename);
    static std::string readFromFile(std::string path);
};

#endif // FSYSTEM_H
