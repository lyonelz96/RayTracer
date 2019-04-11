#include "Camera.h"
#include "Mesh.h"
#include "Plane.h"
#include "Sphere.h"
#include "Light.h"
#include "Ray.h"
#include "CImg.h"
#include "IndexObjLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>




/*
Takes the objects section/attributes (Camera,Plane,Mesh etc...) and separates them
so they are read individually from an array/vector in a convenient way.
*/
std::vector<std::string> dataSplit(std::string data);

/*
Reads the scene file and extracts the attributes information belonging to each object in the scene.
*/
void readScene(std::string fileName, Camera& camera, Mesh& mesh, Plane& plane, 
	           std::vector<Light*>& lights, std::vector<Sphere*>& spheres);

//Keeps track of the closest object hit by a ray
struct ClosestObject {
	float distance;
	std::string type;
	int index; // If applicable
}closestObject;
	
int main() {

	Camera* camera = new Camera();
	Mesh* mesh = new Mesh();
	Plane* plane = new Plane();
	std::vector<Light*> lights;
	std::vector<Sphere*> spheres;

	readScene("scenes\\mesh_scene1.txt", *camera, *mesh, *plane, lights, spheres);


	//Getting the information from the .obj file if any.
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

	if (mesh->getFileName() != "") {
		std::string fileNameS = "scenes\\" + mesh->getFileName();
		const char* fileName = fileNameS.c_str();
		loadOBJ(fileName, indices, vertices, normals, UVs);

		mesh->setIndices(indices);
		mesh->setVertices(vertices);
		mesh->setNormals(normals);
		mesh->setUVS(UVs);
	}

	
	//Making the window smaller for debugging purposes (Faster render)
	//camera->setFocalLength(camera->getFocalLength() / 2);


	//------------------------CImg Stuff------------------------

	int height = (2 *(std::tan((glm::radians(camera->getFOV() / 2))) * camera->getFocalLength()));
	int width = camera->getAspectRatio() * height;


	//PRINTING OUT INFO ABOUT OBJECTS ON THE SCENE FOR DEBUGGING PURPOSES

	//HEIGHT, WIDTH
	std::cout << "The height is: " << height << std::endl;
	std::cout << "The width is: " << width << std::endl;
	std::cout << std::endl;

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

	Ray* ray = new Ray();
	ray->setOrigin(camera->getPosition());
	float t = 0.0;

	//Creates an image with three channels and sets it to black
	cimg_library::CImg<float> image(width, height, 1, 3, 0);
	
	//Compute the color of each pixel and assign it
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			//Converting from Raster Space to NDC Space ([0,1])
			float NDCX = (x + 0.5) / width;
			float NDCY = (y + 0.5) / height;
			//From NDC Space to Image Space ([-1,1])
			float u = (2 * NDCX - 1) * camera->getAspectRatio() * std::tan(glm::radians(camera->getFOV()) / 2);
			float v = (1 - 2 * NDCY) * std::tan(glm::radians(camera->getFOV()) / 2);
			ray->setDirection(glm::vec3(u, v, -1));

			//Resetting info about closest object for every pixel
			bool firstObjectIntersected = false;
			closestObject.distance = -1;
			closestObject.index = -1;
			closestObject.type = "";

			
			//SPHERES-RAY INTERSECTION TEST
			for (int i = 0; i < spheres.size(); i++) {
				if (spheres[i]->doesRayIntersect(*ray, t)) {

					if (firstObjectIntersected == false) {
						closestObject.distance = t;
						closestObject.index = i;
						closestObject.type = "Sphere";
						firstObjectIntersected = true;
					}
					else {
						if (t < closestObject.distance) {
							closestObject.distance = t;
							closestObject.index = i;
							closestObject.type = "Sphere";
						}
					}
				}
			}

			//PLANES-RAY INTERSECTION TEST
			if (plane->doesRayIntersect(*ray, t)) {

				if (firstObjectIntersected == false) {
					closestObject.distance = t;
					closestObject.index = -1;
					closestObject.type = "Plane";
					firstObjectIntersected = true;
				}
				else {
					if (t < closestObject.distance) {
						closestObject.distance = t;
						closestObject.index = -1;
						closestObject.type = "Plane";
					}
				}
			}
			

			//MESH-RAY INTERSECTION TEST
			float closestIndex = -1;
			if (mesh->doesRayIntersect(*ray, indices, vertices, t, closestIndex)) {

				if (firstObjectIntersected == false) {
					closestObject.distance = t;
					closestObject.index = -1;
					closestObject.type = "Mesh";
					firstObjectIntersected = true;
				}
				else {
					if (t < closestObject.distance) {
						closestObject.distance = t;
						closestObject.index = -1;
						closestObject.type = "Mesh";
					}
				}
			}
		
			//Color calculation for closest object for current pixel
			if (closestObject.type == "Sphere") {
				glm::vec3 spherePixelColor = glm::vec3(0.0);

				for (int i = 0; i < lights.size(); i++) {
					spherePixelColor += spheres[closestObject.index]->calcColor(*ray, *lights[i], *plane, spheres, *mesh, closestObject.distance);
				}

				spherePixelColor = glm::clamp(spherePixelColor, 0.0f, 1.0f);

				image(x, y, 0) = spherePixelColor.x * 255.0f;
				image(x, y, 1) = spherePixelColor.y * 255.0f;
				image(x, y, 2) = spherePixelColor.z * 255.0f;
			}
			else if (closestObject.type == "Plane") {
				glm::vec3 planePixelColor = glm::vec3(0.0);

				for (int i = 0; i < lights.size(); i++) {
					planePixelColor += plane->calcColor(*ray, *lights[i], *plane, spheres, *mesh, closestObject.distance);
				}

				planePixelColor = glm::clamp(planePixelColor, 0.0f, 1.0f);

				image(x, y, 0) = planePixelColor.x * 255.0f;
				image(x, y, 1) = planePixelColor.y * 255.0f;
				image(x, y, 2) = planePixelColor.z * 255.0f;
			}
			else if (closestObject.type == "Mesh") {
				glm::vec3 meshPixelColor = glm::vec3(0.0f);

				for (int i = 0; i < lights.size(); i++) {
					meshPixelColor += mesh->calcColor(*ray, *lights[i], *plane, spheres, *mesh, closestObject.distance, closestIndex);
				}

				meshPixelColor = glm::clamp(meshPixelColor, 0.0f, 1.0f);

				image(x, y, 0) = meshPixelColor.x * 255.0f;
				image(x, y, 1) = meshPixelColor.y * 255.0f;
				image(x, y, 2) = meshPixelColor.z * 255.0f;
			}
			else {
				image(x, y, 0) = 0.0f;
				image(x, y, 1) = 0.0f;
				image(x, y, 2) = 0.0f;
			}
		
		}

	}
	
	//Save out the image in BMP format. Pixel values must be in the range [0,255]
	//image.normalize(0, 255);
	image.save("render.bmp");

	//Display the rendered image on screen
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed()) {
		main_disp.wait();
	}

	

	//---------------------------DEBUGGING PURPOSES---------------------------
	/*

	//HEIGHT, WIDTH
	std::cout << "The height is: " << height << std::endl;
	std::cout << "The width is: " << width << std::endl;

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

	std::cout << std::endl;

	//MESH INFORMATION (VERTICES, NORMALS, INDICES,UVS)
	int x = 0;
	while (x != 1) {
		std::cout << mesh->getFileName() << std::endl;
		for (int i = 0; i < indices.size(); i++) {
			std::cout << indices[i] << std::endl;
			std::cout << indices.size() << std::endl;
			std::cout << vertices.size() << std::endl;
			std::cout << normals.size() << std::endl;
			std::cout << UVs.size() << std::endl;

			std::cout<< "" << std::endl;
			std::cout<< "" << std::endl;
			std::cout<< "" << std::endl;

			std::cout << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
			std::cout << normals[i].x << " " << normals[i].y << " " << normals[i].z << std::endl;
			std::cout << UVs[i].x << " " << UVs[i].y << std::endl;

			std::cin >> x;
		}

	}

	//MORE MESH STUFF
	std::cout << indices.size() << std::endl;
	std::cout << vertices.size() << std::endl;
	std::cout << normals.size() << std::endl;
	std::cout << UVs.size() << std::endl;
	int j = 0;
	for (int i = 0; i < indices.size(); i+=3) {

		std::cout << "Face: " << j << std::endl;
		j++;

		std::cout << "index0: " << indices[i] << std::endl;
		std::cout << "index1: " << indices[i + 1] << std::endl;
		std::cout << "index2: " << indices[i + 2] << std::endl;

		std::cout << std::endl;

		std::cout << "v0: " << vertices[indices[i]].x << ", " <<vertices[indices[i]].y << ", " << vertices[indices[i]].z << std::endl;
		std::cout << "v1: " << vertices[indices[i+1]].x << ", " <<  vertices[indices[i+1]].y << ", " << vertices[indices[i+1]].z << std::endl;
		std::cout << "v2: " << vertices[indices[i+2]].x << ", " << vertices[indices[i+2]].y << ", " << vertices[indices[i+2]].z << std::endl;
		glm::vec3 v0v1 = vertices[indices[i]] - vertices[indices[i + 1]];
		glm::vec3 v0v2 = vertices[indices[i]] - vertices[indices[i + 2]];
		glm::vec3 normal = glm::normalize(glm::cross(v0v1, v0v2));
		std::cout << "Normal: " << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
		std::cout << std::endl;
	}
	int x = 0;
	std::cin >> x;

	*/
	//---------------------------DEBUGGING PURPOSES---------------------------

}


