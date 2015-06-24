/*
 * GLTypes.inl
 *
 *  Created on: 24.06.2015
 *      Author: mimoe
 */


namespace OpGLLib {

namespace gl {

namespace GLTypes {

template<class T> constexpr ::gl::GLenum getType() {
	return GLTypeEnums[static_cast<int>(Types::getType<T>())];
}

template<Types::TypeInfo N> constexpr ::gl::GLenum getType() {
	return GLTypeEnums[static_cast<int>(N)];
}

}

}

}
