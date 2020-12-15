#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"
#include "shader/shader.h"

/// <summary>
/// ������Ⱦ���������Լ���Shader����Ⱦһ������
/// </summary>
class SpriteRenderer
{
public:
    //������
    SpriteRenderer(Shader& shader);
    //������
    ~SpriteRenderer();
    //��Ⱦ��һ������
    void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    //��ɫ��
    Shader shader;
    GLuint quadVAO;
    //����VAO��ؼ�������
    void initRenderData();
};