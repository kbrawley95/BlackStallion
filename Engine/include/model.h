#ifndef _MODEL_H
#define _MODEL_H

class Model
{
    public:
        Model(std::string filepath)
        {
            objLoader = new OBJLoader(filepath, positions, textureCoords, normals);
        }

        std::vector<glm::vec3> getPositions()
        {
            return positions;
        }
        std::vector<glm::vec2> getTextureCoords()
        {
            return textureCoords;
        }
        std::vector<glm::vec3> getNormals()
        {
            return normals;
        }
        std::vector<unsigned int> getIndices()
        {
            return indices;
        }

    private:
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> textureCoords;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        OBJLoader* objLoader;
};

#endif