void readScene(std::string fileName, Camera& camera, Mesh& mesh, Plane& plane, std::vector<Light*>& lights, std::vector<Sphere*>& spheres) {
	std::ifstream inFile;
	std::string data;
	std::vector<std::string> subData;
	inFile.open(fileName);

	while (!inFile.eof()) {
		std::getline(inFile, data);

		if (data == "camera") {
			int attributeCounter = 0;
			//pos,fov,f,a
			while (attributeCounter < 4) {
				std::getline(inFile, data);

				if (data.find("pos:") != std::string::npos) {
					subData = dataSplit(data);
					camera.setPosition(glm::vec3(std::stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("fov:") != std::string::npos) {
					subData = dataSplit(data);
					camera.setFOV(std::stof(subData[1]));
				}
				else if (data.find("f:") != std::string::npos) {
					subData = dataSplit(data);
					camera.setFocalLength(std::stof(subData[1]));
				}
				else if (data.find("a:") != std::string::npos) {
					subData = dataSplit(data);
					camera.setAspectRatio(std::stof(subData[1]));
				}
				attributeCounter++;
			}
		}
		else if (data == "plane") {
			int attributeCounter = 0;
			//nor,pos,amb,dif,spe,shi
			while (attributeCounter < 6) {
				std::getline(inFile, data);

				if (data.find("nor:") != std::string::npos) {
					subData = dataSplit(data);
					plane.setNormal(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("pos:") != std::string::npos) {
					subData = dataSplit(data);
					plane.setPosition(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("amb:") != std::string::npos) {
					subData = dataSplit(data);
					plane.setAmbientColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("dif:") != std::string::npos) {
					subData = dataSplit(data);
					plane.setDiffuseColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("spe:") != std::string::npos) {
					subData = dataSplit(data);
					plane.setSpecularColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("shi:") != std::string::npos) {
					subData = dataSplit(data);
					plane.setShininess(std::stof(subData[1]));
				}

				attributeCounter++;
			}
		}
		else if (data == "sphere") {
			int attributeCounter = 0;
			spheres.push_back(new Sphere());
			//pos,rad,amb,dif,spe,shi
			while (attributeCounter < 6) {
				std::getline(inFile, data);

				if (data.find("pos:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres.size() - 1]->setPosition(glm::vec3(std::stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("rad:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres.size() - 1]->setRadius(std::stof(subData[1]));
				}
				else if (data.find("amb:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres.size() - 1]->setAmbientColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("dif:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres.size() - 1]->setDiffuseColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("spe:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres.size() - 1]->setSpecularColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("shi:") != std::string::npos) {
					subData = dataSplit(data);
					spheres[spheres.size() - 1]->setShininess(std::stof(subData[1]));
				}

				attributeCounter++;
			}
		}
		else if (data == "mesh") {
			int attributeCounter = 0;
			//file,amb,dif,spe,shi
			while (attributeCounter < 5) {
				std::getline(inFile, data);

				if (data.find("file:") != std::string::npos) {
					subData = dataSplit(data);
					mesh.setFileName(subData[1]);
				}
				else if (data.find("amb:") != std::string::npos) {
					subData = dataSplit(data);
					mesh.setAmbientColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("dif:") != std::string::npos) {
					subData = dataSplit(data);
					mesh.setDiffuseColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("spe:") != std::string::npos) {
					subData = dataSplit(data);
					mesh.setSpecularColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("shi:") != std::string::npos) {
					subData = dataSplit(data);
					mesh.setShininess(std::stof(subData[1]));
				}

				attributeCounter++;
			}
		}
		else if (data == "light") {
			int attributeCounter = 0;
			lights.push_back(new Light());
			//pos,dif,spe
			while (attributeCounter < 3) {
				std::getline(inFile, data);

				if (data.find("pos:") != std::string::npos) {
					subData = dataSplit(data);
					lights[lights.size() - 1]->setPosition(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("dif:") != std::string::npos) {
					subData = dataSplit(data);
					lights[lights.size() - 1]->setDiffuseColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				else if (data.find("spe:") != std::string::npos) {
					subData = dataSplit(data);
					lights[lights.size() - 1]->setSpecularColor(glm::vec3(stof(subData[1]), std::stof(subData[2]), std::stof(subData[3])));
				}
				attributeCounter++;
			}
		}
	}

}

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
