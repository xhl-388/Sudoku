#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"
#include "shader/shader.h"

/// <summary>
/// 精灵渲染器，根据自己的Shader来渲染一个物体
/// </summary>
class SpriteRenderer
{
public:
    //构造器
    SpriteRenderer(Shader& shader);
    //析构器
    ~SpriteRenderer();
    //渲染出一个材质
    void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    //着色器
    Shader shader;
    GLuint quadVAO;
    //创建VAO相关几何属性
    void initRenderData();
};