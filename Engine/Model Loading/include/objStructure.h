#ifndef _OBJSTRUCTURE_H
#define _OBJSTRUCTURE_H

struct ObjStructure
{
    std::vector<glm::vec3>          vertices;
    std::vector<glm::vec2>          uvs;
    std::vector<glm::vec3>          normals;

    std::vector<uint32_t>           indices;
};


#endif
