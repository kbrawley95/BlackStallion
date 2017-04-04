OBJModel::OBJModel(std::string name, const char* path, std::string texturepath)
{
    texture = new Texture();
    modelShader = new Shader("/textureVS.glsl", "/textureFS.glsl");
    textureID = texture->loadTextureFromFile(texturepath);
    // IndexedModel model = OBJLoader(path).ToIndexedModel();
    ObjLoader::ObjStructure model = ObjLoader::LoadObj(path);

    if (model.vertices.size() == model.uvs.size() && model.uvs.size() == model.normals.size())
    {
        const int VERTS_LEN = model.vertices.size();
        const int INDICES_LEN = model.indices.size();
        vertices.resize(VERTS_LEN);
        indices.resize(INDICES_LEN);

        for (int i = 0; i < VERTS_LEN; i++)
        {
            vertices[i] = {
                model.vertices[i],
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                model.uvs[i],
                model.normals[i]
            };
        }

        for (int i = 0; i < INDICES_LEN; i++)
        {
            indices[i] = model.indices[i];
        }
    }


    init();
}

void OBJModel::init()
{
    //Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    //Create EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    Vertex::AttributeInfo();
}

void OBJModel::render(Camera* renderer)
{
    glUseProgram(modelShader->getShaderProgram());

    //View Matrix
    GLint modelMatrix = glGetUniformLocation(modelShader->getShaderProgram(), "model");
    glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(glm::mat4(gameObject->getTransform()->getModelToWorldMatrix())));

    //View Matrix
    GLint viewMatrix = glGetUniformLocation(modelShader->getShaderProgram(), "view");
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(renderer->getViewMatrix()));

    //Projection Matrix
    GLint projectionMatrix = glGetUniformLocation(modelShader->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(renderer->getProjectionMatrix()));

    //Bind Vertex Array Object to pipeline (Sanity Check)
    glBindTexture(GL_TEXTURE, textureID);

    //CubeMap Texture
    GLint texture0Location = glGetUniformLocation(modelShader->getShaderProgram(), "texture0");
	glUniform1i(texture0Location, 0);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void OBJModel::cleanUp()
{
    glDeleteTextures(1, &textureID);
    glDeleteProgram(modelShader->getShaderProgram());

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}