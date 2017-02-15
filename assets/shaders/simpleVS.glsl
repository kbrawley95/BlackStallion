#version 450

in layout(location=0, vec3 vertexPostion);

uniform mat4 MVP;

void main()
{
    glPosition=MVP * vec4(vertexPostion,1.0f);
}