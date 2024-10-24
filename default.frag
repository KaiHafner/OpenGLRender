#version 330 core

//Outputs colours in RGBA
out vec4 FragColour;

//Imports from Vertex Shader
in vec3 colour; 
in vec2 texCoord;
in vec3 Normal;
in vec3 currentPos;

//Imports from main function
uniform sampler2D tex0;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	//ambient lighting
	float ambient = 0.20f;

	//diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currentPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	//outputs final color
	FragColour = texture(tex0, texCoord) * lightColour * (diffuse + ambient + specular);
}