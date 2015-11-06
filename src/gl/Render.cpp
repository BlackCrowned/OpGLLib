/*
 * Render.cpp
 *
 *  Created on: 10.01.2015
 *      Author: Michael
 */

#include <OpGLLib/gl/Render.h>

using namespace std;
using namespace gl;

namespace OpGLLib {
namespace gl {

ModelRenderSettings::ModelRenderSettings() :
		_modelSettings(), _materialSettings() {

}

ModelRenderSettings::ModelRenderSettings(std::initializer_list<std::pair<ModelData, ModelRenderSetting>> init_list) {
	for (auto it = init_list.begin(); it != init_list.end(); it++) {
		_modelSettings.insert(*it);
	}
}

ModelRenderSettings::ModelRenderSettings(std::initializer_list<std::pair<MaterialData, ModelRenderSetting>> init_list) {
	for (auto it = init_list.begin(); it != init_list.end(); it++) {
		_materialSettings.insert(*it);
	}
}

ModelRenderSettings::ModelRenderSettings(std::map<ModelData, ModelRenderSetting> modelSetting,
		std::map<MaterialData, ModelRenderSetting> materialSetting) :
		_modelSettings(modelSetting), _materialSettings(materialSetting) {

}

bool ModelRenderSettings::indexDraw(bool indexDraw) {
	_indexDraw = indexDraw;
	return _indexDraw;
}

bool ModelRenderSettings::indexDraw() const {
	return _indexDraw;
}

void ModelRenderSettings::addSetting(std::pair<ModelData, ModelRenderSetting> modelSetting) {
	_modelSettings.insert(modelSetting);
}

void ModelRenderSettings::addSetting(ModelData modelData, ModelRenderSetting modelSetting) {
	_modelSettings[modelData] = modelSetting;
}

void ModelRenderSettings::addSetting(std::pair<MaterialData, ModelRenderSetting> materialSetting) {
	_materialSettings.insert(materialSetting);
}

void ModelRenderSettings::addSetting(MaterialData materialData, ModelRenderSetting materialSetting) {
	_materialSettings[materialData] = materialSetting;
}

void ModelRenderSettings::removeSetting(ModelData modelData) {
	_modelSettings.erase(modelData);
}

void ModelRenderSettings::removeSetting(MaterialData materialData) {
	_materialSettings.erase(materialData);
}

ModelRenderSetting ModelRenderSettings::getSetting(ModelData modelData) const {
	//Only return settings if they exist.
	if (_modelSettings.count(modelData) > 0) {
		return _modelSettings.at(modelData);
	}
	//Otherwise assume disabled dataMembers
	else {
		ModelRenderSetting setting;
		setting.enabled = false;
		return setting;
	}
}

ModelRenderSetting ModelRenderSettings::getSetting(MaterialData materialData) const {
	//Only return settings if they exist.
	if (_materialSettings.count(materialData) > 0) {
		return _materialSettings.at(materialData);
	}
	//Otherwise assume disabled dataMembers
	else {
		ModelRenderSetting setting;
		setting.enabled = false;
		return setting;
	}
}

Render::Render() :
		_context(glbinding::getCurrentContext()), _vertexArrayObject(State::genVertexArray()), _bufferSettings(), _drawSettings() {

}

Render::~Render() {
	//Delete VAO
	State::deleteVertexArray(_vertexArrayObject, _context);

	//Delete Buffers
	for (auto i : _bufferSettings) {
		State::deleteBuffer(i.first);
	}

	//Automatic destruction of other objects
}

unsigned int Render::setVertexArrayObject(unsigned int vao) {
	State::deleteVertexArray(_vertexArrayObject, _context);
	if (vao == 0) {
		vao = State::genVertexArray(_context);
	}
	_vertexArrayObject = vao;
	return vao;
}

void Render::bindVertexArrayObject() {
	State::bindVertexArray(_vertexArrayObject, _context);
}

void Render::bindBuffer(::gl::GLenum target, unsigned int& buffer) {
	State::bindBuffer(target, buffer);
}

void Render::setVertexAttribute(unsigned int index, unsigned int vertexBuffer, ::gl::GLboolean normalize, size_t stride,
		const void* offset, int start) {

	//Bind VAO
	bindVertexArrayObject();
	//Bind Vertex Buffer
	bindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	//Enable Array and set data
	glEnableVertexAttribArray(index);
	//TODO
	std::shared_ptr<Data::VertexSettings> vertexSettings = Data::getBufferSettings(vertexBuffer)->vertexSettings;
	glVertexAttribPointer(index, vertexSettings->vectorLength, vertexSettings->valueType, normalize, stride, offset);
//	glVertexAttribPointer(index, _bufferSettings[vertexBuffer].vectorLength, _bufferSettings[vertexBuffer].valueType, normalize, stride,
//				offset);

//Update Draw details
//TODO
	updateDrawSettings(0, vertexSettings->vertexCount);
	updateDrawSettings(0, _bufferSettings[vertexBuffer].vertexCount);
}

void Render::setVertexAttribute(unsigned int index, unsigned int vertexBuffer, unsigned int indexBuffer, ::gl::GLboolean normalize,
		size_t stride, const void* offset, const void* indicies) {
	//Bind VAO
	bindVertexArrayObject();
	//Bind Vertex Buffer
	bindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	//Enable Array and set data
	glEnableVertexAttribArray(index);
	//TODO
	std::shared_ptr<Data::VertexSettings> vertexSettings = Data::getBufferSettings(vertexBuffer)->vertexSettings;
	glVertexAttribPointer(index, vertexSettings->vectorLength, vertexSettings->valueType, normalize, stride, offset);
//	glVertexAttribPointer(index, _bufferSettings[vertexBuffer].vectorLength, _bufferSettings[vertexBuffer].valueType, normalize, stride,
//				offset);

//Bind Index Buffer
	bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	//Update Draw details
	//TODO
	std::shared_ptr<Data::VertexSettings> indexSettings = Data::getBufferSettings(indexBuffer)->vertexSettings;
	updateDrawSettings(indexSettings->vertexCount * indexSettings->vectorLength, indexSettings->valueType, indicies);
//	updateDrawSettings(_bufferSettings[indexBuffer].vertexCount * _bufferSettings[indexBuffer].vectorLength,
//			_bufferSettings[indexBuffer].valueType, indicies);
}

void Render::enableVertexAttribute(unsigned int index) {
	bindVertexArrayObject();

	glEnableVertexAttribArray(index);
}

void Render::disableVertexAttribute(unsigned int index) {
	bindVertexArrayObject();

	glDisableVertexAttribArray(index);
}

void Render::setTexture2D(unsigned int textureUnit, Texture2D texture, int sampler2DLocation) {
	_texture2Ds[textureUnit] = texture;
	_sampler2Ds[textureUnit] = sampler2DLocation;

	_drawSettings.texture2DCount++;
}

void Render::setTexture2D(GLenum textureUnit, Texture2D texture, int sampler2DLocation) {
	_texture2Ds[static_cast<unsigned int>(textureUnit)] = texture;
	_sampler2Ds[static_cast<unsigned int>(textureUnit)] = sampler2DLocation;

	_drawSettings.texture2DCount++;
}

void Render::unsetTexture2D(unsigned int textureUnit) {
	//Make sure elements have been erased before decreasing counter
	if (_texture2Ds.erase(textureUnit) > 0) {
		_drawSettings.texture2DCount--;
	}
}

void Render::unsetTexture2D(GLenum textureUnit) {
	//Make sure elements have been erased before decreasing counter
	if (_texture2Ds.erase(static_cast<unsigned int>(textureUnit)) > 0) {
		_drawSettings.texture2DCount--;
	}
}

void Render::loadModel(std::shared_ptr<Model> model, ModelRenderSettings const& settings) {
	unsigned int indexBuffer, vertexBuffer, normalBuffer, texCoordBuffer;

	//Load indicies
	ModelRenderSetting indexSettings = settings.getSetting(ModelData::indices);
	if (settings.indexDraw()) {
		indexBuffer = setIndexBuffer(model->mesh()->indices(), GL_UNSIGNED_INT, indexSettings.usage);
	}

	//Load vertexData
	ModelRenderSetting vertexSettings = settings.getSetting(ModelData::vertices);
	if (vertexSettings.enabled) {
		vertexBuffer = setVertexBuffer(model->mesh()->vertices(), GL_FLOAT, vertexSettings.usage);
	}

	//Load normals
	ModelRenderSetting normalSettings = settings.getSetting(ModelData::normals);
	if (normalSettings.enabled) {
		normalBuffer = setVertexBuffer(model->mesh()->normals(), GL_FLOAT, normalSettings.usage);
	}
	//Load texCoords
	ModelRenderSetting texCoordSettings = settings.getSetting(ModelData::texCoords);
	if (texCoordSettings.enabled) {
		texCoordBuffer = setVertexBuffer(model->mesh()->texCoords(), GL_FLOAT, vertexSettings.usage);
	}

	//Load materials //TODO
	loadMaterial(model->materialCollecion()->get(), settings);

	//Use indexed drawing
	if (settings.indexDraw()) {
		if (vertexSettings.enabled) {
			setVertexAttribute(vertexSettings.vertexAttribute, vertexBuffer, indexBuffer, vertexSettings.normalize, vertexSettings.stride,
					vertexSettings.offset, vertexSettings.indices);
		}
		if (normalSettings.enabled) {
			setVertexAttribute(normalSettings.vertexAttribute, normalBuffer, indexBuffer, normalSettings.normalize, normalSettings.stride,
					normalSettings.offset, normalSettings.indices);
		}
		if (texCoordSettings.enabled) {
			setVertexAttribute(texCoordSettings.vertexAttribute, texCoordBuffer, indexBuffer, texCoordSettings.normalize,
					texCoordSettings.stride, texCoordSettings.offset, texCoordSettings.indices);
		}
	}
	//No indexed drawing
	else {
		if (vertexSettings.enabled) {
			setVertexAttribute(vertexSettings.vertexAttribute, vertexBuffer, vertexSettings.normalize, vertexSettings.stride,
					vertexSettings.offset, vertexSettings.start);
		}
		if (normalSettings.enabled) {
			setVertexAttribute(normalSettings.vertexAttribute, normalBuffer, normalSettings.normalize, normalSettings.stride,
					normalSettings.offset, normalSettings.start);
		}
		if (texCoordSettings.enabled) {
			setVertexAttribute(texCoordSettings.vertexAttribute, texCoordBuffer, texCoordSettings.normalize, texCoordSettings.stride,
					texCoordSettings.offset, texCoordSettings.start);
		}
	}
}

void Render::loadMaterial(std::shared_ptr<Material> material, ModelRenderSettings const& settings) {
	int ambientBuffer, diffuseBuffer, specularBuffer, transmittanceBuffer, emissionBuffer;
	unsigned int ambientTexture, diffuseTexture, specularTexture, normalTexture;

	//Load ambient
	ModelRenderSetting ambientSettings = settings.getSetting(MaterialData::ambient);
	if (ambientSettings.enabled) {
		//ambientBuffer = setVertexBuffer(material->ambient(), GL_FLOAT, ambientSettings.usage);
	}

	//Load diffuse
	ModelRenderSetting diffuseSettings = settings.getSetting(MaterialData::diffuse);
	if (diffuseSettings.enabled) {
		//diffuseBuffer = setVertexBuffer(material->diffuse(), GL_FLOAT, diffuseSettings.usage);
	}

	//Load specular
	ModelRenderSetting specularSettings = settings.getSetting(MaterialData::specular);
	if (specularSettings.enabled) {
		//specularBuffer = setVertexBuffer(material->specular(), GL_FLOAT, specularSettings.usage);
	}

	//Load transmittance
	ModelRenderSetting transmittanceSettings = settings.getSetting(MaterialData::transmittance);
	if (transmittanceSettings.enabled) {
		//transmittanceBuffer = setVertexBuffer(material->transmittance(), GL_FLOAT, transmittanceSettings.usage);
	}

	//Load emission
	ModelRenderSetting emissionSettings = settings.getSetting(MaterialData::emission);
	if (emissionSettings.enabled) {
		//emissionBuffer = setVertexBuffer(material->emission(), GL_FLOAT, emissionSettings.usage);
	}

	//Load ambientTexture	//TODO

	//Load diffuseTexture	//TODO

	//Load specularTexture	//TODO

	//Load normalTexture	//TODO
}

void Render::updateDrawSettings(GLenum mode) {
	_drawSettings.mode = mode;
}

void Render::updateDrawSettings(int first, int count) {
	_drawSettings.indexedDraw = false;
	_drawSettings.first = first;
	_drawSettings.count = count;
}

void Render::updateDrawSettings(int count, GLenum type, const void* indicies) {
	_drawSettings.indexedDraw = true;
	_drawSettings.indiciesCount = count;
	_drawSettings.indiciesType = type;
	_drawSettings.indicies = indicies;
}

void Render::updateDrawSettings(bool indexedDraw) {
	_drawSettings.indexedDraw = indexedDraw;
}

void Render::enableTextures() {
	_drawSettings.textures = true;
}

void Render::disableTextures() {
	_drawSettings.textures = false;
}

void Render::draw() {
	//Bind VAO
	bindVertexArrayObject();

	//Bind Textures
	if (_drawSettings.textures) {
		if (_drawSettings.texture2DCount > 0) {
			for (auto it = _texture2Ds.begin(); it != _texture2Ds.end(); it++) {
				//Select textureUnit
				glActiveTexture(static_cast<GLenum>(it->first));
				//Bind Texture
				it->second.bindTexture();
				//Upload active texture to sampler2D
				glUniform1i(_sampler2Ds[it->first], static_cast<int>(it->first) - static_cast<int>(GL_TEXTURE0));
			}
		}
	}

	//Draw
	if (_drawSettings.indexedDraw) {
		glDrawElements(_drawSettings.mode, _drawSettings.indiciesCount, _drawSettings.indiciesType, _drawSettings.indicies);
	} else {
		glDrawArrays(_drawSettings.mode, _drawSettings.first, _drawSettings.count);
	}
}

}
}

