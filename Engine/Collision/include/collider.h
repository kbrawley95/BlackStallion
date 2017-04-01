#ifndef _COLLIDER_H
#define _COLLIDER_H

class Collider
{
    public:
        Collider();
        void init();

    protected:
        btTransform* transform;
        btMotionState* motion;
        btRigidBody* rigidbody;
        btRigidBody::btRigidBodyConstructionInfo* info;
        btVector3* inertia;
};

#include "../src/collider.cpp"

#endif