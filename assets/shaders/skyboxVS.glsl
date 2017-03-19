#version 150

in vec3 vertexPosition;

uniform mat4 WVP;

out vec3 vertexTexCoords;


void main()
{
	vec4 WVP_Pos = WVP * vec4(vertexPosition, 1.0f);
	gl_Position = WVP_Pos.xyww;
	vertexTexCoords = vertexPosition;
}
