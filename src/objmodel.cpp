ObjModel::ObjModel(const char* path)
{
    objectLoader = new OBJLoader();
    objectLoader->loadObjModel(path, vertices, uvs, normals);
    textureShader = new Shader("/textureVS.glsl", "/textureFS.glsl");
    initModel();
}

ObjModel::~ObjModel()
{
    
}

std::vector<glm::vec3> ObjModel::getVertices()
{
    return vertices;
}
std::vector<glm::vec2> ObjModel::getUVs()
{
    return uvs;
}
std::vector<glm::vec3> ObjModel::getNormals()
{
    return normals;
}

void ObjModel::initModel()
{
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    //Create Vertex vertexBuffer
    glGenBuffers(1, &vertexBufferID);
    //Make the new VBO active (Bind it to pipeline)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //Copy Vertex Data to VBO
    std::vector<glm::vec3>vertices;
    vertices = getVertices();
    std::cout<<"Number of Vertices: " <<vertices.size() << std::endl;
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices, GL_STATIC_DRAW);

    // //Create Elements (Index)Buffer
    // glGenBuffers(1, &elementsBufferID);
    // //Make the EBO active
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferID);
    // //Copy Index data to the EBO
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, Cube::m_indices.size() * sizeof(GLuint), &Cube::m_indices[0], GL_STATIC_DRAW);

    //Tell the shader that 0 is the position 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

    //Tell the shader that 1 is the colour 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, colour));

    //Tell the shader that 2 is the texture coordinates 
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uvTextCoords));
}
void ObjModel::render(Camera* mainCamera)
{
    //Bind Vertex Array Object to pipeline (Sanity Check)
    glBindVertexArray(vertexArrayID);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureID);

    //Use the specified shader program
    glUseProgram(textureShader->getShaderProgram());

    //Model Matrix 
    GLint modelMatrix = glGetUniformLocation(textureShader->getShaderProgram(),"model");
    glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera->attached_transform->getModeltoWorldMatrix()));

    //View Matrix
    GLint viewMatrix = glGetUniformLocation(textureShader->getShaderProgram(), "view");
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera->getViewMatrix()));

    //Projection Matrix
    GLint projectionMatrix = glGetUniformLocation(textureShader->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera->getProjectionMatrix()));

    // //CubeMap Texture
    // GLint texture0Location = glGetUniformLocation(skyboxShader->getShaderProgram(), "cubeTexture");
	// glUniform1i(texture0Location, 0);

    //Draw vertices data based on index selection values
    glDrawArrays(GL_TRIANGLES, getVertices().size(), GL_UNSIGNED_INT);
}