#pragma once

#include <map>
#include <string>
#include "glad/glad.h"
#include "texture.h"
#include "shader/shader.h"


/// <summary>
/// һ��������Դ�����࣬�������еĵ�shader��texture
/// </summary>
class ResourceManager
{
public:
    //��Դ����
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    //����һ��Shader
    static Shader&   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    //���һ��Shader
    static Shader&   GetShader(std::string name);
    //����һ��Texture
    static Texture2D& LoadTexture(const GLchar *file,std::string name);
    //���һ��Texture
    static Texture2D& GetTexture(std::string name);
    //�ͷ����иù������йܵ���Դ
    static void Clear();
private:
    //˽�й��������������ٱ�����ʵ��
    ResourceManager() { }
};

