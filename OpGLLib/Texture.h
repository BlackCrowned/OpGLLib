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

#include <OpGLLib/ImageLoader.h>
#include <OpGLLib/GLTypes.h>

#include <type_traits>

namespace OpGLLib {

namespace gl {

class Texture2D {
public:
	Texture2D();
	template<class T> Texture2D(ImageLoader::Image<T>& image, ::gl::GLenum target = ::gl::GL_TEXTURE_2D, int mipmap = 0,
			int internalFormat = (int) ::gl::GL_RGBA, ::gl::GLenum format = ::gl::GL_RGBA);
	~Texture2D();

	void setTarget(::gl::GLenum target);
	template<class T> void setData(ImageLoader::Image<T>& image, int mipmap = 0, int internalFormat = ::gl::GL_RGBA, ::gl::GLenum format =
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

}

}

#include <OpGLLib/Texture.inl>

#endif /* OPGLLIB_TEXTURE_H_ */
