/*
 * Texture.inl
 *
 *  Created on: 28.06.2015
 *      Author: mimoe
 */

namespace OpGLLib {

namespace gl {

template<class T> Texture2D::Texture2D(ImageLoader::Image<T>& image, ::gl::GLenum target, int mipmap, int internalFormat,
		::gl::GLenum format) {
	//Create GLTexture
	::gl::glGenTextures(1, &_id);

	//Set target
	setTarget(target);

	//Set data
	setData(image, mipmap, internalFormat, format);
}

template<class T> void Texture2D::setData(ImageLoader::Image<T>& image, int mipmap, int internalFormat, ::gl::GLenum format) {
	//Bind Texture
	bind();

	//Upload ImageData
	ImageLoader::Dimensions dimensions = image.getDimensions();
	::gl::glTexImage2D(_target, mipmap, internalFormat, dimensions.width, dimensions.height, 0, format, GLTypes::getType<T>(),
			&image.get()[0]);
}

template<class T> void Texture2D::texParameteri(::gl::GLenum pname, T param) {
	//Bind Texture
	bind();

	//Set Texture Parameter
	::gl::glTexParameteri(_target, pname, static_cast<int>(param));
}

template<class T> void Texture2D::texParameterf(::gl::GLenum pname, T param) {
	//Bind Texture
	bind();

	//Set Texture Parameter
	::gl::glTexParameterf(_target, pname, static_cast<float>(param));
}

template<class T> void Texture2D::texParameterfv(::gl::GLenum pname, T params) {
	//Bind Texture
	bind();

	//Set Texture Parameter
	::gl::glTexParameterfv(_target, pname, static_cast<float const*>(params));
}

template<class T> void Texture2D::texParameteriv(::gl::GLenum pname, T params) {
	//Bind Texture
	bind();

	//Set Texture Parameter
	::gl::glTexParameteriv(_target, pname, static_cast<int const*>(params));
}

template<class T> void Texture2D::texParameterIiv(::gl::GLenum pname, T params) {
	//Bind Texture
	bind();

	//Set Texture Parameter
	::gl::glTexParameterIiv(_target, pname, static_cast<int const*>(params));
}

template<class T> void Texture2D::texParameterIuiv(::gl::GLenum pname, T params) {
	//Bind Texture
	bind();

	//Set Texture Parameter
	::gl::glTexParameterIuiv(_target, pname, static_cast<unsigned int const*>(params));
}

}

}

