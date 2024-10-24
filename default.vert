#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;

layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 aNormal;

out vec3 colour;

out vec2 texCoord;

out vec3 Normal;
out vec3 currentPos;

//Imports camera matrix from the main function
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	currentPos = vec3(model * vec4(aPos, 1.0f));

    gl_Position = camMatrix * vec4(currentPos, 1.0);
    colour = aColour;
    texCoord = aTex;
    Normal = aNormal;

}