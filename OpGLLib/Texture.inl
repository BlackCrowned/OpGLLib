/*
 * Texture.inl
 *
 *  Created on: 12.02.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_TEXTURE_INL_
#define OPGLLIB_TEXTURE_INL_


namespace OpGLLib {

template<class T> void Texture::setImage(ImageLoader::Image<T>& image, int level, gl::GLenum internalFormat, gl::GLenum format,
		gl::GLenum type) {
	ImageLoader::Dimensions dims = image.getDimensions();
	imageData[level] = {internalFormat, dims.width, dims.height, format, type, image.getData()};
}
}


#endif /* OPGLLIB_TEXTURE_INL_ */
