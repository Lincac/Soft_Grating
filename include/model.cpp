#include"model.h"

Model::Model(const char* filename){
	std::ifstream file(filename);
	std::string line;
	if (!file.is_open())
	{
		std::cerr << filename << " can not open : \n";
		exit(-1);
	}

    float maxX = -INF,maxY = -INF,maxZ = -INF;
    float minX = INF,minY = INF,minZ = INF;

	while (std::getline(file, line))
	{
		std::istringstream str(line);
		std::string type;

		float x, y, z;
		int v0, v1, v2;
		float uvx,uvy;

		str >> type;
		if (type == "v")
		{
			str >> x >> y >> z;
			maxX = x > maxX ? x : maxX;
			maxY = y > maxY ? y : maxY;
			maxZ = z > maxZ ? z : maxZ;

			minX = x < minX ? x : minX;
			minY = y < minY ? y : minY;
			minZ = z < minZ ? z : minZ;

			vertices.push_back(vec3(x, y, z));
		}
		else if (type == "f") {
			str >> v0 >> v1 >> v2;

			index.push_back(v0 - 1);
			index.push_back(v1 - 1);
			index.push_back(v2 - 1);
		}else if(type == "uv"){
			str >> uvx >> uvy;
			uv.push_back(vec2(uvx,uvy));
		}
	}
    file.close();



    float deltax = (maxX - minX) == 0 ? 1 : maxX - minX;
    float deltay = (maxY - minY) == 0 ? 1 : maxY - minY;
    float deltaz = (maxZ - minZ) == 0 ? 1 : maxZ - minZ;

    for(auto &temp : vertices){
        temp.x /= deltax;
        temp.y /= deltay;
        temp.z /= deltaz;
    }
}

Model::~Model(){
}
