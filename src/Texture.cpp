/*
 * Texture.cpp
 *
 *  Created on: 29.01.2015
 *      Author: Michael
 */

#include <OpGLLib/Texture.h>

namespace OpGLLib {

Texture::Texture() :
		textureId(0), target(gl::GLenum::GL_TEXTURE_2D) {

}

Texture::Texture(gl::GLenum target, std::initializer_list<std::pair<gl::GLenum, int>> texParameteri) :
		textureId(0), target(target) {
	for (auto i = texParameteri.begin(); i != texParameteri.end(); i++) {
		textureParameteri[i->first] = i->second;
	}
}

template<class T> Texture::Texture(gl::GLenum target, ImageLoader::Image<T>& image, int level, gl::GLenum internalFormat, gl::GLenum format,
		gl::GLenum type, std::initializer_list<std::pair<gl::GLenum, int>> texParameteri) :
		textureId(0), target(target) {
	setImage(image, level, internalFormat, format, type);
	for (auto i = texParameteri.begin(); i != texParameteri.end(); i++) {
		textureParameteri[i->first] = i->second;
	}
}

void Texture::setTextureId(unsigned int id) {
	textureId = id;
}

unsigned int Texture::getTextureId() {
	return textureId;
}

void Texture::setTexParameteri(gl::GLenum type, int value) {
	textureParameteri[type] = value;
}

void Texture::unsetTexParameteri(gl::GLenum type) {
	textureParameteri.erase(type);
}

void Texture::setTexParameterf(gl::GLenum type, float value) {
	textureParameterf[type] = value;
}

void Texture::unsetTexParameterf(gl::GLenum type) {
	textureParameterf.erase(type);
}

void Texture::setTexParameteriv(gl::GLenum type, const int* value) {
	textureParameteriv[type] = value;
}

void Texture::unsetTexParameteriv(gl::GLenum type) {
	textureParameteriv.erase(type);
}

void Texture::setTexParameterfv(gl::GLenum type, const float* value) {
	textureParameterfv[type] = value;
}

void Texture::unsetTexParameterfv(gl::GLenum type) {
	textureParameterfv.erase(type);
}

std::map<gl::GLenum, int> const& Texture::getTexParameteri() {
	return textureParameteri;
}

std::map<gl::GLenum, float> const& Texture::getTexParameterf() {
	return textureParameterf;
}

std::map<gl::GLenum, const int*> const& Texture::getTexParameteriv() {
	return textureParameteriv;
}

std::map<gl::GLenum, const float*> const& Texture::getTexParameterfv() {
	return textureParameterfv;
}

} /* namespace OpGLLib */
