#include "pch.h"
#include "MeshLoader.h"
#include <iostream>
#include <fstream>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

MeshLoader::MeshLoader() {

}

void MeshLoader::parseObj(const char* path) {
	std::ifstream myReadFile;
	myReadFile.open(path);
	std::string str;
	if (myReadFile.is_open()) {
		while (std::getline(myReadFile, str)) {
			// output the line
			//std::cout << str << std::endl;
			size_t pos = 0;
			std::string token;
			std::string delimiter = " ";
			if ((pos = str.find(delimiter)) != std::string::npos) {
				token = str.substr(0, pos);

				size_t pos1 = str.find(delimiter, pos + delimiter.length());
				size_t pos2 = str.find(delimiter, pos1 + delimiter.length());
				std::string str1 = str.substr(pos, pos1 - pos);
				std::string str2 = str.substr(pos1 + delimiter.length(), pos2 - pos1);
				std::string str3 = str.substr(pos2 + delimiter.length(), str.length() - pos2);

				if (token == "v") {
					V.push_back(glm::vec3(std::stof(str1), std::stof(str2), std::stof(str3)));
				}
				else if (token == "vn") {
					VN.push_back(glm::vec3(std::stof(str1), std::stof(str2), std::stof(str3)));
				}
				else if (token == "f") {
					std::vector<std::string> strs({ str1, str2, str3 });
					glm::ivec3 face, fn;
					for (int i = 0; i < 3; i++) {
						pos2 = strs[i].find("//");
						std::string v = strs[i].substr(0, pos2);
						std::string vn = strs[i].substr(pos2+2, strs[i].length());
						face[i] = std::stoi(v);
						fn[i] = std::stoi(vn);
					}
					F.push_back(face);
					FN.push_back(fn);
					std::cout << glm::to_string(fn) << std::endl;
				}
			}
		}
	}
	else {

	}
}