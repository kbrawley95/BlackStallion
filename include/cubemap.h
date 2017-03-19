#ifndef _CUBEMAP_H
#define _CUBEMAP_H

class Cubemap
{
    public:
        Cubemap(std::string texturePaths[], GLuint textureTargets[]);
        bool loadCubeMap(std::string texturePaths[], GLuint textureTargets[]);
        void bindToCubemapToPipeline();
    
    private:
       std::string texturePaths[6];

       GLenum textureTargets[6]=
       {    /*===TEXTURE TARGET====*/           /*====ORIENTATION===*/
           GL_TEXTURE_CUBE_MAP_POSITIVE_X,       //Right
           GL_TEXTURE_CUBE_MAP_NEGATIVE_X,       //Left
           GL_TEXTURE_CUBE_MAP_POSITIVE_Y,       //Top
           GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,       //Bottom
           GL_TEXTURE_CUBE_MAP_POSITIVE_Z,       //Back
           GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,       //Front
       };

       GLuint textureID;
};


#include "../src/cubemap.h"

#endif