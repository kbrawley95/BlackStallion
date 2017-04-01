#ifndef _BOX_COLLIDER_H
#define _BOX_COLLIDER_H

class BoxCollider : public Collider
{
    public:
        BoxCollider();
        void init();

    private:
        btBoxShape* box;

};

#include "../src/box_collider.cpp"

#endif