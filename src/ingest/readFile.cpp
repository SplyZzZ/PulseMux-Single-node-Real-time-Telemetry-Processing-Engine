#include "ingest/readFile.h"
#include "pipeline/router.h"
#include "pipeline/worker.h"
#include <fstream>
#include <exception>
#include <string>
void readFile(const std::string& path,  std::function<void(const std::string_view&)>& onLine)
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