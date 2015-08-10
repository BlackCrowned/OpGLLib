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

Model::Model() :
		_mesh(new NullMesh(), OpGLLib::default_delete<Mesh>()) {

}

Model::Model(std::shared_ptr<Mesh> mesh) :
		_mesh(mesh) {

}

void Model::setMesh(std::shared_ptr<Mesh>&& mesh) {
	_mesh = std::forward<std::shared_ptr<Mesh>>(mesh);
}

std::string const& Model::name() const {
	return _mesh->name();
}

std::shared_ptr<Mesh> Model::mesh() const{
	return _mesh;
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

std::shared_ptr<Model> ModelLoader::load(std::string const& modelfile) {
	std::shared_ptr<Model> model;
	std::string fileType = modelfile.substr(modelfile.find_last_of('.') + 1);

	//Log
	getServiceLocator().getLoggingService()->log("Loading model: " + modelfile, LoggingLevel::debug);

	if (fileType == "obj") {
		model = loadObj(modelfile);
	} else {
		//Return if unrecoverable
		if (!LoadModelException(this, modelfile, "Unknown file extension ." + fileType).handle()) {
			return std::shared_ptr<Model>(new Model(), OpGLLib::default_delete<Model>());
		}
	}
	return model;
}

std::shared_ptr<Model> ModelLoader::loadObj(std::string const& modelfile) {
	//Construct storage classes
	std::shared_ptr<Model> model(new Model(), OpGLLib::default_delete<Model>());
	std::shared_ptr<MeshImpl<MeshType::OBJ>> mesh(new MeshImpl<MeshType::OBJ>(), OpGLLib::default_delete<MeshImpl<MeshType::OBJ>>());
	std::vector<tinyobj::material_t> materials;
	std::vector<tinyobj::shape_t> shapes;

	//Load obj file
	std::string err = tinyobj::LoadObj(shapes, materials, modelfile.c_str());

	if (!err.empty()) {
		LOG(err, OpGLLib::LoggingLevel::recoverableError);
		return model;
	}

	//Convert data to Mesh
	mesh->setData(shapes[0]);

	//Use Mesh in Model
	model->setMesh(mesh);

	return model;
}

NullModelLoader::NullModelLoader() :
		ModelLoaderBase() {

}

NullModelLoader::NullModelLoader(OpGLLibBase const* pointer) :
		ModelLoaderBase(pointer) {

}

std::shared_ptr<Model> NullModelLoader::load(std::string const& model) {
	//Return NullMesh
	return std::shared_ptr<Model>(new Model(), OpGLLib::default_delete<Model>());
}

}
}
