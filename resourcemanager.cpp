#include "resourcemanager.h"

ShaderCache ResourceManager::_shaderCache;

Shader ResourceManager::getShader(const std::string& vertPath,
                                  const std::string& fragPath)
{
    return _shaderCache.getShader(vertPath, fragPath);
}
