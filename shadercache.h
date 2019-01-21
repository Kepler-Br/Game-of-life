#ifndef SHADERCACHE_H
#define SHADERCACHE_H

#include <map>
#include <string>

#include "shader.h"

class ShaderCache
{
private:
    std::map<std::string, Shader> _shaderMap;

    Shader loadShader(const std::string& vertPath, const std::string& fragPath);
    void shaderCheckCompileErrors(const GLuint shader, const std::string& type,
                                  const std::string& path = "");

public:
    ShaderCache();
    ~ShaderCache();
    Shader getShader(const std::string& vertPath, const std::string& fragPath);
};

#endif // SHADERCACHE_H
