OBJModel::OBJModel(std::string name, const char* path, std::string texturepath) : GameObject(name)
{
    modelShader = new Shader("/textureVS.glsl", "/textureVS.glsl");
    textureID = texture->loadTextureFromFile(texturepath);
	bool res = objLoader ->loadOBJ(path, vertices, uvs, normals);

    std::cout<<"Vertices: " <<vertices.size()<<std::endl;
    std::cout<<"UVS: " <<uvs.size()<<std::endl;
    std::cout<<"Normals: " <<normals.size()<<std::endl;
}

void OBJModel::init()
{   
    for(int i = 0; i<vertices.size(); i++)
    {
        m_vertices[i]=
        {
            vertices[i],
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            uvs[i]
        };
    }

    //Create & Bind Vertex Array Object (VAO)
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    //Create  Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBufferID);
    //Make the new VBO active (Bind it to pipeline)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //Copy Vertex Data to VBO
     glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    // //Create Element Buffer Object (EBO)
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

void OBJModel::render(Camera* mainCamera)
{
    //Bind Vertex Array Object to pipeline (Sanity Check)

    glBindTexture(GL_TEXTURE, textureID);

    //View Matrix
    GLint modelMatrix = glGetUniformLocation(modelShader->getShaderProgram(), "model");
    glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(getTransform()->getModelToWorldMatrix()));

    //View Matrix
    GLint viewMatrix = glGetUniformLocation(modelShader->getShaderProgram(), "view");
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(mainCamera->getViewMatrix()))));

    //Projection Matrix
    GLint projectionMatrix = glGetUniformLocation(modelShader->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera->getProjectionMatrix()));

    //CubeMap Texture
    GLint texture0Location = glGetUniformLocation(modelShader->getShaderProgram(), "texture0");
	glUniform1i(texture0Location, 0);


    glBindVertexArray(vertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);
}