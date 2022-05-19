#include "myGL_Texture.hpp"
#include <stb/stb_image.hpp>

myGL_Texture::myGL_Texture(GLenum bindTarget):
	BIND_TARGET(bindTarget)
{
	glGenTextures(1, &ID);
	glBindTexture(BIND_TARGET, ID);
}

void myGL_Texture::UnBind()
{
	glBindTexture(BIND_TARGET, 0);
}

void myGL_Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

void myGL_Texture::Bind()
{
	glBindTexture(BIND_TARGET, ID);
}

myGL_Texture & myGL_Texture::Generate(const char * filename)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char *bytes = stbi_load(filename, &widthImg, &heightImg, &numColCh, 0);
	GLenum format;
	switch (numColCh) {
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	case 2:
		format = GL_RGB16;
		break;
	case 1:
		format = GL_RGB8;
		break;
	default:
		std::cerr << "Not such the immage format\n";
		std::cerr << "Only support => GL_RGB GL_RGBA GL_RGB16 GL_RGB8\n";
        exit(EXIT_FAILURE);
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(BIND_TARGET, 0, format, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, bytes);
	stbi_image_free(bytes);
	glGenerateMipmap(BIND_TARGET);
	return *this;
}

myGL_Texture & myGL_Texture::Parameteri(GLenum key, GLenum value)
{
	glTexParameteri(BIND_TARGET, key, value);
	return *this;
}

