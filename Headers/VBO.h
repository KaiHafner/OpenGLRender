#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex 
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 colour;
	glm::vec3 texUV;
};

class VBO 
{
	public:
		GLuint ID;
		VBO(std::vector<Vertex>& vertices);

		void Bind();
		void Unbind();
		void Delete();
};

#endif