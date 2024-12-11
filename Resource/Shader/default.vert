#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColour;
layout (location = 3) in vec2 aTex;


//Outputs for the Fragment Shader
out vec3 currentPos;
out vec3 Normal;
out vec3 colour;
out vec2 texCoord;

//Imports camera matrix from the main function
uniform mat4 camMatrix;

uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
    //Calculates posistion
	currentPos = vec3(model * translation * rotation * scale * vec4(aPos, 1.0f));
    Normal = aNormal;
    colour = aColour;
    texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;;

    //Outputs position of all vertices
    gl_Position = camMatrix * vec4(currentPos, 1.0);

}