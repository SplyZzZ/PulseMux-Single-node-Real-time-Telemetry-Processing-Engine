#include <fstream>
#include <functional>
void readFile(const std::string& path, const std::function<void(const std::string&)>& onLine);
