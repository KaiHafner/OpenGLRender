#version 330 core

out vec4 FragColour;

uniform vec4 lightColour;

void main()
{
	FragColour = lightColour;
}