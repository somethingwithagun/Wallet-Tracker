#include "fsystem.h"

Filesystem::Filesystem()
{

}

bool Filesystem::writeInto(std::string path,std::string filename, std::string data)
{
    std::string fullpath = path + filename;

#if defined(_WIN32) || defined(_WIN64)
    mkdir(path.c_str());
#else 
    mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    std::string previousData =Filesystem::readFromFile(fullpath);

    std::ofstream dist(fullpath);

    if(!dist.is_open())
        return false;

    previousData = (previousData == "error") ? "" : previousData; // if the error had happened then set string to the null-string
    dist <<  previousData/*<- getting previous data */ + data /*<- appending current data */;

    dist.close();

    return true;
}
bool Filesystem::replaceInto(std::string path,std::string filename, std::string data)
{
    std::string fullpath = path + filename;

#if defined(_WIN32) || defined(_WIN64)
    mkdir(path.c_str());
#else 
    mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    std::ofstream dist(fullpath);

    if(!dist.is_open())
        return false;

    dist << data /*<- appending current data */;

    dist.close();

    return true;
}

bool Filesystem::exists(std::string path)
{
    std::ifstream dist(path);
    if(dist.is_open())
    {
        dist.close();
        return true;
    }
    return false;
}
bool Filesystem::rm(std::string path, std::string filename)
{
    std::string fullpath = path +'/'+ filename;
    return !(remove(fullpath.c_str()));
}
std::string Filesystem::readFromFile(std::string path)
{
    if(!Filesystem::exists(path))
        return std::string("");

    std::ifstream dist(path);

    if(!dist.is_open())
        return std::string("");

    std::string data = "";
    std::string buffer = "";
    while(std::getline(dist, buffer))
        data +=buffer+'\n';

    return data;
}
