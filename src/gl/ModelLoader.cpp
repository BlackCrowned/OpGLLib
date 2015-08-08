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

std::string& MeshImpl<MeshType::OBJ>::name() {
	return _name;
}

std::vector<glm::vec3>& MeshImpl<MeshType::OBJ>::vertices() {
	return _vertices;
}

std::vector<glm::vec3>& MeshImpl<MeshType::OBJ>::normals() {
	return _normals;
}

std::vector<glm::vec2>& MeshImpl<MeshType::OBJ>::texCoords() {
	return _texCoords;
}

std::vector<glm::uvec3>& MeshImpl<MeshType::OBJ>::indices() {
	return _indices;
}

std::string& NullMesh::name() {
	return _name;
}

std::vector<glm::vec3>& NullMesh::vertices() {
	return _vertices;
}

std::vector<glm::vec3>& NullMesh::normals() {
	return _normals;
}

std::vector<glm::vec2>& NullMesh::texCoords() {
	return _texCoords;
}

std::vector<glm::uvec3>& NullMesh::indices() {
	return _indices;
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

std::shared_ptr<Mesh> ModelLoader::load(std::string const& model) {
	std::shared_ptr<Mesh> mesh;
	std::string fileType = model.substr(model.find_last_of('.') + 1);

	//Log
	getServiceLocator().getLoggingService()->log("Loading model: " + model, LoggingLevel::debug);

	if (fileType == "obj") {
		mesh = loadObj(model);
	} else {
		//Return if unrecoverable
		if (!LoadModelException(this, model, "Unknown file extension ." + fileType).handle()) {
			return std::shared_ptr<Mesh>(new NullMesh(), OpGLLib::default_delete<Mesh>());
		}
	}
	return mesh;
}

std::shared_ptr<MeshImpl<MeshType::OBJ>> ModelLoader::loadObj(std::string const& model) {
	std::shared_ptr<MeshImpl<MeshType::OBJ>> mesh(new MeshImpl<MeshType::OBJ>(), OpGLLib::default_delete<MeshImpl<MeshType::OBJ>>());
	std::vector<tinyobj::material_t> materials;
	std::vector<tinyobj::shape_t> shapes;

	std::string err = tinyobj::LoadObj(shapes, materials, model.c_str());

	if (!err.empty()) {
		LOG(err, OpGLLib::LoggingLevel::recoverableError);
		return mesh;
	}

	mesh->setData(shapes[0]);

	return mesh;
}

NullModelLoader::NullModelLoader() :
		ModelLoaderBase() {

}

NullModelLoader::NullModelLoader(OpGLLibBase const* pointer) :
		ModelLoaderBase(pointer) {

}

std::shared_ptr<Mesh> NullModelLoader::load(std::string const& model) {
	//Return NullMesh
	return std::shared_ptr<Mesh>(new NullMesh(), OpGLLib::default_delete<Mesh>());
}

}
}
