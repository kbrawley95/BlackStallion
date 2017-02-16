#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Common.h"

class Transform
{
    public:
    mat4 getMVPMatrix();

    Transform();
    ~Transform();


    private:
    mat4 worldMatrix;
    mat4 viewMatrix;
    mat4 projectionMatrix;

};

#endif 