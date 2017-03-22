#version 150

in vec3 vertexPosition;

// uniform mat4 MVP;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexTexCoords;


void main()
{
	vec4 VP_Pos = projection * view * vec4(vertexPosition, 1.0);
	gl_Position = VP_Pos.xyww;
	vertexTexCoords = vertexPosition;
}
