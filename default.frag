#version 330 core

out vec4 FragColour;

in vec3 colour;

in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	FragColour = texture(tex0, texCoord);
}