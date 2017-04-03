#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

class Rigidbody
{
    public:
        Rigidbody(Collider* newCollider, float newMass,
        glm::vec3 relativePosition, glm::quat relativeRotation, glm::vec3 relativeScale);
        ~Rigidbody();

        btRigidBody* getRigidbody();
        btTransform getTransform();
        btMotionState* getMotion();
        btVector3 getInertia();
        
        
    private:
        //Collider Type
        Collider* collider;

        //Bullet rigidybody instance
        btRigidBody* rigidbody;

        //Transform realtive to Gameobject associated with
        btTransform transform;
        
        //Mass of the GameObject (Simulated by rigidbody)
        float mass;

        //Responsible for enacting forces on the rigidbody
        btMotionState* motion;

        //Inertia is the resistance to change in state of motion
        btVector3 inertia;

        //Transform values
        btVector3 position;
        btQuaternion rotation;
        
};

#include "../src/rigidbody.cpp"

#endif