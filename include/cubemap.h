#ifndef _CUBEMAP_H
#define _CUBEMAP_H

class Cubemap
{
    public:
        Cubemap(const string& directory,const std::string& posX,const std::string& negX,const std::string& posY, const std::string& negY,const std::string& posZ,const std::string& negZ);
        bool loadCubemap();
        void bindCubemapToPipeline(GLenum textureUnit);

    private:
        std::string m_fileNames[6];
        GLuint m_textureID;

        GLenum m_cubeMapFaceTypes[6]=
        {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X, 
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };
 
};

#include "../src/cubemap.h"

#endif