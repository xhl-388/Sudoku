#pragma once

#include "glad/glad.h"

/// <summary>
/// �����֧࣬��ֱ�Ӵ��ļ���ȡ����
/// </summary>
class Texture2D
{
public:
    //����ID
    GLuint ID;
    //�����С
    GLuint Width, Height;
    //�����ʽ
    GLuint Internal_Format;
    //���ص�ͼƬ������
    GLuint Image_Format;
    //��������
    GLuint Wrap_S; //S�����������
    GLuint Wrap_T; //T�����������
    GLuint Filter_Min; //��������Ĺ��˷�ʽ
    GLuint Filter_Max; //Զ������Ĺ��˷�ʽ
    //������
    Texture2D(char const* path);
    Texture2D();
    //�󶨸�����Ϊ��ǰ�����
    void Bind() const;
};
