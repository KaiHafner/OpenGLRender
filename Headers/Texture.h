#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
	public:
		GLuint ID;
		const char* type;
		GLuint unit;

		Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

		void texUnit(Shader& shader, const char* uniform, GLuint unit); // Assigns a texture unit to a texture
		void Bind();	// Binds a texture
		void Unbind();	// Unbinds a texture
		void Delete();	// Deletes a texture
};
#endif