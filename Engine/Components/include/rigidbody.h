#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

class Rigidbody : public Component
{
    public:
        Rigidbody(Collider* newCollider, float newMass,
        glm::vec3 relativePosition, glm::quat relativeRotation, glm::vec3 relativeScale);
        ~Rigidbody();

        btRigidBody* getRigidbody();
        btTransform getTransform();
        btMotionState* getMotion();
<<<<<<< HEAD:Engine/Components/include/rigidbody.h

        void update();
=======
        btVector3 getInertia();
        
>>>>>>> parent of 6c7ae85... Bullet Physics:Engine/Collision/include/rigidbody.h
        
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

#include "../../Components/src/rigidbody.cpp"

#endif