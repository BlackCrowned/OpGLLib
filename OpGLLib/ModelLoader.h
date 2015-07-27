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

	virtual std::string& name() = 0;

	virtual std::vector<glm::vec3>& vertices() = 0;
	virtual std::vector<glm::vec3>& normals() = 0;
	virtual std::vector<glm::vec2>& texCoords() = 0;
	virtual std::vector<glm::uvec3>& indices() = 0;
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

	virtual std::string& name();

	virtual std::vector<glm::vec3>& vertices();
	virtual std::vector<glm::vec3>& normals();
	virtual std::vector<glm::vec2>& texCoords();
	virtual std::vector<glm::uvec3>& indices();

private:
	std::string _name;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec2> _texCoords;
	std::vector<glm::uvec3> _indices;
};

class ModelLoader {
public:
	ModelLoader() = delete;
	~ModelLoader() = delete;

	static std::shared_ptr<Mesh> load(std::string const& model);

protected:
	static std::shared_ptr<MeshImpl<MeshType::OBJ>> loadObj(std::string const& model);
};

}
}

#endif /* OPGLLIB_MODELLOADER_H_ */
