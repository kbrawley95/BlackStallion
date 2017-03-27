#ifndef _OBJLOADER_H
#define _OBJLOADER_H

class OBJLoader
{   
    public:
        OBJLoader(std::string filepath, std::vector<glm::vec3>&vertexPositions, std::vector<glm::vec2>&textCoords, std::vector<glm::vec3>&normalVectors);

        void loadModelDataFromFile(std::string filepath, std::vector<glm::vec3>&vertexPositions, std::vector<glm::vec2>&textCoords, std::vector<glm::vec3>&normalVectors);

        static void parseDataToArray(const char* &charBuffer, std::vector<std::string> &array, char regs[]);
        static void parseVector2(std::vector<std::string> array, std::vector<glm::vec2> &output);
        static void parseVector3(std::vector<std::string> array, std::vector<glm::vec3> &output);

        static void printArrayContents(std::string arrayName, std::vector<std::string> array);
        static void printArrayContents(std::string arrayName, std::vector<glm::vec2> &array);
        static void printArrayContents(std::string arrayName, std::vector<glm::vec3> &array);



    private:
        std::vector<std::string> positions;
        std::vector<std::string> uvs;
        std::vector<std::string> normals;
        std::vector<std::string> faces;
      

       

};

// class Model
// {
//     public:
//         Model();

//     private:
//         std::vector<glm::vec3> positions;
//         std::vector<glm::vec4> colours;
//         std::vector<glm::vec2> textureCoords;
//         std::vector<glm::vec3> normals;

       
// };

#include "../src/objloader.cpp"

#endif