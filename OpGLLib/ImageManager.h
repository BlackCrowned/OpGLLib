/*
 * ImageManager.h
 *
 *  Created on: 23.09.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_IMAGEMANAGER_H_
#define OPGLLIB_IMAGEMANAGER_H_

#include <OpGLLib/OpGLLib.h>
#include <OpGLLib/Image.h>
#include <OpGLLib/FileLoader.h>
#include <OpGLLib/ServiceLocator.h>

#include <string>
#include <map>

namespace OpGLLib {

class ImageManagerBase : public OpGLLibBase{
public:
	ImageManagerBase();
	ImageManagerBase(OpGLLibBase const* pointer);
	virtual ~ImageManagerBase() = default;

	virtual Image<unsigned char> loadPng(std::string const& file, bool cache = false) const = 0;
	virtual void preloadPng(std::string const& file) = 0;

	virtual bool checkImageCache(std::string const& file) const = 0;
	virtual void deleteImageCache(std::string const& file) = 0;
};

class ImageManager : public ImageManagerBase {
public:
	ImageManager();
	ImageManager(OpGLLibBase const* pointer);
	virtual ~ImageManager() = default;

	virtual Image<unsigned char> loadPng(std::string const& file, bool cache = false) const;
	virtual void preloadPng(std::string const& file);

	virtual bool checkImageCache(std::string const& file) const;
	virtual void deleteImageCache(std::string const& file);

private:
	Image<unsigned char> _loadPng(std::string const& file) const;

	template<class T = unsigned char> Image<T> const& getCachedImage(std::string const& file) const;


	mutable std::map<std::string, Image<unsigned char>> _imageCache;
};
template<> Image<unsigned char> const& ImageManager::getCachedImage(std::string const& file) const;

class NullImageManager : public ImageManagerBase {
public:
	NullImageManager();
	NullImageManager(OpGLLibBase const* pointer);
	virtual ~NullImageManager() = default;

	virtual Image<unsigned char> loadPng(std::string const& file, bool cache = false) const;
	virtual void preloadPng(std::string const& file);

	virtual bool checkImageCache(std::string const& file) const;
	virtual void deleteImageCache(std::string const& file);

};

}

#include <OpGLLib/ImageManager.inl>

#endif /* OPGLLIB_IMAGEMANAGER_H_ */
