#include "shadercache.h"

#include "iomanager.h"
#include <iostream>

Shader ShaderCache::loadShader(const std::__cxx11::string& vertPath,
                               const std::__cxx11::string& fragPath)
{
    std::string vertSource = IOManager::readTextFile(vertPath);
    std::string fragSource = IOManager::readTextFile(fragPath);
    // 2. Compile shaders
    GLuint vertex, fragment;
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vSource = vertSource.c_str();
    glShaderSource(vertex, 1, &vSource, NULL);
    glCompileShader(vertex);
    shaderCheckCompileErrors(vertex, "VERTEX", vertPath);
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fSource = fragSource.c_str();
    glShaderSource(fragment, 1, &fSource, NULL);
    glCompileShader(fragment);
    shaderCheckCompileErrors(fragment, "FRAGMENT", fragPath);
    // Shader Program
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    shaderCheckCompileErrors(programID, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer
    // necessery.
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    Shader shader;
    shader.ID = programID;
    return shader;
}

void ShaderCache::shaderCheckCompileErrors(const GLuint shader,
                                           const std::string& type,
                                           const std::string& path)
{
    GLint success;
    GLchar infoLog[2048];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 2048, NULL, infoLog);
            std::cout << "ShaderCache::shaderCheckCompileErrors: \nShader "
                         "compilation error:\n"
                      << "\tShader path: " << path << "\n"
                      << "\tType: " << type << "\n"
                      << "\tInformation: " << infoLog << std::endl;
            throw std::runtime_error("Shader program error");
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 2048, NULL, infoLog);
            std::cout << "ShaderCache::shaderCheckCompileErrors: \nShader "
                         "linking error:\n"
                      << "\tType: " << type << "\n"
                      << "\tInformation: " << infoLog << std::endl;
            throw std::runtime_error("Shader linking error.");
        }
    }
}

ShaderCache::ShaderCache()
{
}

ShaderCache::~ShaderCache()
{
    // TODO: Unloading stuff.
}

Shader ShaderCache::getShader(const std::string& vertPath,
                              const std::string& fragPath)
{
    std::string catString = vertPath + fragPath;
    auto it = _shaderMap.find(catString);
    // No such shader were loaded.
    if (it == _shaderMap.end())
    {
        Shader shader = loadShader(vertPath, fragPath);
        _shaderMap.insert(std::make_pair(catString, shader));
        return shader;
    }
    return it->second;
}
