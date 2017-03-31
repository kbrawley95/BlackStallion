UI::UI(std::string name, std::string filepath, int fontSize, std::string caption) : GameObject(name)
{
    uiShader = new Shader("/textureVS.glsl", "/textureFS.glsl");
    textureID = texture->loadTextureFromFont(filepath, fontSize, caption);
    init();
}

void UI::init()
{
    m_vertices=
    {
       //Position                    //Colour                           //Texture Coordinates
        {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}
    };
    
    //Create & Bind Vertex Array Object (VAO)
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    //Create  Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBufferID);
    //Make the new VBO active (Bind it to pipeline)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //Copy Vertex Data to VBO
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    //Tell the shader that 0 is the position 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

    //Tell the shader that 1 is the colour
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, colour));
    
    //Tell the shader that 2 is the uv texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uvTextCoords));

}

void UI::render(Camera* mainCamera)
{
    //Enables blending and set up a Blend Function (for alpha channel)
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Bind Texture to pipeline
    glBindTexture(GL_TEXTURE, textureID);

    //Use the specified shader program
	glUseProgram(uiShader->getShaderProgram());

    //View Matrix
    GLint modelMatrix = glGetUniformLocation(uiShader->getShaderProgram(), "model");
    glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(getTransform()->getModelToWorldMatrix()));

    //View Matrix
    GLint viewMatrix = glGetUniformLocation(uiShader->getShaderProgram(), "view");
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera->getViewMatrix()));

    //Projection Matrix
    GLint projectionMatrix = glGetUniformLocation(uiShader->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera->getProjectionMatrix()));

    //CubeMap Texture
    GLint texture0Location = glGetUniformLocation(uiShader->getShaderProgram(), "texture0");
	glUniform1i(texture0Location, 0);

    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());


}

void UI::cleanUp()
{
    glDeleteTextures(1, &textureID);
}