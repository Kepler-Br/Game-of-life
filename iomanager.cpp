#include "iomanager.h"
#include <fstream>
#include <iostream>

std::string IOManager::readTextFile(const std::__cxx11::string& path)
{
    std::string out;
    std::ifstream file(path);
    if (file.fail())
    {
        std::cout << "IOManager::readTextFile: cannot open " << path
                  << std::endl;
        throw std::ios_base::failure("Cannot open file.");
    }

    // Get file size.
    file.seekg(0, std::ios::end);
    uint fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    fileSize -= file.tellg();
    out.resize(fileSize);
    file.read(&out[0], fileSize);

    return out;
}

std::vector<char> IOManager::readBinFile(const std::string& path)
{
    std::vector<char> out;
    std::ifstream file(path, std::ios_base::binary);
    if (file.fail())
    {
        std::cout << "IOManager::readBinFile: cannot open " << path
                  << std::endl;
        throw std::ios_base::failure("Cannot open file.");
    }

    // Get file size.
    file.seekg(0, std::ios::end);
    uint fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    fileSize -= file.tellg();
    out.resize(fileSize);
    file.read(&out[0], fileSize);

    return out;
}
