OBJModel::OBJModel()
{

}

OBJModel::~OBJModel()
{

}
 
vector<glm::vec3>OBJModel::parseVertices(std::string pathName)
{
    vector<glm::vec3> temp;

    std::ifstream openFile;

    if(openfile != null)
     openfile.open(MODEL_PATH + "stall.obj");
    else
    {
        std::cout<<"File Reader was not configured";
        return;
    }


    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
        
        }
    }

    return temp;
}
vector<glm::vec2>OBJModel::parseTextures(std::string pathName)
{
    vector<glm::vec2> temp;

    std::ifstream openFile;

    if(openfile != null)
     openfile.open(MODEL_PATH + "stall.obj");
    else
    {
        std::cout<<"File Reader was not configured";
        return;
    }


    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
        
        }
    }

        return temp;
}
vector<glm::vec3>OBJModel::parseNormals(std::string pathName)
{
    vector<glm::vec3> temp;

    std::ifstream openFile;

    if(openfile != null)
     openfile.open(MODEL_PATH + "stall.obj");
    else
    {
        std::cout<<"File Reader was not configured";
        return;
    }


    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
        
        }
    }

        return temp;
}