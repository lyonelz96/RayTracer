#include "Camera.h"
#include "Mesh.h"
#include "Plane.h"
#include "Sphere.h"
#include "Light.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


//This function takes the objects section (Camera,Plane,Mesh etc...) and separates their respective attributes
//so they are read individually from an array/vector in a more convenient way.
std::vector<std::string> dataSplit(std::string data) {
	std::vector<std::string> subData;

	int end = data.find(" ");

	while (end != std::string::npos) {
		subData.push_back(data.substr(0, end));
		data.erase(0, end + 1);
		end = data.find(" ");

		if (end == std::string::npos) {
			subData.push_back(data);
		}
	}

	return subData;
}

void readScene(std::string fileName,Camera* camera, Mesh* mesh, Plane* plane, std::vector<Light*>* lights, std::vector<Sphere*>* spheres) {
	std::ifstream inFile;
	std::string data;
	std::vector<std::string> subData;
	inFile.open(fileName);

	while (!inFile.eof()) {
		std::getline(inFile, data);

		if (data == "camera"){
			int attributeCounter = 0;
			//pos,fov,f,a
			while (attributeCounter < 4) {
				std::getline(inFile, data);

				if (data.find("pos:") != std::string::npos) {
					 subData = dataSplit(data);
					 camera->setPosition(glm::vec3(std::stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("fov:") != std::string::npos) {
					subData = dataSplit(data);
					camera->setTheta(std::stof(subData[1]));
				}
				else if (data.find("f:") != std::string::npos) {
					subData = dataSplit(data);
					camera->setFocalLength(std::stof(subData[1]));
				}
				else if (data.find("a:") != std::string::npos) {
					subData = dataSplit(data);
					camera->setAspectRatio(std::stof(subData[1]));
				}
				attributeCounter++;
			}
		}
		else if (data == "plane"){
			int attributeCounter = 0;
			//nor,pos,amb,dif,spe,shi
			while (attributeCounter < 6) {
				std::getline(inFile, data);

				if (data.find("nor:") != std::string::npos) {
					subData = dataSplit(data);
					plane->setNormal(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("pos:") != std::string::npos) {
					subData = dataSplit(data);
					plane->setPosition(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("amb:") != std::string::npos) {
					subData = dataSplit(data);
					plane->setAmbientColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("dif:") != std::string::npos) {
					subData = dataSplit(data);
					plane->setDiffuseColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("spe:") != std::string::npos) {
					subData = dataSplit(data);
					plane->setSpecularColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("shi:") != std::string::npos) {
					subData = dataSplit(data);
					plane->setShininess(std::stof(subData[1]));
				}

				attributeCounter++;
			}
		}
		else if (data == "sphere"){
			int attributeCounter = 0;
			spheres->push_back(new Sphere());
			//pos,rad,amb,dif,spe,shi
			while (attributeCounter < 6) {
				std::getline(inFile, data);

				if (data.find("pos:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres->size() - 1][spheres->size() - 1]->setPosition(glm::vec3(std::stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("rad:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres->size() - 1][spheres->size() - 1]->setRadius(std::stof(subData[1]));
				}
				else if (data.find("amb:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres->size() - 1][spheres->size() - 1]->setAmbientColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("dif:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres->size() - 1][spheres->size() - 1]->setDiffuseColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("spe:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres->size() - 1][spheres->size() - 1]->setSpecularColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("shi:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres->size() - 1][spheres->size() - 1]->setShininess(std::stof(subData[1]));
				}

				attributeCounter++;
			}
		}
		else if (data == "mesh"){
			int attributeCounter = 0;
			//file,amb,dif,spe,shi
			while (attributeCounter < 5) {
				std::getline(inFile, data);

				if (data.find("file:") != std::string::npos) {
					subData = dataSplit(data);
					mesh->setFileName(subData[1]);
				}
				else if (data.find("amb:") != std::string::npos) {
					subData = dataSplit(data);
					mesh->setAmbientColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("dif:") != std::string::npos) {
					subData = dataSplit(data);
					mesh->setDiffuseColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("spe:") != std::string::npos) {
					subData = dataSplit(data);
					mesh->setSpecularColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("shi:") != std::string::npos) {
					subData = dataSplit(data);
					mesh->setShininess(std::stof(subData[1]));
				}

				attributeCounter++;
			}
		}
		else if (data == "light"){
			int attributeCounter = 0;
			lights->push_back(new Light());
			//pos,dif,spe
			while (attributeCounter < 3) {
				std::getline(inFile, data);

				if (data.find("pos:") != std::string::npos) {
					subData = dataSplit(data);
					lights[lights->size() - 1][lights->size() - 1]->setPosition(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("dif:") != std::string::npos) {
					subData = dataSplit(data);
					lights[lights->size() - 1][lights->size() - 1]->setDiffuseColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("spe:") != std::string::npos) {
					subData = dataSplit(data);
					lights[lights->size() - 1][lights->size() - 1]->setSpecularColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				attributeCounter++;
			}
		}
	}

}

int main() {

	Camera* camera = new Camera();
	Mesh* mesh = new Mesh();
	Plane* plane = new Plane();
	std::vector<Light*> lights;
	std::vector<Sphere*> spheres;

	readScene("mesh_scene1.txt", camera, mesh, plane, &lights, &spheres);



	//DEBUGGING PURPOSES

	//CAMERA
	camera->toString(); 

	std::cout << std::endl;

	//PLANE
	plane->toString(); 

	std::cout << std::endl;

	//SPHERES
	for (int i = 0; i < spheres.size(); i++) {
		spheres[i]->toString();
		std::cout << std::endl;
	}

	//MESH
	mesh->toString(); 

	std::cout << std::endl;

	//LIGHTS
	for (int i = 0; i < lights.size(); i++) {
		lights[i]->toString();
		std::cout << std::endl;
	}

}