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

class ModelLoader;

//struct Object {
//	std::string name = "";
//	int count = 0;
//	int lineSmoothing = 0;
//	std::vector<glm::vec4> vertices;
//	std::vector<glm::vec2> textureVertices;
//	std::vector<glm::vec3> normals;
//	std::vector<glm::uvec3> indicies;
//	std::vector<glm::uvec3> textureIndicies;
//	std::vector<glm::uvec3> normalIndicies;
//};

//struct Model {
//	std::string name = "";
//	unsigned int id = 0;
//	int count = 0;
//	int loaded = false;
//	std::vector<Object> objects;
//};

class ObjectBase {
public:
	ObjectBase() = default;
	ObjectBase(ObjectBase const& other) = default;
	ObjectBase(ObjectBase&& other) = default;
	virtual ~ObjectBase() = 0;

	ObjectBase& operator=(ObjectBase const& other) = default;

	virtual std::string& getName() = 0;
	virtual int getVerticesCount() = 0;
	virtual int getLineSmoothing() = 0;
	virtual std::vector<glm::vec4>& getVertices() = 0;
	virtual std::vector<glm::vec2>& getTextureVertices() = 0;
	virtual std::vector<glm::vec3>& getNormals() = 0;
	virtual std::vector<glm::uvec3>& getIndicies() = 0;
	virtual gl::GLenum getIndiciesType() = 0;
	virtual const void* getIndiciesOffset() = 0;
	virtual std::vector<glm::uvec3>& getTextureIndicies() = 0;
	virtual std::vector<glm::uvec3>& getNormalIndicies() = 0;
};

class ModelBase {
public:
	ModelBase() = default;
	ModelBase(ModelBase const& other) = default;
	ModelBase(ModelBase&& other) = default;
	virtual ~ModelBase() = 0;

	ModelBase& operator=(ModelBase const& other) = default;

	virtual std::string& getName() = 0;
	virtual unsigned int getId() = 0;
	virtual int getObjectCount() = 0;
	virtual int getLoadedState() = 0;
	virtual ObjectBase& getObject(int id) = 0;
};

class Object: public ObjectBase {
public:
	Object() = default;
	Object(Object const& other) = default;
	Object(Object&& other) = default;
	~Object() = default;

	Object& operator=(Object const& other) = default;

	std::string& getName();
	int getVerticesCount();
	int getLineSmoothing();
	std::vector<glm::vec4>& getVertices();
	std::vector<glm::vec2>& getTextureVertices();
	std::vector<glm::vec3>& getNormals();
	std::vector<glm::uvec3>& getIndicies();
	gl::GLenum getIndiciesType();
	const void* getIndiciesOffset();
	std::vector<glm::uvec3>& getTextureIndicies();
	std::vector<glm::uvec3>& getNormalIndicies();

private:
	friend class ModelLoader;
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

class Model: public ModelBase {
public:
	Model() = default;
	Model(Model const& other) = default;
	Model(Model&& other) = default;
	~Model() = default;

	Model& operator=(Model const& other) = default;

	std::string& getName();
	unsigned int getId();
	int getObjectCount();
	int getLoadedState();
	Object& getObject(int id);
private:
	friend class ModelLoader;
	std::string name = "";
	unsigned int id = 0;
	int count = 0;
	int loaded = false;
	std::vector<Object> objects;
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
