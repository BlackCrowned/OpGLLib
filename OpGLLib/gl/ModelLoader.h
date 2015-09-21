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
#include <OpGLLib/FileLoader.h>

#include <string>
#include <vector>
#include <memory>

#include <tinyObjLoader/tiny_obj_loader.h>

namespace OpGLLib {
namespace gl {

enum class MeshType {
	OBJ = 0
};

enum class MaterialType {
	MTL = 0, MATERIAL_COLLECTION
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

class Material {
public:
	Material() = default;
	Material(Material const& other) = default;
	virtual ~Material() = default;

	virtual std::string const& name() const = 0;

	virtual glm::vec4 const& ambient() const = 0;
	virtual glm::vec4 const& diffuse() const = 0;
	virtual glm::vec4 const& specular() const = 0;
	virtual glm::vec4 const& transmittance() const = 0;
	virtual glm::vec4 const& emission() const = 0;

	virtual std::string const& ambientTexture() const = 0;
	virtual std::string const& diffuseTexture() const = 0;
	virtual std::string const& specularTexture() const = 0;
	virtual std::string const& normalTexture() const = 0;
};

template<MaterialType T>
class MaterialImpl {
public:
	MaterialImpl() = delete;
	~MaterialImpl() = delete;
};

template<> class MaterialImpl<MaterialType::MTL> : public Material {
public:
	MaterialImpl() = default;
	MaterialImpl(tinyobj::material_t material);
	MaterialImpl(MaterialImpl<MaterialType::MTL> const& other) = default;
	MaterialImpl(MaterialImpl<MaterialType::MTL> && other) = default;
	virtual ~MaterialImpl() = default;

	void setData(tinyobj::material_t material);

	virtual std::string const& name() const;

	virtual glm::vec4 const& ambient() const;
	virtual glm::vec4 const& diffuse() const;
	virtual glm::vec4 const& specular() const;
	virtual glm::vec4 const& transmittance() const;
	virtual glm::vec4 const& emission() const;

	virtual std::string const& ambientTexture() const;
	virtual std::string const& diffuseTexture() const;
	virtual std::string const& specularTexture() const;
	virtual std::string const& normalTexture() const;

private:
	std::string _name;

	glm::vec4 _ambient;
	glm::vec4 _diffuse;
	glm::vec4 _specular;
	glm::vec4 _transmittance;
	glm::vec4 _emission;

	std::string _ambientTexture;
	std::string _diffuseTexture;
	std::string _specularTexture;
	std::string _normalTexture;
};

template<> class MaterialImpl<MaterialType::MATERIAL_COLLECTION> : public Material {
public:
	MaterialImpl() = default;
	MaterialImpl(Material const& other);
	~MaterialImpl() = default;

	void setName(std::string const& name);

	void setAmbient(glm::vec4 const& ambient);
	void setDiffuse(glm::vec4 const& diffuse);
	void setSpecular(glm::vec4 const& specular);
	void setTransmittance(glm::vec4 const& transmittance);
	void setEmission(glm::vec4 const& emission);

	void setAmbientTexture(std::string const& ambientTexture);
	void setDiffuseTexture(std::string const& diffuseTexture);
	void setSpecularTexture(std::string const& specularTexture);
	void setNormalTexture(std::string const& normalTexture);

	virtual std::string const& name() const;

	virtual glm::vec4 const& ambient() const;
	virtual glm::vec4 const& diffuse() const;
	virtual glm::vec4 const& specular() const;
	virtual glm::vec4 const& transmittance() const;
	virtual glm::vec4 const& emission() const;

	virtual std::string const& ambientTexture() const;
	virtual std::string const& diffuseTexture() const;
	virtual std::string const& specularTexture() const;
	virtual std::string const& normalTexture() const;

private:
	std::string _name;

	glm::vec4 _ambient;
	glm::vec4 _diffuse;
	glm::vec4 _specular;
	glm::vec4 _transmittance;
	glm::vec4 _emission;

	std::string _ambientTexture;
	std::string _diffuseTexture;
	std::string _specularTexture;
	std::string _normalTexture;
};

class NullMaterial: public Material {
public:
	NullMaterial() = default;
	NullMaterial(NullMaterial const& other) = default;
	~NullMaterial() = default;

	virtual std::string const& name() const;

	virtual glm::vec4 const& ambient() const;
	virtual glm::vec4 const& diffuse() const;
	virtual glm::vec4 const& specular() const;
	virtual glm::vec4 const& transmittance() const;
	virtual glm::vec4 const& emission() const;

	virtual std::string const& ambientTexture() const;
	virtual std::string const& diffuseTexture() const;
	virtual std::string const& specularTexture() const;
	virtual std::string const& normalTexture() const;

private:
	std::string _name;

	glm::vec4 _ambient;
	glm::vec4 _diffuse;
	glm::vec4 _specular;
	glm::vec4 _transmittance;
	glm::vec4 _emission;

	std::string _ambientTexture;
	std::string _diffuseTexture;
	std::string _specularTexture;
	std::string _normalTexture;
};

class MaterialComparator {
public:
	MaterialComparator() = default;
	~MaterialComparator() = default;

	void operator() (MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;

	void compNames(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
	void compAmbient(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
	void compDiffuse(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
	void compSpecular(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
	void compTransmittance(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
	void compEmission(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;

	void compAmbientTexture(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
	void compDiffuseTexture(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
	void compSpecularTexture(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
	void compNormalTexture(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const;
};

class MaterialCollection {
public:
	MaterialCollection();
	MaterialCollection(std::initializer_list<std::shared_ptr<Material>> init_list);
	~MaterialCollection() = default;

	void addMaterial(std::shared_ptr<Material>&& material);

	void update();

	std::shared_ptr<Material> get() const;
private:
	std::deque<std::shared_ptr<Material>> _materialList;
	std::shared_ptr<Material> _material;
};

class Model {
public:
	Model();
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<MaterialCollection> materialCollection);
	Model(Model const& other) = default;
	~Model() = default;

	void setMesh(std::shared_ptr<Mesh>&& mesh);
	void setMaterial(std::shared_ptr<Material>&& material);
	void setMaterialCollection(std::shared_ptr<MaterialCollection>&& materialCollection);

	std::string const& name() const;

	std::shared_ptr<Mesh> mesh() const;
	std::shared_ptr<Material> material() const;
	std::shared_ptr<MaterialCollection> materialCollecion() const;

private:
	void update();

	std::string _name;
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<MaterialCollection> _materialCollection;
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

	virtual std::shared_ptr<Model> load(std::string const& file) = 0;
};

class ModelLoader: public ModelLoaderBase {
public:
	ModelLoader();
	ModelLoader(OpGLLibBase const* pointer);
	virtual ~ModelLoader() = default;

	virtual std::shared_ptr<Model> load(std::string const& file);

protected:
	std::shared_ptr<Model> loadObj(std::string const& file, std::string const& basepath = "");
};

class NullModelLoader: public ModelLoaderBase {
public:
	NullModelLoader();
	NullModelLoader(OpGLLibBase const* pointer);
	virtual ~NullModelLoader() = default;

	virtual std::shared_ptr<Model> load(std::string const& file);
};

}
}

#endif /* OPGLLIB_MODELLOADER_H_ */
