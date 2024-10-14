#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
	public:
		//Stores the main vectors of the camera
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		//Prevents the camera from jumping arouynd when first clicking LMB
		bool firstClick = true;

		//Stores the width and height of the window
		int width;
		int height;

		//Adjusts the speed and sens of camera
		float speed = 0.01f;
		float sens = 100.0f;

		//Constructor to set up initial values
		Camera(int width, int height, glm::vec3 position);

		// Updates and exports the camera matrix to the Vertex Shader
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
		// Handles camera inputs
		void Inputs(GLFWwindow* window);
};

#endif