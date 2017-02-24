#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Common.h"

class Transform
{
    public:

    //Translation Vectors
    glm::vec3 Forward();
    glm::vec3 Up();
    glm::vec3 Right();

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
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

};

#endif 