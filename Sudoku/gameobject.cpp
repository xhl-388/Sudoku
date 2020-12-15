#include <gameobject.h>
#include <resource_manager.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject()
	: Position(0, 0), Size(1, 1), Color(1.0f), Rotation(0.0f), Sprite() { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
	: Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite) { }

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

NumberObject::NumberObject() :GameObject()
{
	setNumber(0);
}

NumberObject::NumberObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color)
{
	Position = pos;
	Size = size;
	Color = color;
	setNumber(0);
}

NumberObject::NumberObject(int number, glm::vec2 pos, glm::vec2 size, glm::vec3 color)
{
	Position = pos;
	Size = size;
	Color = color;
	setNumber(number);
}

void NumberObject::setNumber(int target)
{
	Number = target;
	if (target >= 0 && target <= 9)
		Sprite = ResourceManager::GetTexture(std::string("Number") + std::string(1, target + '0'));
	else
		std::cerr << "Invalid Number Set!:" << target << std::endl;
}