Mesh::Mesh(std::string name, std::string filepath, std::string texturepath) : GameObject(name)
{
    loadModel(filepath);
    textureShader = new Shader("/textureVS.glsl", "/textureFS.glsl");
    textureID = texture->loadTextureFromFile(texturepath);
    assignMeshData(vertices, indices);
    init();
}

void Mesh::loadModel(std::string filepath)
{
    model = new Model(filepath);
}

void Mesh::assignMeshData(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
    if (model->getPositions().size() == model->getTextureCoords().size() && model->getTextureCoords().size() == model->getNormals().size())
    {
        const int VERTS_LEN = model->getPositions().size();
        const int INDICES_LEN = model->getIndices().size();
        vertices.resize(VERTS_LEN);
        indices.resize(INDICES_LEN);

        for (int i = 0; i < VERTS_LEN; i++)
        {
            vertices[i] = {
                model->getPositions()[i],
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                model->getTextureCoords()[i],
                model->getNormals()[i]
            };
        }

        for (int i = 0; i < INDICES_LEN; i++)
        {
            indices[i] = model->getIndices()[i];
        }
    }
}

void Mesh::init()
{
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    //Create Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBufferID);
    //Make the new VBO active (Bind it to pipeline)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //Copy Vertex Data to VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    //Create Element Buffer Object (EBO) for indices
    glGenBuffers(1, &elementBufferID);
    //Make the EBO active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
    //Copy Index data to EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    //Tell the shader that 0 is the Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

    //Tell the shader that 0 is the Colour
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, colour));

    //Tell the shader that 0 is the Texture Coordinates
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uvTextCoords));

    //Tell the shader that 0 is the Normal
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
}

void Mesh::render(Camera* mainCamera)
{
    //Bind Vertex Array Object to pipeline (Sanity Check)
    glBindVertexArray(vertexArrayID);
    glBindTexture(GL_TEXTURE, textureID);

    //Use the specified shader program
    glUseProgram(textureShader->getShaderProgram());

    //View Matrix
    GLint modelMatrix = glGetUniformLocation(textureShader->getShaderProgram(), "model");
    glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(getTransform()->getModelToWorldMatrix()));

    //View Matrix
    GLint viewMatrix = glGetUniformLocation(textureShader->getShaderProgram(), "view");
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(mainCamera->getViewMatrix()))));

    //Projection Matrix
    GLint projectionMatrix = glGetUniformLocation(textureShader->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera->getProjectionMatrix()));

    //CubeMap Texture
    GLint texture0Location = glGetUniformLocation(textureShader->getShaderProgram(), "texture0");
	glUniform1i(texture0Location, 0);

    //Draw vertices data based on index selection values
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void Mesh::cleanUp()
{
    // glDeleteTextures(1, &cubemapTextureID);
    glDeleteProgram(textureShader->getShaderProgram());
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &elementBufferID);
    glDeleteBuffers(1, &vertexArrayID);
}