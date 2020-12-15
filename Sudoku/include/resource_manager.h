#pragma once

#include <map>
#include <string>
#include "glad/glad.h"
#include "texture.h"
#include "shader/shader.h"


/// <summary>
/// 一个单例资源管理类，管理所有的的shader和texture
/// </summary>
class ResourceManager
{
public:
    //资源储存
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    //加载一个Shader
    static Shader&   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    //获得一个Shader
    static Shader&   GetShader(std::string name);
    //加载一个Texture
    static Texture2D& LoadTexture(const GLchar *file,std::string name);
    //获得一个Texture
    static Texture2D& GetTexture(std::string name);
    //释放所有该管理器托管的资源
    static void Clear();
private:
    //私有构造器，不允许再被创建实例
    ResourceManager() { }
};

