#ifndef _COLLISION_H
#define _COLLISION_H

class CollisionManager
{
    public:
        CollisionManager();

        void init();
        void update(float &delaTime);
        void cleanUp();

        static void addRigidBodyToWorld(btRigidBody* newRigidbody);
        btDynamicsWorld* getWorld();
      
        static btDynamicsWorld* world;
        btDispatcher* dispatcher;
        btCollisionConfiguration* collisionConfig;
        btBroadphaseInterface* broadphase;
        btConstraintSolver* solver;

    private:
        static std::vector<btRigidBody*>rigidBodies;
};

btDynamicsWorld* CollisionManager::world;
std::vector<btRigidBody*>CollisionManager::rigidBodies;

#include "../src/collision_manager.cpp"

#endif