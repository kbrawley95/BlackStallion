#version 150

in vec3 vertexTexCoords;

out vec4 FragColor;

uniform samplerCube cubeTexture;

void main()
{
	FragColor = texture(cubeTexture, vertexTexCoords);
	//FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
