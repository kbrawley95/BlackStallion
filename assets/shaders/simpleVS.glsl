#version 450

in vec3 vertexPosition;
in vec4 vertexColour;
out vec4 colour; 

uniform mat4 MVP;
uniform mat4 trans;

void main()
{
    gl_Position = MVP *  trans * vec4(vertexPosition,1.0);
    colour = vertexColour;
}