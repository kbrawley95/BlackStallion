OBJLoader::OBJLoader(std::string filepath, std::vector<glm::vec3>&vertexPositions, std::vector<glm::vec2>&textCoords, std::vector<glm::vec3>&normalVectors)
{
    loadModelDataFromFile(filepath, vertexPositions, textCoords, normalVectors);
}

void OBJLoader::loadModelDataFromFile(std::string filepath, std::vector<glm::vec3>&vertexPositions, std::vector<glm::vec2>&textCoords, std::vector<glm::vec3>&normalVectors)
{
    char positionReg[] = "v";
    char uvReg[] = "vt";
    char normalReg[] = "vn";
    char faceReg[] = "f";

    std::ifstream file;
	file.open(filepath);

	std::string line;
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);

			unsigned int lineLength = line.length();

			if (lineLength < 2)
				continue;
			
			const char* charBuffer = line.c_str();

			switch (charBuffer[0])
			{
				case 'v':
					if (charBuffer[1] == 't')
					{
						parseDataToArray(charBuffer, uvs, uvReg);
						parseVector2(uvs, textCoords);
					}
					else if (charBuffer[1] == 'n')
					{
						parseDataToArray(charBuffer, normals, normalReg);
						parseVector3(normals, normalVectors);
					}
					else
					{
						parseDataToArray(charBuffer, positions, positionReg);
						parseVector3(positions, vertexPositions);
					}
					break;

				case 'f':
					parseDataToArray(charBuffer, faces, faceReg);
			}

		}

		file.close();
	}
	else
	{
		std::cerr << "Unable to load obj data file: " << filepath << std::endl;
	}
}



void OBJLoader::parseDataToArray(const char* &charBuffer, std::vector<std::string> &array, char regs[])
{
	std::string temp = (std::string)charBuffer;
	std::string formated;

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		temp.erase(std::remove(temp.begin(), temp.end(), regs[i]), temp.end());
	}

	array.push_back(temp);
}

void OBJLoader::parseVector2(std::vector<std::string> array, std::vector<glm::vec2> &output)
{
	float vOne;
	float vTwo;
	
	char sub[255];
	char sub2[255];

	for (unsigned int i = 0; i < array.size(); i++)
	{
		std::istringstream iss(array[i]);
		iss >> sub >> sub2;
		vOne = std::atof(sub);
		vTwo = std::atof(sub2);
		
	}
	output.push_back(glm::vec2((float)vOne, (float)vTwo));
}

void OBJLoader::parseVector3(std::vector<std::string>array, std::vector<glm::vec3> &output)
{
	float vOne;
	float vTwo;
	float vThree;

	char sub[255];
	char sub2[255];
	char sub3[255];

	for (unsigned int i = 0; i < array.size(); i++)
	{
		std::istringstream iss(array[i]);
		iss >> sub >> sub2 >>sub3;
		vOne = std::atof(sub);
		vTwo = std::atof(sub2);
		vThree = std::atof(sub2);

	}
	output.push_back(glm::vec3((float)vOne, (float)vTwo, (float)vThree));
}

void OBJLoader::printArrayContents(std::string arrayName, std::vector<std::string> array)
{
	std::cout << arrayName << ": " << std::endl;
	for (int i = 0; i <array.size(); i++)
	{
		std::cout << i + 1 << ": " << array[i] << std::endl;
	}
}

void OBJLoader::printArrayContents(std::string arrayName, std::vector<glm::vec2>&array)
{
	std::cout << arrayName << ": " << std::endl;
	for (int i = 0; i <array.size(); i++)
	{
		std::cout << i + 1 << ": x: " << array[i].x << " y: " << array[i].y  <<std::endl;
	}
}

void printArrayContents(std::string arrayName, std::vector<glm::vec3>&array)
{
	std::cout << arrayName << ": " << std::endl;
	for (int i = 0; i <array.size(); i++)
	{
		std::cout << i + 1 << ": x: " << array[i].x << " y: " << array[i].y << " z: " << array[i].z <<std::endl;
	}
}