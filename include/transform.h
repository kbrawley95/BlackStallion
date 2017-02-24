#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Common.h"

class Transform
{
    public:

    

    //OpenGL Vertex Transformations
    glm::mat4 getMVPMatrix();
    glm::mat4 getModeltoWorldMatrix();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    //Translation Vectors
    glm::vec3 moveForward();
    glm::vec3 moveUp();
    glm::vec3 moveRight();

    //Basic Vector Transformations
    glm::vec3 getPosition();
    glm::vec3 getScale();
    glm::vec3 getRotation();


    Transform();
    ~Transform();

    static float ToRadians(float d){
		return (d / 180.0f) * glm::pi<float>();
	}

	static float ToDegrees(float r){
		return (r / glm::pi<float>()) * 180.0f;
	}
    

    private:
    glm::mat4x4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

};

#endif 