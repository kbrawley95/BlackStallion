#ifndef _OBJLOADER
#define _OBJLOADER

class OBJLoader
{
    public:

    OBJLoader();
    ~OBJLoader();

    bool loadObjModel(const char* path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals);
  

    private:
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

};

#include "../src/objloader.cpp"

#endif