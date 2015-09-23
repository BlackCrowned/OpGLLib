/*
 * Texture.h
 *
 *  Created on: 28.06.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_TEXTURE_H_
#define OPGLLIB_TEXTURE_H_

#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/OpGLLib.h>
#include <OpGLLib/Image.h>
#include <OpGLLib/GLTypes.h>
#include <OpGLLib/State.h>

#include <type_traits>

namespace OpGLLib {

namespace gl {

class Texture2D {
public:
	//TODO: Copy/Move constructors
	Texture2D();
	template<class T> Texture2D(Image<T>& image, ::gl::GLenum target = ::gl::GL_TEXTURE_2D, int mipmap = 0,
			int internalFormat = (int) ::gl::GL_RGBA, ::gl::GLenum format = ::gl::GL_RGBA);
	~Texture2D();

	void setTarget(::gl::GLenum target);
	template<class T> void setData(Image<T>& image, int mipmap = 0, int internalFormat = ::gl::GL_RGBA, ::gl::GLenum format =
			::gl::GL_RGBA);

	unsigned int getId();

	void bindTexture();

	void generateMipmap();

	template<class T> void texParameteri(::gl::GLenum pname, T param);
	template<class T> void texParameterf(::gl::GLenum pname, T param);

	template<class T> void texParameterfv(::gl::GLenum pname, T params);
	template<class T> void texParameteriv(::gl::GLenum pname, T params);
	template<class T> void texParameterIiv(::gl::GLenum pname, T params);
	template<class T> void texParameterIuiv(::gl::GLenum pname, T params);
private:
	unsigned int _id;
	::gl::GLenum _target;
};

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

#include <OpGLLib/Texture.inl>

#endif /* OPGLLIB_TEXTURE_H_ */
