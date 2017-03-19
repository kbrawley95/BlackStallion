#version 150

in vec3 vertexPosition;

uniform mat4 MVP;

out vec3 vertexTexCoords;


void main()
{
	vec4 MVP_Pos = MVP * vec4(vertexPosition, 1.0f);
	gl_Position = MVP_Pos.xyww;
	vertexTexCoords = vertexPosition;
}
