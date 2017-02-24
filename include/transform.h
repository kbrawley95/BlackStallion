#ifndef _TRANSFORM_H
#define _TRANSFORM_H

class Transform
{
    public:

    //CONSTRUCTOR/DECONSTRUCTOR
    Transform();
    ~Transform();

    //Translation Vectors
    glm::vec3 forward();
    glm::vec3 up();
    glm::vec3 right();

    //Basic Vector Transformations
    glm::vec3 getPosition();
    glm::vec3 getScale();
    glm::vec3 getRotation(); 

    glm::vec3 setPosition(float speed, float deltaTime);
    glm::vec3 setScale(glm::vec3);
    glm::vec3 setRotation(glm::vec3); 



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

#include "../src/transform.cpp"

#endif 