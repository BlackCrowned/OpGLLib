/*
 * ModelLoader.cpp
 *
 *  Created on: 30.11.2014
 *      Author: Michael
 */

#include <OpGLLib/gl/ModelLoader.h>

#include <OpGLLib/ServiceLocator.h>

namespace OpGLLib {
namespace gl {

void MeshImpl<MeshType::OBJ>::setData(tinyobj::shape_t shape) {
	//Set name
	_name = shape.name;

	//Reserve space
	_vertices.resize(shape.mesh.positions.size() / 3);
	_normals.resize(shape.mesh.normals.size() / 3);
	_texCoords.resize(shape.mesh.texcoords.size() / 2);
	_indices.resize(shape.mesh.indices.size() / 3);

	/*Manually copy data*/
	//Declare required iterators
	std::vector<float>::iterator floatIt;
	std::vector<unsigned int>::iterator uintIt;
	std::vector<glm::vec3>::iterator vec3It;
	std::vector<glm::vec2>::iterator vec2It;
	std::vector<glm::uvec3>::iterator uvec3It;

	//Vertices
	floatIt = shape.mesh.positions.begin();
	vec3It = _vertices.begin();
	while (floatIt != shape.mesh.positions.end() && vec3It != _vertices.end()) {
		*vec3It = glm::vec3(*floatIt, *(floatIt + 1), *(floatIt + 2));
		vec3It++;
		floatIt += 3;
	}
	//Normals
	floatIt = shape.mesh.normals.begin();
	vec3It = _normals.begin();
	while (floatIt != shape.mesh.normals.end() && vec3It != _normals.end()) {
		*vec3It = glm::vec3(*floatIt, *(floatIt + 1), *(floatIt + 2));
		vec3It++;
		floatIt += 3;
	}
	//TexCoords
	floatIt = shape.mesh.texcoords.begin();
	vec2It = _texCoords.begin();
	while (floatIt != shape.mesh.texcoords.end() && vec2It != _texCoords.end()) {
		*vec2It = glm::vec2(*floatIt, *(floatIt + 1));
		vec2It++;
		floatIt += 2;
	}
	//Indices
	uintIt = shape.mesh.indices.begin();
	uvec3It = _indices.begin();
	while (uintIt != shape.mesh.indices.end() && uvec3It != _indices.end()) {
		*uvec3It = glm::vec3(*uintIt, *(uintIt + 1), *(uintIt + 2));
		uvec3It++;
		uintIt += 3;
	}
}

std::string const& MeshImpl<MeshType::OBJ>::name() const {
	return _name;
}

std::vector<glm::vec3> const& MeshImpl<MeshType::OBJ>::vertices() const {
	return _vertices;
}

std::vector<glm::vec3> const& MeshImpl<MeshType::OBJ>::normals() const {
	return _normals;
}

std::vector<glm::vec2> const& MeshImpl<MeshType::OBJ>::texCoords() const {
	return _texCoords;
}

std::vector<glm::uvec3> const& MeshImpl<MeshType::OBJ>::indices() const {
	return _indices;
}

std::string const& NullMesh::name() const {
	return _name;
}

std::vector<glm::vec3> const& NullMesh::vertices() const {
	return _vertices;
}

std::vector<glm::vec3> const& NullMesh::normals() const {
	return _normals;
}

std::vector<glm::vec2> const& NullMesh::texCoords() const {
	return _texCoords;
}

std::vector<glm::uvec3> const& NullMesh::indices() const {
	return _indices;
}

MaterialImpl<MaterialType::MTL>::MaterialImpl(tinyobj::material_t material) {
	//Set Data
	setData(material);
}

void MaterialImpl<MaterialType::MTL>::setData(tinyobj::material_t material) {
	_name = material.name;

	_ambient = glm::vec4(material.ambient[0], material.ambient[1], material.ambient[2], 1.0f);
	_diffuse = glm::vec4(material.diffuse[0], material.diffuse[1], material.diffuse[2], 1.0f);
	_specular = glm::vec4(material.specular[0], material.specular[1], material.specular[2], 1.0f);
	_transmittance = glm::vec4(material.transmittance[0], material.transmittance[1], material.transmittance[2], 1.0f);
	_emission = glm::vec4(material.emission[0], material.emission[1], material.emission[2], 1.0f);

	_ambientTexture = material.ambient_texname;
	_diffuseTexture = material.diffuse_texname;
	_specularTexture = material.specular_texname;
	_normalTexture = material.normal_texname;
}

std::string const& MaterialImpl<MaterialType::MTL>::name() const {
	return _name;
}

glm::vec4 const& MaterialImpl<MaterialType::MTL>::ambient() const {
	return _ambient;
}

glm::vec4 const& MaterialImpl<MaterialType::MTL>::diffuse() const {
	return _diffuse;
}

glm::vec4 const& MaterialImpl<MaterialType::MTL>::specular() const {
	return _specular;
}

glm::vec4 const& MaterialImpl<MaterialType::MTL>::transmittance() const {
	return _transmittance;
}

glm::vec4 const& MaterialImpl<MaterialType::MTL>::emission() const {
	return _emission;
}

std::string const& MaterialImpl<MaterialType::MTL>::ambientTexture() const {
	return _ambientTexture;
}

std::string const& MaterialImpl<MaterialType::MTL>::diffuseTexture() const {
	return _diffuseTexture;
}

std::string const& MaterialImpl<MaterialType::MTL>::specularTexture() const {
	return _specularTexture;
}

std::string const& MaterialImpl<MaterialType::MTL>::normalTexture() const {
	return _normalTexture;
}

MaterialImpl<MaterialType::MATERIAL_COLLECTION>::MaterialImpl(Material const& other) :
		Material(), _name(other.name()), _ambient(other.ambient()), _diffuse(other.diffuse()), _specular(other.specular()),
				_transmittance(other.transmittance()), _emission(other.emission()), _ambientTexture(other.ambientTexture()),
				_diffuseTexture(other.diffuseTexture()), _specularTexture(other.specularTexture()), _normalTexture(other.normalTexture()) {

}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setName(std::string const& name) {
	_name = name;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setAmbient(glm::vec4 const& ambient) {
	_ambient = ambient;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setDiffuse(glm::vec4 const& diffuse) {
	_diffuse = diffuse;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setSpecular(glm::vec4 const& specular) {
	_specular = specular;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setTransmittance(glm::vec4 const& transmittance) {
	_transmittance = transmittance;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setEmission(glm::vec4 const& emission) {
	_emission = emission;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setAmbientTexture(std::string const& ambientTexture) {
	_ambientTexture = ambientTexture;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setDiffuseTexture(std::string const& diffuseTexture) {
	_diffuseTexture = diffuseTexture;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setSpecularTexture(std::string const& specularTexture) {
	_specularTexture = specularTexture;
}

void MaterialImpl<MaterialType::MATERIAL_COLLECTION>::setNormalTexture(std::string const& normalTexture) {
	_normalTexture = normalTexture;
}

std::string const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::name() const {
	return _name;
}

glm::vec4 const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::ambient() const {
	return _ambient;
}

glm::vec4 const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::diffuse() const {
	return _diffuse;
}

glm::vec4 const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::specular() const {
	return _specular;
}

glm::vec4 const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::transmittance() const {
	return _transmittance;
}

glm::vec4 const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::emission() const {
	return _emission;
}

std::string const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::ambientTexture() const {
	return _ambientTexture;
}

std::string const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::diffuseTexture() const {
	return _diffuseTexture;
}

std::string const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::specularTexture() const {
	return _specularTexture;
}

std::string const& MaterialImpl<MaterialType::MATERIAL_COLLECTION>::normalTexture() const {
	return _normalTexture;
}

std::string const& NullMaterial::name() const {
	return _name;
}

glm::vec4 const& NullMaterial::ambient() const {
	return _ambient;
}

glm::vec4 const& NullMaterial::diffuse() const {
	return _diffuse;
}

glm::vec4 const& NullMaterial::specular() const {
	return _specular;
}

glm::vec4 const& NullMaterial::transmittance() const {
	return _transmittance;
}

glm::vec4 const& NullMaterial::emission() const {
	return _emission;
}

std::string const& NullMaterial::ambientTexture() const {
	return _ambientTexture;
}

std::string const& NullMaterial::diffuseTexture() const {
	return _diffuseTexture;
}

std::string const& NullMaterial::specularTexture() const {
	return _specularTexture;
}

std::string const& NullMaterial::normalTexture() const {
	return _normalTexture;
}

void MaterialComparator::operator ()(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Compare names
	compNames(dest, src);

	//Compare ambients
	compAmbient(dest, src);
	//Compare diffuses
	compDiffuse(dest, src);
	//Compare speculars
	compSpecular(dest, src);
	//Compare transmittances
	compTransmittance(dest, src);
	//Compare emissions
	compEmission(dest, src);

	//Compare ambientTextures
	compAmbientTexture(dest, src);
	//Compare diffuseTextures
	compDiffuseTexture(dest, src);
	//Compare specularTextures
	compSpecularTexture(dest, src);
	//Compare normalTextures
	compNormalTexture(dest, src);
}

void MaterialComparator::compNames(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty name
	if (!src.name().empty()) {
		//If dest is empty use src
		if (dest.name().empty()) {
			dest.setName(src.name());
		}
		//If not combine both names
		else {
			dest.setName(dest.name() + "|" + src.name());
		}
	}
}

void MaterialComparator::compAmbient(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty ambient
	if (src.ambient() != glm::vec4()) {
		//If dest is empty use src
		if (dest.ambient() == glm::vec4()) {
			dest.setAmbient(src.ambient());
		}
		//If not multiply both values
		else {
			dest.setAmbient(dest.ambient() * src.ambient());
		}
	}
}

void MaterialComparator::compDiffuse(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty diffuse
	if (src.diffuse() != glm::vec4()) {
		//If dest is empty use src
		if (dest.diffuse() == glm::vec4()) {
			dest.setDiffuse(src.diffuse());
		}
		//If not multiply both values
		else {
			dest.setDiffuse(dest.diffuse() * src.diffuse());
		}
	}
}

void MaterialComparator::compSpecular(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty specular
	if (src.specular() != glm::vec4()) {
		//If dest is empty use src
		if (dest.specular() == glm::vec4()) {
			dest.setSpecular(src.specular());
		}
		//If not multiply both values
		else {
			dest.setSpecular(dest.specular() * src.specular());
		}
	}
}

void MaterialComparator::compTransmittance(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty transmittance
	if (src.transmittance() != glm::vec4()) {
		//If dest is empty use src
		if (dest.transmittance() == glm::vec4()) {
			dest.setTransmittance(src.transmittance());
		}
		//If not multiply both values
		else {
			dest.setTransmittance(dest.transmittance() * src.transmittance());
		}
	}
}

void MaterialComparator::compEmission(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty emission
	if (src.emission() != glm::vec4()) {
		//If dest is empty use src
		if (dest.emission() == glm::vec4()) {
			dest.setEmission(src.emission());
		}
		//If not multiply both values
		else {
			dest.setEmission(dest.emission() * src.emission());
		}
	}
}

void MaterialComparator::compAmbientTexture(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty ambientTexture
	if (!src.ambientTexture().empty()) {
		//If dest is empty use src
		if (dest.ambientTexture().empty()) {
			dest.setAmbientTexture(src.ambientTexture());
		}
		//If not keep using dest value
	}
}

void MaterialComparator::compDiffuseTexture(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty diffuseTexture
	if (!src.diffuseTexture().empty()) {
		//If dest is empty use src
		if (dest.diffuseTexture().empty()) {
			dest.setDiffuseTexture(src.diffuseTexture());
		}
		//If not keep using dest value
	}
}

void MaterialComparator::compSpecularTexture(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty specularTexture
	if (!src.specularTexture().empty()) {
		//If dest is empty use src
		if (dest.specularTexture().empty()) {
			dest.setSpecularTexture(src.specularTexture());
		}
		//If not keep using dest value
	}
}

void MaterialComparator::compNormalTexture(MaterialImpl<MaterialType::MATERIAL_COLLECTION>& dest, Material const& src) const {
	//Ignore empty normalTexture
	if (!src.normalTexture().empty()) {
		//If dest is empty use src
		if (dest.normalTexture().empty()) {
			dest.setNormalTexture(src.normalTexture());
		}
		//If not keep using dest value
	}
}

MaterialCollection::MaterialCollection() :
		_material(new NullMaterial(), OpGLLib::default_delete<Material>()) {

}

MaterialCollection::MaterialCollection(std::initializer_list<std::shared_ptr<Material>> init_list) {
	//Add all materials provided by init_list
	for (auto i : init_list) {
		addMaterial(std::move(i));
	}

	//Update resulting material
	update();
}

void MaterialCollection::addMaterial(std::shared_ptr<Material>&& material) {
	_materialList.push_back(std::forward<std::shared_ptr<Material>>(material));
}

void MaterialCollection::update() {
	MaterialComparator comparator;

	//Make sure _materialList isn't empty
	if (!_materialList.empty()) {
		//Construct new _material with first material from _materialList as base
		_material.reset(new MaterialImpl<MaterialType::MATERIAL_COLLECTION>(*_materialList[0]), OpGLLib::default_delete<Material>());
	}
	//Continue with the following materials in _materialList (if any)
	for (size_t i = 1; i < _materialList.size(); i++) {
		//Compare materials
		comparator.operator ()(*std::dynamic_pointer_cast<MaterialImpl<MaterialType::MATERIAL_COLLECTION>>(_material), *_materialList[i]);
	}
}

std::shared_ptr<Material> MaterialCollection::get() const {
	return _material;
}

Model::Model() :
		_name(""), _mesh(new NullMesh(), OpGLLib::default_delete<Mesh>()),
				_materialCollection(new MaterialCollection(), OpGLLib::default_delete<MaterialCollection>()) {

}

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<MaterialCollection> materialCollection) :
		_mesh(mesh), _materialCollection(materialCollection) {
	update();
}

void Model::setMesh(std::shared_ptr<Mesh>&& mesh) {
	_mesh = std::forward<std::shared_ptr<Mesh>>(mesh);
	update();
}

void Model::setMaterial(std::shared_ptr<Material>&& material) {
	_materialCollection->addMaterial(std::forward<std::shared_ptr<Material>>(material));
	_materialCollection->update();
	update();
}

void Model::setMaterialCollection(std::shared_ptr<MaterialCollection>&& materialCollection) {
	_materialCollection = std::forward<std::shared_ptr<MaterialCollection>>(materialCollection);
	update();
}

std::string const& Model::name() const {
	return _name;
}

std::shared_ptr<Mesh> Model::mesh() const {
	return _mesh;
}

std::shared_ptr<Material> Model::material() const {
	return _materialCollection->get();
}

std::shared_ptr<MaterialCollection> Model::materialCollecion() const {
	return _materialCollection;
}

void Model::update() {
	//Update name;
	_name = _mesh->name() + "|" + _materialCollection->get()->name();
}

LoadModelException::LoadModelException(OpGLLibBase const* pointer, std::string const& model, std::string const& reason) :
		Exception(pointer), _model(model), _reason(reason) {

}

ExceptionType LoadModelException::what() {
	return ExceptionType::GL_MODELLOADER_LOADMODEL_EXCEPTION;
}

std::string LoadModelException::toString() {
	return "Unable to load model " + _model + ": " + _reason;
}

bool LoadModelException::handle() {
	getServiceLocator().getLoggingService()->log(toString(), LoggingLevel::unrecoverableError);

	//Assume unrecoverable
	return false;
}

ModelLoaderBase::ModelLoaderBase() :
		OpGLLibBase() {

}

ModelLoaderBase::ModelLoaderBase(OpGLLibBase const* pointer) :
		OpGLLibBase(pointer) {

}

ModelLoader::ModelLoader() :
		ModelLoaderBase() {

}

ModelLoader::ModelLoader(OpGLLibBase const* pointer) :
		ModelLoaderBase(pointer) {

}

std::shared_ptr<Model> ModelLoader::load(std::string const& file) {
	std::shared_ptr<Model> model;
	std::string fileType = files::fileType(file);

	//Log
	getServiceLocator().getLoggingService()->log("Loading model: " + file, LoggingLevel::debug);

	//Get seperate path and filename
	std::string const& path = files::filePath(file);
	//std::string const& filename = files::fileName(file);

	if (fileType == "obj") {
		model = loadObj(file, path);
	} else {
		//Return if unrecoverable
		if (!LoadModelException(this, file, "Unknown file extension ." + fileType).handle()) {
			return std::shared_ptr<Model>(new Model(), OpGLLib::default_delete<Model>());
		}
	}
	return model;
}

std::shared_ptr<Model> ModelLoader::loadObj(std::string const& file, std::string const& basepath) {
	//Construct storage classes
	std::shared_ptr<Model> model(new Model(), OpGLLib::default_delete<Model>());
	std::shared_ptr<Mesh> mesh(new MeshImpl<MeshType::OBJ>(), OpGLLib::default_delete<Mesh>());
	std::shared_ptr<MaterialCollection> materialCollection(new MaterialCollection(), OpGLLib::default_delete<MaterialCollection>());
	std::vector<tinyobj::material_t> materials;
	std::vector<tinyobj::shape_t> shapes;

	//Load obj file
	std::string err = tinyobj::LoadObj(shapes, materials, file.c_str(), basepath.c_str());

	if (!err.empty()) {
		LOG(err, OpGLLib::LoggingLevel::recoverableError);
		return model;
	}

	//Convert data to Mesh
	std::dynamic_pointer_cast<MeshImpl<MeshType::OBJ>>(mesh)->setData(shapes[0]);

	//Use Mesh in Model
	model->setMesh(std::move(mesh));

	//Loop through all materials and fill the materialCollection
	for (auto it = materials.begin(); it != materials.end(); it++) {
		std::shared_ptr<Material> material(new MaterialImpl<MaterialType::MTL>(), OpGLLib::default_delete<Material>());
		std::dynamic_pointer_cast<MaterialImpl<MaterialType::MTL>>(material)->setData(*it);
		materialCollection->addMaterial(std::move(material));
	}

	//Update materialCollection
	materialCollection->update();

	//Use materialCollection in model
	model->setMaterialCollection(std::move(materialCollection));

	return model;
}

NullModelLoader::NullModelLoader() :
		ModelLoaderBase() {

}

NullModelLoader::NullModelLoader(OpGLLibBase const* pointer) :
		ModelLoaderBase(pointer) {

}

std::shared_ptr<Model> NullModelLoader::load(std::string const& file) {
	//Return NullMesh
	return std::shared_ptr<Model>(new Model(), OpGLLib::default_delete<Model>());
}

}
}
