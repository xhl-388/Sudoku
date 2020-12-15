#include <resource_manager.h>

std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

Shader& ResourceManager::LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name)
{
	Shader target(vShaderFile, fShaderFile);
	if (Shaders.find(name) != Shaders.end())
		std::cerr << "error!:different shaders have the same name" << std::endl;
	Shaders.insert({ name,target });
	return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
	if (Shaders.find(name) == Shaders.end())
		std::cerr << "error!:try to get a shader not exists:" + name << std::endl;
	return Shaders[name];
}

Texture2D& ResourceManager::LoadTexture(const GLchar* file, std::string name)
{
	Texture2D target(file);
	if (Textures.find(name) != Textures.end())
		std::cerr << "error!:different textures have the same name" << std::endl;
	Textures.insert({ name,target });
	return Textures[name];
}

Texture2D& ResourceManager::GetTexture(std::string name)
{
	if (Textures.find(name) == Textures.end())
		std::cerr << "error!:try to get a texture not exist:" + name << std::endl;
	return Textures[name];
}

void ResourceManager::Clear()
{
	for (auto it : Shaders)
		glDeleteProgram(it.second.ID);
	for (auto it : Textures)
		glDeleteTextures(1, &it.second.ID);
}