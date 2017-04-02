#ifndef _COLLISION_H
#define _COLLISION_H

class CollisionManager
{
    public:
        CollisionManager();

        void init();
        void update(float &delaTime);
        void cleanUp();
        
      
        btDynamicsWorld* world;
        btDispatcher* dispatcher;
        btCollisionConfiguration* collisionConfig;
        btBroadphaseInterface* broadphase;
        btConstraintSolver* solver;

    private:
};

#include "../src/collision_manager.cpp"

#endif