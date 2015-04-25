/*
 * ModelLoader.h
 *
 *  Created on: 30.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_MODELLOADER_H_
#define OPGLLIB_MODELLOADER_H_

#define INCLUDE_GLM
#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/FileLoader.h>

#include <regex>
#include <map>

struct Object {
	std::string name = "";
	int count = 0;
	int lineSmoothing = 0;
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> textureVertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::uvec3> indicies;
	std::vector<glm::uvec3> textureIndicies;
	std::vector<glm::uvec3> normalIndicies;
};

struct Model {
	std::string name = "";
	unsigned int id = 0;
	int count = 0;
	int loaded = false;
	std::vector<Object> objects;
};

class ObjectWrapper {
public:
	ObjectWrapper(Object* o) :
			object(o) {

	}
	virtual ~ObjectWrapper() {
	}

	virtual std::string* getObjectName() {
		return &object->name;
	}
	virtual int getVerticesCount() {
		return object->count;
	}
	virtual int getLineSmoothing() {
		return object->lineSmoothing;
	}
	virtual std::vector<glm::vec4>* getVertices() {
		return &object->vertices;
	}
	virtual std::vector<glm::vec2>* getTextureVerticess() {
		return &object->textureVertices;
	}
	virtual std::vector<glm::vec3>* getNormals() {
		return &object->normals;
	}
	virtual std::vector<glm::uvec3>* getIndicies() {
		return &object->indicies;
	}
	virtual gl::GLenum getIndiciesType() {
		return gl::GL_UNSIGNED_INT;
	}
	virtual const void* getIndiciesOffset() {
		return static_cast<const void*>(0);
	}
	virtual std::vector<glm::uvec3>* getTextureIndicies() {
		return &object->textureIndicies;
	}
	virtual std::vector<glm::uvec3>* getNormalIndicies() {
		return &object->normalIndicies;
	}

private:
	Object* object;
};

class ModelWrapper {
public:
	ModelWrapper(Model* model) {
		ModelWrapper::model = model;
	}
	virtual ~ModelWrapper() {
	}

	virtual std::string* getModelName() {
		return &model->name;
	}
	virtual unsigned int* getModelId() {
		return &model->id;
	}
	virtual int* getObjectCount() {
		return &model->count;
	}
	virtual int* getLoadedState() {
		return &model->loaded;
	}
	virtual Object* getObject(int id) {
		return &model->objects[id];
	}
	virtual std::unique_ptr<ObjectWrapper> getObjectWrapper(int id) {
		return std::unique_ptr<ObjectWrapper>(new ObjectWrapper(getObject(id)));
	}

private:
	Model* model;
};

class ModelLoader: private OpGLLib::FileLoader {
public:
	ModelLoader();
	ModelLoader(const std::string& name, unsigned int id);
	~ModelLoader();

	unsigned int reserve(const std::string& name, unsigned int id);
	unsigned int load(const std::string& name, unsigned int id);
	unsigned int unload(const std::string& name, unsigned int id);

	Model &getModel(unsigned int id);
private:
	Model parseObj(const std::string& name, unsigned int id);
	std::map<unsigned int, Model> models;
};

#endif /* OPGLLIB_MODELLOADER_H_ */
