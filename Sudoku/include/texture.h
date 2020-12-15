#pragma once

#include "glad/glad.h"

/// <summary>
/// 纹理类，支持直接从文件读取纹理
/// </summary>
class Texture2D
{
public:
    //纹理ID
    GLuint ID;
    //纹理大小
    GLuint Width, Height;
    //纹理格式
    GLuint Internal_Format;
    //加载的图片的纹理
    GLuint Image_Format;
    //纹理配置
    GLuint Wrap_S; //S方向的纹理环绕
    GLuint Wrap_T; //T方向的纹理环绕
    GLuint Filter_Min; //近处物体的过滤方式
    GLuint Filter_Max; //远处物体的过滤方式
    //构造器
    Texture2D(char const* path);
    Texture2D();
    //绑定该纹理为当前活动纹理
    void Bind() const;
};
