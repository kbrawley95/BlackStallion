#ifndef _COLLIDER_H
#define _COLLIDER_H

class Collider
{
    public:
        Collider()
        {
            
        }
        
        ~Collider()
        {
            delete shape;
        }

        btCollisionShape* getShape()
        {
            return shape;
        }

    protected:
        btCollisionShape* shape;
};

#endif
