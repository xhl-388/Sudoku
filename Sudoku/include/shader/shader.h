#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/// <summary>
/// 着色器类，支持从文件获取着色器
/// </summary>
class Shader
{
public:
	unsigned int ID;
	//从指定文件读取并创建顶点着色器和片段着色器
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader();
	//激活这个着色器
	void use();
	//一些工具方法
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
	//检查着色器是否有编译错误
	void checkCompileErrors(unsigned int shader, std::string type);
};
