/*
 * ImageManager.cpp
 *
 *  Created on: 25.09.2015
 *      Author: mimoe
 */

#include <OpGLLib/ImageManager.h>

namespace OpGLLib {

ImageManagerBase::ImageManagerBase() :
		OpGLLibBase() {

}

ImageManagerBase::ImageManagerBase(OpGLLibBase const* pointer) :
		OpGLLibBase(pointer) {

}

ImageManager::ImageManager() :
		ImageManagerBase() {

}

ImageManager::ImageManager(OpGLLibBase const* pointer) :
		ImageManagerBase(pointer) {

}

Image<unsigned char> ImageManager::loadPng(std::string const& file, bool cache) const {
	//Check wether image is cached
	if (cache && checkImageCache(file)) {
		return getCachedImage<unsigned char>(file);
	}

	//Load image
	Image<unsigned char> image = _loadPng(file);

	//Cache image if requested
	if (cache) {
		_imageCache[file] = std::experimental::any(image);
	}

	return image;
}

void ImageManager::preloadPng(std::string const& file) {
	loadPng(file, true);
}

bool ImageManager::checkImageCache(std::string const& file) const {
	if (_imageCache.count(file) >= 1) {
		return true;
	}
	return false;
}

void ImageManager::deleteImageCache(std::string const& file) {
	_imageCache.erase(file);
}

Image<unsigned char> ImageManager::_loadPng(std::string const& file) const {
	//Decode png
	std::vector<unsigned char> data;
	unsigned int width, height;
	int errorCode = lodepng::decode(data, width, height, file);
	if (errorCode) {
		getServiceLocator().getLoggingService()->log(
				"Loading" + file + " failed with error: " + lodepng_error_text(errorCode) + "(" + std::to_string(errorCode) + ").",
				LoggingLevel::unrecoverableError);
	}

	//Return Image
	return Image<unsigned char>( { width, height }, std::move(data));
}

Image<unsigned char> NullImageManager::loadPng(std::string const& file, bool cache) const{
	return Image<unsigned char>();
}

void NullImageManager::preloadPng(std::string const& file) {
	return;
}

bool NullImageManager::checkImageCache(std::string const& file) const {
	return false;
}

void NullImageManager::deleteImageCache(std::string const& file) {
	return;
}

}

