#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

class Rigidbody
{
    public:
        Rigidbody(Collider* newCollider, glm::vec3 relativePosition, glm::quat relativeRotation, glm::vec3 relativeScale);
        ~Rigidbody();

        btRigidBody* getRigidbody();
        btMotionState* getMotion();

        void update(GameObject* gameObject);
        
    private:
        //Collider Type
        Collider* collider = NULL;

        //Bullet rigidybody instance
        btRigidBody* rigidbody = NULL;

        //Mass of the GameObject (Simulated by rigidbody)
        float mass = 1.0f;

        //Responsible for enacting forces on the rigidbody
        btMotionState* motion = NULL;

        //Transform values
        btVector3 position;
        btQuaternion rotation;
        
};

#include "../src/rigidbody.cpp"

#endif