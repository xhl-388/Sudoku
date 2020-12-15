#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/// <summary>
/// ��ɫ���֧࣬�ִ��ļ���ȡ��ɫ��
/// </summary>
class Shader
{
public:
	unsigned int ID;
	//��ָ���ļ���ȡ������������ɫ����Ƭ����ɫ��
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader();
	//���������ɫ��
	void use();
	//һЩ���߷���
	void setBool(const std::string& name, bool value) const;
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const;
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const;
	void setFloat2(const std::string& name, float value1, float value2) const;
	void setFloat3(const std::string& name, float value1, float value2, float value3) const;
	void setVec3(const std::string& name,const glm::vec3& vec);
	void setVec3(const std::string& name, float value1, float value2, float value3) const;
	void setMat4(const std::string& name, const glm::mat4& mat);
private:
	//�����ɫ���Ƿ��б������
	void checkCompileErrors(unsigned int shader, std::string type);
};
