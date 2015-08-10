/*
 * ModelLoader.h
 *
 *  Created on: 30.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_MODELLOADER_H_
#define OPGLLIB_MODELLOADER_H_

#define INCLUDE_GLM
#include <OpGLLib/internal.h>

#include <OpGLLib/DefaultDelete.h>
#include <OpGLLib/Logging.h>
#include <OpGLLib/OpGLLib.h>
#include <OpGLLib/Exception.h>

#include <string>
#include <vector>
#include <memory>

#include <tinyObjLoader/tiny_obj_loader.h>

namespace OpGLLib {
namespace gl {

enum class MeshType {
	OBJ = 0
};

class Mesh {
public:
	Mesh() = default;
	virtual ~Mesh() = default;

	virtual std::string const& name() const = 0;

	virtual std::vector<glm::vec3> const& vertices() const = 0;
	virtual std::vector<glm::vec3> const& normals() const = 0;
	virtual std::vector<glm::vec2> const& texCoords() const = 0;
	virtual std::vector<glm::uvec3> const& indices() const = 0;
};

template<MeshType T> class MeshImpl {
public:
	MeshImpl() = delete;
	~MeshImpl() = delete;
};

template<> class MeshImpl<MeshType::OBJ> : public Mesh {
public:
	MeshImpl() = default;
	virtual ~MeshImpl() = default;

	void setData(tinyobj::shape_t shape);

	virtual std::string const& name() const;

	virtual std::vector<glm::vec3> const& vertices() const;
	virtual std::vector<glm::vec3> const& normals() const;
	virtual std::vector<glm::vec2> const& texCoords() const;
	virtual std::vector<glm::uvec3> const& indices() const;

private:
	std::string _name;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec2> _texCoords;
	std::vector<glm::uvec3> _indices;
};

class NullMesh: public Mesh {
public:
	NullMesh() = default;
	virtual ~NullMesh() = default;

	virtual std::string const& name() const;

	virtual std::vector<glm::vec3> const& vertices() const;
	virtual std::vector<glm::vec3> const& normals() const;
	virtual std::vector<glm::vec2> const& texCoords() const;
	virtual std::vector<glm::uvec3> const& indices() const;

private:
	std::string _name;
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec2> _texCoords;
	std::vector<glm::uvec3> _indices;
};

class Model {
public:
	Model();
	Model(std::shared_ptr<Mesh> mesh);
	Model(Model const& other) = default;
	~Model() = default;

	void setMesh(std::shared_ptr<Mesh>&& mesh);
	/*void setMaterial */
	/*void setMaterialCollection */

	std::string const& name() const;

	std::shared_ptr<Mesh> mesh() const;
	/*Material material();*/
	/*MaterialCollection materialCollecion();*/

private:
	std::shared_ptr<Mesh> _mesh;
	/*std::shared_ptr<MaterialCollection> _materialCollection;*/
};

/*
 * Required exceptions
 */

class LoadModelException: public Exception {
public:
	LoadModelException(OpGLLibBase const* pointer, std::string const& model, std::string const& reason);
	~LoadModelException() = default;

	virtual ExceptionType what();
	virtual std::string toString();

	virtual bool handle();

private:
	std::string const& _model;
	std::string const& _reason;
};

/*
 * Main class
 */

class ModelLoaderBase: public OpGLLibBase {
public:
	ModelLoaderBase();
	ModelLoaderBase(OpGLLibBase const* pointer);
	virtual ~ModelLoaderBase() = default;

	virtual std::shared_ptr<Model> load(std::string const& model) = 0;
};

class ModelLoader: public ModelLoaderBase {
public:
	ModelLoader();
	ModelLoader(OpGLLibBase const* pointer);
	virtual ~ModelLoader() = default;

	virtual std::shared_ptr<Model> load(std::string const& model);

protected:
	std::shared_ptr<Model> loadObj(std::string const& modelfile);
};

class NullModelLoader: public ModelLoaderBase {
public:
	NullModelLoader();
	NullModelLoader(OpGLLibBase const* pointer);
	virtual ~NullModelLoader() = default;

	virtual std::shared_ptr<Model> load(std::string const& model);
};

}
}

#endif /* OPGLLIB_MODELLOADER_H_ */
