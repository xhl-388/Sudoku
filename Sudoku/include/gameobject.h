#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include "texture.h"
#include "spriterenderer.h"


//每个游戏实体的基类
class GameObject
{
public:
    //物体状态
    glm::vec2   Position, Size;
    glm::vec3   Color;
    GLfloat     Rotation;
    //材质
    Texture2D   Sprite;
    //构造器
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
    //渲染该物体
    virtual void Draw(SpriteRenderer& renderer);
};

/// <summary>
/// 棋子类
/// </summary>
class NumberObject :public GameObject
{
private:
    //棋子特有的编号0~9,0代表不存在
    int Number;
public:
    //构造器
    NumberObject();
    NumberObject(glm::vec2 pos, glm::vec2 size,glm::vec3 color = glm::vec3(1.0f));
    NumberObject(int number, glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
    //获得编号
    unsigned int getNumber() const { return Number; }
    //设置编号（同时会更新材质）
    void setNumber(int target);
};
