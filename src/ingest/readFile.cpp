#include "ingest/readFile.h"
#include <fstream>
#include <exception>
void readFile(const std::string& path, const std::function<void(const std::string&)>& onLine)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        throw std::runtime_error("cannot open file: " + path);
    }
    std::string line;
    while(std::getline(file, line))
    {
        if(!line.empty())
        {
            onLine(line);
        }
    }
}