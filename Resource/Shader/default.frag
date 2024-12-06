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
uniform sampler2D tex1;

uniform vec4 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
	//used in two variables so I calculate it here (stops it needing to be done twice)
	vec3 lightVec = lightPos - currentPos;

	//Intensity of light based on distance
	float dist = length(lightVec);
	float a = 1;
	float b = 0.04;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	//ambient lighting
	float ambient = 0.20f;

	//diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular lighting
	float specularLight = 0.75f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColour;
}

vec4 directLight()
{
	//ambient lighting
	float ambient = 0.20f;

	//diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular lighting
	float specularLight = 0.75f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse + ambient) + texture(tex1, texCoord).r * specular) * lightColour;
}

vec4 spotLight()
{
	//Controls the size of lit area (cone)
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	//ambient lighting
	float ambient = 0.20f;

	//diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currentPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular lighting
	float specularLight = 0.75f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	//Calculates the intensity of the currentPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColour;
}

void main()
{
	//outputs final color
	FragColour = directLight();
}