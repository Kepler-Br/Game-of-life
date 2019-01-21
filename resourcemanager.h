#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>

#include "shader.h"
#include "shadercache.h"

class ResourceManager
{
private:
    ResourceManager();
    static ShaderCache _shaderCache;

public:
    static Shader getShader(const std::string& vertPath,
                            const std::string& fragPath);
};

#endif // RESOURCEMANAGER_H
