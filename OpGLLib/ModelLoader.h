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

struct Model {
	std::string name;
	std::string fileType;
	std::vector<glm::vec4> vertices;
	std::vector<gl::GLint> indicies;
};

class ModelLoader : private FileLoader {
public:
	ModelLoader();
	ModelLoader(std::string name, int id);
	~ModelLoader();

	int load(std::string name, int id);

	Model &getModel(int id);
private:
	std::map<int, Model> models;
};

#endif /* OPGLLIB_MODELLOADER_H_ */
