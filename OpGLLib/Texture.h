/*
 * Texture.h
 *
 *  Created on: 29.01.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_TEXTURE_H_
#define OPGLLIB_TEXTURE_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/ImageLoader.h>

namespace OpGLLib {

struct TextureImage {
	gl::GLenum internalFormat;
	size_t width;
	size_t height;
	gl::GLenum format;
	gl::GLenum type;
	std::shared_ptr<void> data;
};

class Texture {
public:
	Texture();
	Texture(gl::GLenum target, std::initializer_list<std::pair<gl::GLenum, int>> texParameteri);
	template<class T> Texture(gl::GLenum target, ImageLoader::Image<T>& image, int level, gl::GLenum internalFormat, gl::GLenum format,
			gl::GLenum type, std::initializer_list<std::pair<gl::GLenum, int>> texParameteri = { });

	void setTextureId(unsigned int id);
	unsigned int getTextureId();

	template<class T> void setImage(ImageLoader::Image<T>& image, int level, gl::GLenum internalFormat, gl::GLenum format, gl::GLenum type);

	void setTexParameteri(gl::GLenum type, int value);
	void unsetTexParameteri(gl::GLenum type);

	void setTexParameterf(gl::GLenum type, float value);
	void unsetTexParameterf(gl::GLenum type);

	void setTexParameteriv(gl::GLenum type, const int* value);
	void unsetTexParameteriv(gl::GLenum type);

	void setTexParameterfv(gl::GLenum type, const float* value);
	void unsetTexParameterfv(gl::GLenum type);

	std::map<gl::GLenum, int> const& getTexParameteri();
	std::map<gl::GLenum, float> const& getTexParameterf();
	std::map<gl::GLenum, const int*> const& getTexParameteriv();
	std::map<gl::GLenum, const float*> const& getTexParameterfv();
private:
	unsigned int textureId;
	gl::GLenum target;
	std::map<int, TextureImage> imageData;
	std::map<gl::GLenum, int> textureParameteri;
	std::map<gl::GLenum, float> textureParameterf;
	std::map<gl::GLenum, const int*> textureParameteriv;
	std::map<gl::GLenum, const float*> textureParameterfv;
};

} /* namespace OpGLLib */

#include <OpGLLib/Texture.inl>

#endif /* OPGLLIB_TEXTURE_H_ */
