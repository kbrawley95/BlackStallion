#ifndef _CUBEMAP_H
#define _CUBEMAP_H

class Cubemap
{
    public:
        Cubemap(std::vector<std::string>texturePaths, std::vector<GLenum>textureTargets);
        GLuint loadCubeMap(std::vector<std::string>texturePaths, std::vector<GLenum>textureTargets);
        void bindCubemapToPipeline(GLuint textureID);
        GLuint getTextureID();
    
    private:
        std::vector<std::string>texturePaths;
        std::vector<GLenum>textureTargets;

        GLuint textureID;
};




#include "../src/cubemap.cpp"

#endif