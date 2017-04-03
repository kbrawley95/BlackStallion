#ifndef _CUBEMAP_H
#define _CUBEMAP_H

class Skybox : public GameObject
{
    public:
        Skybox(std::string name, std::vector<std::string>texturePaths, std::vector<GLenum>textureTargets);
        GLuint loadCubeMap(std::vector<std::string>texturePaths, std::vector<GLenum>textureTargets);
        void bindCubemapToPipeline(GLuint textureID);
        GLuint getTextureID();

        GLuint generateCubeMap();

       
    
    private:
        std::vector<std::string>texturePaths;
        std::vector<GLenum>textureTargets;

        GLuint textureID;
};




#include "../src/skybox.cpp"

#endif