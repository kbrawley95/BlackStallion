#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

class Rigidbody
{
    public:
        Rigidbody();
        ~Rigidbody();

        btRigidBody* getRigidbody();
        btTransform* getTransform();
        btMotionState* getMotion();
        btRigidBody::btRigidBodyConstructionInfo* getInfo();
        btVector3* getInertia();
        
        
    private:
        //Collider Type
        Collider* collider;

        //Bullet rigidybody instance
        btRigidBody* rigidbody;

        //Transform realtive to Gameobject associated with
        btTransform* transform;
        
        //Mass of the GameObject (Simulated by rigidbody)
        float mass;

        //Responsible for enacting forces on the rigidbody
        btMotionState* motion;

        //Info use when creating rigidbody
        btRigidBody::btRigidBodyConstructionInfo* info;

        //Inertia is the resistance to change in state of motion
        btVector3* inertia;

        //Transform values
        btVector3 position;
        btQuaternion rotation;
        
};

#include "../src/rigidbody.cpp"

#endif