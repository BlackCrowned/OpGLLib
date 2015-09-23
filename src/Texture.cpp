/*
 * Texture.cpp
 *
 *  Created on: 28.06.2015
 *      Author: mimoe
 */

#include <OpGLLib/Texture.h>

namespace OpGLLib {

namespace gl {

Texture2D::Texture2D() {
	//Create GLTexture
	_id = State::genTexture();

	//Set default target
	_target = ::gl::GL_TEXTURE_2D;
}

Texture2D::~Texture2D() {
	//Delete GLTexture
	State::deleteTexture(_id);
}

void Texture2D::setTarget(::gl::GLenum target) {
	_target = target;
}

unsigned int Texture2D::getId() {
	//Return TextureID
	return _id;
}

void Texture2D::bindTexture() {
	//Bind Texture as target
	State::bindTexture(_target, _id);
}

void Texture2D::generateMipmap() {
	//Bind Texture
	bindTexture();

	//Generate Mipmap
	::gl::glGenerateMipmap(_target);
}

TextureManagerBase::TextureManagerBase() :
		OpGLLibBase() {

}

TextureManagerBase::TextureManagerBase(OpGLLibBase const* pointer) :
		OpGLLibBase(pointer) {

}

TextureManager::TextureManager() :
		TextureManagerBase(), _textureCache() {

}

TextureManager::TextureManager(OpGLLibBase const* pointer) :
		TextureManagerBase(pointer), _textureCache() {

}

Texture2D TextureManager::loadTexture2D(std::string file, bool cache) {
	//Check wether texture is cached
	if (cache && checkTextureCache(file)) {
		return getCachedTexture(file);
	}

	//Texture needs to be loaded
	//TODO: Call to an ImageManager

	//Generate Texture // TODO: Add arguments
	Texture2D texture;

	//If requested, cache texture
	if (cache) {
		_textureCache[file] = texture;
	}

	return texture;
}

void TextureManager::preloadTexture2D(std::string file) {
	loadTexture2D(file);
}

bool TextureManager::checkTextureCache(std::string file) {
	return (_textureCache.count(file) > 0 ? true : false);
}

Texture2D TextureManager::getCachedTexture(std::string file) {
	return _textureCache[file];
}

NullTextureManager::NullTextureManager() :
		TextureManagerBase() {

}

NullTextureManager::NullTextureManager(OpGLLibBase const* pointer) :
		TextureManagerBase(pointer) {

}

Texture2D NullTextureManager::loadTexture2D(std::string file, bool cache) {
	return Texture2D();
}

void NullTextureManager::preloadTexture2D(std::string file) {
	return;
}

bool NullTextureManager::checkTextureCache(std::string file) {
	return false;
}

}

}
