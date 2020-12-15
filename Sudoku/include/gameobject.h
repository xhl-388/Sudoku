#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include "texture.h"
#include "spriterenderer.h"


//ÿ����Ϸʵ��Ļ���
class GameObject
{
public:
    //����״̬
    glm::vec2   Position, Size;
    glm::vec3   Color;
    GLfloat     Rotation;
    //����
    Texture2D   Sprite;
    //������
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
    //��Ⱦ������
    virtual void Draw(SpriteRenderer& renderer);
};

/// <summary>
/// ������
/// </summary>
class NumberObject :public GameObject
{
private:
    //�������еı��0~9,0��������
    int Number;
public:
    //������
    NumberObject();
    NumberObject(glm::vec2 pos, glm::vec2 size,glm::vec3 color = glm::vec3(1.0f));
    NumberObject(int number, glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
    //��ñ��
    unsigned int getNumber() const { return Number; }
    //���ñ�ţ�ͬʱ����²��ʣ�
    void setNumber(int target);
};
