#ifndef _OBJMODEL_H
#define _OBJMODEL_H

class ObjModel
{
    public:
        ObjModel(const char* path);
        ~ObjModel();

        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec2> getUVs();
        std::vector<glm::vec3> getNormals();

        void initModel();
        void render(Camera* mainCamera);

    private:
        OBJLoader* objectLoader;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;

         //Buffer objects
        GLuint vertexArrayID;
        GLuint vertexBufferID;
        GLuint elementsBufferID;

        //Shader
        Shader* textureShader;
        
};

#include "../src/objmodel.cpp"

#endif