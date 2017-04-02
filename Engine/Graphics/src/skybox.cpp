Skybox::Skybox(std::string name) : GameObject(name)
{
    skyboxShader = new Shader("/skyboxVS.glsl", "/skyboxFS.glsl");
    cubemapTextureID = generateCubeMap();
    initSkybox();
}

GLuint Skybox::generateCubeMap()
{
    GLuint textureMap = 0;
    //Load Cubemap Textures
    texturePaths.push_back("assets/textures/CloudyLightRays/right.png");
    texturePaths.push_back("assets/textures/CloudyLightRays/left.png");
    texturePaths.push_back("assets/textures/CloudyLightRays/up.png");
    texturePaths.push_back("assets/textures/CloudyLightRays/down.png");
    texturePaths.push_back("assets/textures/CloudyLightRays/back.png");
    texturePaths.push_back("assets/textures/CloudyLightRays/front.png");
    
                            /*===TEXTURE TARGET====*/         /*====ORIENTATION===*/
    textureTargets.push_back(GL_TEXTURE_CUBE_MAP_POSITIVE_X       /*Right*/);
    textureTargets.push_back(GL_TEXTURE_CUBE_MAP_NEGATIVE_X       /*Left*/);
    textureTargets.push_back(GL_TEXTURE_CUBE_MAP_POSITIVE_Y       /*Top*/);
    textureTargets.push_back(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y       /*Bottom*/);
    textureTargets.push_back(GL_TEXTURE_CUBE_MAP_POSITIVE_Z       /*Back*/);
    textureTargets.push_back(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z       /*Front*/);

    cubemap = new Cubemap(texturePaths, textureTargets);
    return textureMap = cubemap->getTextureID();
}

void Skybox::initSkybox()
{
    //Create & Bind Vertex Array Object (VAO)
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    //Create  Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBufferID);
    //Make the new VBO active (Bind it to pipeline)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //Copy Vertex Data to VBO
    glBufferData(GL_ARRAY_BUFFER, Cube::m_vertices.size() * sizeof(Vertex), &Cube::m_vertices[0], GL_STATIC_DRAW);

    //Create Element Buffer Object (EBO)
    glGenBuffers(1, &elementsBufferID);
    //Make the EBO active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferID);
    //Copy Index data to the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Cube::m_indices.size() * sizeof(GLuint), &Cube::m_indices[0], GL_STATIC_DRAW);

    //Tell the shader that 0 is the position 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
}

void Skybox::render(Camera* mainCamera)
{
    //Disable Depth Mask
    glDepthMask(GL_FALSE);
 
    //Switch on Alpha Blending
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Bind Vertex Array Object to pipeline (Sanity Check)
    glBindVertexArray(vertexArrayID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureID);

    //Use the specified shader program
    glUseProgram(skyboxShader->getShaderProgram());

    //Projection Matrix
    GLint projectionMatrix = glGetUniformLocation(skyboxShader->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera->getProjectionMatrix()));

    glm::mat4 converted_view_matrix = mainCamera->getViewMatrix();
    converted_view_matrix[3][0] = 0;
    converted_view_matrix[3][1] = 0;
    converted_view_matrix[3][2] = 0;

    //View Matrix
    GLint viewMatrix = glGetUniformLocation(skyboxShader->getShaderProgram(), "view");
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(converted_view_matrix));

    //CubeMap Texture
    GLint texture0Location = glGetUniformLocation(skyboxShader->getShaderProgram(), "cubeTexture");
	glUniform1i(texture0Location, 0);

    //Draw vertices data based on index selection values
    glDrawElements(GL_TRIANGLES, Cube::m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Enable Depth Mask
    glDepthMask(GL_TRUE);
}

void Skybox::cleanUp()
{
    glDeleteTextures(1, &cubemapTextureID);
    glDeleteProgram(skyboxShader->getShaderProgram());
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &elementsBufferID);
    glDeleteBuffers(1, &vertexArrayID);
}