#ifndef _COLLISION_H
#define _COLLISION_H

class CollisionManager
{
    public:
        CollisionManager();

        void init();
        void update(float &delaTime);
        void cleanUp();

        void addRigidBodyToWorld(btRigidBody* body);
        btDynamicsWorld* getWorld();
      
        btDynamicsWorld* world;
        btDispatcher* dispatcher;
        btCollisionConfiguration* collisionConfig;
        btBroadphaseInterface* broadphase;
        btConstraintSolver* solver;

    private:
        std::vector<btRigidBody*>rigidBodies;
};

#include "../src/collision_manager.cpp"

#endif