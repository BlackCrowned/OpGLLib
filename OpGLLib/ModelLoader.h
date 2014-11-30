/*
 * ModelLoader.h
 *
 *  Created on: 30.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_MODELLOADER_H_
#define OPGLLIB_MODELLOADER_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/FileLoader.h>
#include <OpGLLib/Debug.h>

struct Object {
	std::string name = "";
	int count = 0;
	int lineSmoothing = 0;
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> textureVertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::ivec3> indicies;
	std::vector<glm::ivec3> textureIndicies;
	std::vector<glm::ivec3> normalIndicies;
};

struct Model {
	std::string name = "";
	unsigned int id = 0;
	int count = 0;
	std::vector<Object> objects;
};

class ModelLoader : private FileLoader {
public:
	ModelLoader();
	ModelLoader(const std::string& name, unsigned int id);
	~ModelLoader();

	unsigned int load(const std::string& name, unsigned int id);

	Model &getModel(unsigned int id);
private:
	Model parseObj(const std::string& name, unsigned int id);
	static std::map<unsigned int, Model> models;
};

#endif /* OPGLLIB_MODELLOADER_H_ */
