OBJLoader::OBJLoader(const char* path)
{
    loadObjModel(path, temp_vertices,temp_uvs,temp_normals);
}

OBJLoader::~OBJLoader()
{

}

std::vector<glm::vec3>OBJLoader::getVertices()
{
    return temp_vertices;
}

std::vector<glm::vec2>OBJLoader::getUVs()
{
   return temp_uvs;
}

std::vector<glm::vec3>OBJLoader::getNormals()
{
   return temp_normals;
}

 
void OBJLoader::loadObjModel(const char* path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals)
{
    FILE* file = fopen(path, "r");

    if(file == NULL)
    {
        printf("Couldn't open the specified file");
        return;
    }

    while(true)
    {
        char charBuffer[128];
        
        //Read the first word of the line
        int firstWord = fscanf(file, "%s", charBuffer);
        if(firstWord == EOF)
        {
            break;  //if end of file, quit loop
        }

        //Parse obj file data for each of the following properties
        if(strcmp(charBuffer, "v")==0){ //Vertices
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if(strcmp(charBuffer, "vt")==0) //UV Textures
        {
            glm::vec2 textCoords;
            fscanf(file, "%f %f\n", &textCoords.x, &textCoords.y);
            temp_uvs.push_back(textCoords);
        }
        else if(strcmp(charBuffer, "vn")==0)   //Normals
        {
            glm::vec3 normals;
            fscanf(file, "%f %f %f\n", &normals.x, &normals.y, &normals.z);
            temp_normals.push_back(normals);
        }
        else if(strcmp(charBuffer, "first")==0)  //Faces
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
            &vertexIndex[0], &uvIndex[0], &normalIndex[0],
            &vertexIndex[1], &uvIndex[1], &normalIndex[1],
            &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            if(matches !=9)
            {
                printf("File can't be read by parser");
                return;
            }

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);

            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);

            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);

        }
        
    }
}
