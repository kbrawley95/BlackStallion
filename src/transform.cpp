#include "../include/transform.h"

Transform::Transform()
{
    worldMatrix=translate(mat4(1.0f), vec3(0.0f,0.0f,0.0f));
    viewMatrix=lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix=perspective(45.0f, 640.0f/480.0f, 0.1f, 100.0f);
}

Transform::~Transform()
{
    
}

mat4 Transform::getMVPMatrix()
{
    return worldMatrix * viewMatrix * projectionMatrix;    
}
