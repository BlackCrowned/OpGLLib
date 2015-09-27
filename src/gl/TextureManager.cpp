/*
 * TextureManager.cpp
 *
 *  Created on: 26.09.2015
 *      Author: mimoe
 */

#include <OpGLLib/gl/TextureManager.h>

namespace OpGLLib {
namespace gl {

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

Texture2D TextureManager::loadTexture2D(std::string const& file, bool cache) {
	//Check wether texture is cached
	if (cache && checkTextureCache(file)) {
		return getCachedTexture(file);
	}

	//Determine FileType
	std::string const& fileType = files::fileType(file);
	Texture2D texture;
	if (fileType == "png") {
		Image<unsigned char> img = getServiceLocator().getImageManagerService()->loadPng(file, false);
		texture.setData(img);
	}
	else {
		getServiceLocator().getLoggingService()->log("TextureManager::loadTexture2D: " + fileType + "-files not supported.", LoggingLevel::unrecoverableError);
	}

	//If requested, cache texture
	if (cache) {
		_textureCache[file] = texture;
	}

	return texture;
}

void TextureManager::preloadTexture2D(std::string const& file) {
	loadTexture2D(file);
}

bool TextureManager::checkTextureCache(std::string const& file) {
	return (_textureCache.count(file) > 0 ? true : false);
}

Texture2D TextureManager::getCachedTexture(std::string const& file) {
	return _textureCache[file];
}

NullTextureManager::NullTextureManager() :
		TextureManagerBase() {

}

NullTextureManager::NullTextureManager(OpGLLibBase const* pointer) :
		TextureManagerBase(pointer) {

}

Texture2D NullTextureManager::loadTexture2D(std::string const& file, bool cache) {
	return Texture2D();
}

void NullTextureManager::preloadTexture2D(std::string const& file) {
	return;
}

bool NullTextureManager::checkTextureCache(std::string const& file) {
	return false;
}

}
}


