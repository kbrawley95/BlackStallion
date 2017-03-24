OBJLoader::OBJLoader()
{

}

OBJLoader::~OBJLoader()
{

}

bool OBJLoader::loadObjModel(const char* path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals)
{
    FILE* file = fopen(path, "r");

    if(file == NULL)
    {
        printf("Couldn't open the specified file");
        return false;
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
                return false;
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

        //For each vertex of each triangle
        for(unsigned int i=0; i<vertexIndices.size(); i++)
        {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex-1];
            out_vertices.push_back(vertex);
        }

        //For each uvcoord of each triangle
        for(unsigned int i=0; i<uvIndices.size(); i++)
        {
            unsigned int uvcoords = uvIndices[i];
            glm::vec2 uv = temp_uvs[uvcoords-1];
            out_uvs.push_back(uv);
        }

        //For each normal of each triangle
        for(unsigned int i=0; i<normalIndices.size(); i++)
        {
            unsigned int normalIndex = normalIndices[i];
            glm::vec3 normal = temp_normals[normalIndex-1];
            out_vertices.push_back(normal);
        }

        return false;
    }

    return true;
}