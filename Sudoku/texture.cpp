#include <iostream>
#include "stb_image.h"
#include <texture.h>

Texture2D::Texture2D()
{
	ID = 0;
}

Texture2D::Texture2D(char const* path)
	: Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
	glGenTextures(1, &this->ID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		if (nrComponents == 1)
			this->Image_Format = GL_RED;
		else if (nrComponents == 3)
			this->Image_Format = GL_RGB;
		else if (nrComponents == 4)
			this->Image_Format = GL_RGBA;

		this->Width = width;
		this->Height = height;

		glBindTexture(GL_TEXTURE_2D, this->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, this->Image_Format, this->Width, this->Height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}