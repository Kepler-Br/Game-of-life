#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <GL/glew.h>

#include <string>
#include <vector>

class IOManager
{
public:
    static std::string readTextFile(const std::string& path);
    static std::vector<char> readBinFile(const std::string& path);
};

#endif // IOMANAGER_H
