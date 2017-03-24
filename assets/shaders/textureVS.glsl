#version 150

in vec3 vertexPosition;
in vec2 vertexTexCoords;

out vec2 vertexTextCoordsOut;

out mat4 MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    MVP = projection * view * model;
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
    vertexTextCoordsOut = vertexTexCoords;
}