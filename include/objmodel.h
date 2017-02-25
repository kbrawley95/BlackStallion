#ifndef _OBJLOADER
#define _OBJLOADER

class OBJModel
{
    public:

    OBJModel();
    ~OBJModel();

    private:

    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec2> uvTextCoords;
    std::vector<glm::vec3> normalVectors;

    vector<glm::vec3>parseVertices(std::string pathName);
    vector<glm::vec2>parseTextures(std::string pathName);
    vector<glm::vec3>parseNormals(std::string pathName);

};

#include "../src/objmodel.cpp"

#endif