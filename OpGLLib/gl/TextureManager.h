/*
 * TextureManager.h
 *
 *  Created on: 26.09.2015
 *      Author: mimoe
 */

#ifndef GL_TEXTUREMANAGER_H_
#define GL_TEXTUREMANAGER_H_

#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/OpGLLib.h>
#include <OpGLLib/gl/Texture.h>

#include <string>
#include <map>


namespace OpGLLib {
namespace gl {

class TextureManagerBase: public OpGLLibBase {
public:
	TextureManagerBase();
	TextureManagerBase(OpGLLibBase const* pointer);
	virtual ~TextureManagerBase() = default;

	virtual Texture2D loadTexture2D(std::string file, bool cache = true) = 0;
	virtual void preloadTexture2D(std::string file) = 0;

	virtual bool checkTextureCache(std::string file) = 0;
};

class TextureManager : public TextureManagerBase {
public:
	TextureManager();
	TextureManager(OpGLLibBase const* pointer);
	virtual ~TextureManager() = default;

	virtual Texture2D loadTexture2D(std::string file, bool cache = true);
	virtual void preloadTexture2D(std::string file);

	virtual bool checkTextureCache(std::string file);

private:
	template<class T> Image<T> getImage(std::string file);

	Texture2D getCachedTexture(std::string file);

	std::map<std::string, Texture2D> _textureCache;
};

class NullTextureManager : public TextureManagerBase {
public:
	NullTextureManager();
	NullTextureManager(OpGLLibBase const* pointer);
	virtual ~NullTextureManager() = default;

	virtual Texture2D loadTexture2D(std::string file, bool cache = true);
	virtual void preloadTexture2D(std::string file);

	virtual bool checkTextureCache(std::string file);
};

}
}

#endif /* GL_TEXTUREMANAGER_H_ */
