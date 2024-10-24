#version 330 core

out vec4 FragColour;

in vec3 colour;
in vec2 texCoord;

in vec3 Normal;
in vec3 currentPos;

//Imports
uniform sampler2D tex0;
uniform vec4 lightColour;
uniform vec3 lightPos;

void main()
{
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currentPos);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	FragColour = texture(tex0, texCoord) * lightColour * diffuse;
}