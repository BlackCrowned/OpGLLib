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

}

}
