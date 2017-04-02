#ifndef _COLLIDER_H
#define _COLLIDER_H

class Collider
{
    public:
        Collider();
        void init();

        btTransform* getTransform();
        btMotionState* getMotion();
        btRigidBody* getRigidbody();
        btRigidBody::btRigidBodyConstructionInfo* getInfo();
        btVector3* getInertia();

    protected:
        btTransform* transform;
        btMotionState* motion;
        btRigidBody* rigidbody;
        btRigidBody::btRigidBodyConstructionInfo* info;
        btVector3* inertia;
};

#include "../src/collider.cpp"

#endif