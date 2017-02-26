#version 150

in vec3 vertexPosition;
in vec2 vertexTexCoords;

out vec2 vertexTextCoordsOut;

uniform mat4 MVP;

void main()
{
    vertexTextCoordsOut = vertexTexCoords;
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
}