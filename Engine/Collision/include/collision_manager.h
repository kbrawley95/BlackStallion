#ifndef _COLLISION_H
#define _COLLISION_H

class CollisionManager
{
    public:
        CollisionManager();

        void init();
        void update(float &delaTime);
        void cleanUp();

        static btDynamicsWorld* getWorld();
        static void addRigidbodyToList(btRigidBody* newBody);
      

    private:
        static btDynamicsWorld* world;
        static std::vector<btRigidBody*>rigidBodies;

        btDispatcher* dispatcher;
        btCollisionConfiguration* collisionConfig;
        btBroadphaseInterface* broadphase;
        btConstraintSolver* solver;
};

btDynamicsWorld* CollisionManager::world;
std::vector<btRigidBody*> CollisionManager::rigidBodies;

#include "../src/collision_manager.cpp"

#endif