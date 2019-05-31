#pragma once
#include <vector>
#include <glm/glm.hpp>

class MeshLoader {
public:
	MeshLoader();
	void parseObj(const char* path);
private:
	std::vector<glm::vec3> V;
	std::vector<glm::vec3> VN;
	std::vector<glm::ivec3> F;
	std::vector<glm::ivec3> FN;

};