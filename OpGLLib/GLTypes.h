/*
 * GLTypes.h
 *
 *  Created on: 24.06.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_GLTYPES_H_
#define OPGLLIB_GLTYPES_H_

#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/Types.h>

#include <array>

namespace OpGLLib {

namespace gl {

namespace GLTypes {

constexpr std::array<::gl::GLenum, static_cast<int>(Types::TypeInfo::TYPEINFO_SIZE) + 1> GLTypeEnums = { ::gl::GL_INVALID_ENUM, //UNDEFINED
		::gl::GL_INVALID_ENUM, 		//VOID
		::gl::GL_BOOL,				//BOOL
		::gl::GL_SHORT,				//SHORT INT
		::gl::GL_UNSIGNED_SHORT,	//UNSIGNED SHORT INT
		::gl::GL_INT,				//INT
		::gl::GL_UNSIGNED_INT,		//UNSIGNED INT
		::gl::GL_INT,				//LONG INT
		::gl::GL_UNSIGNED_INT,		//UNSIGNED LONG INT
		::gl::GL_INT,				//LONG LONG INT
		::gl::GL_UNSIGNED_INT,		//UNSIGNED LONG LONG INT
		::gl::GL_FLOAT,				//FLOAT
		::gl::GL_DOUBLE,			//DOUBLE
		::gl::GL_DOUBLE,			//LONG DOUBLE
		::gl::GL_BYTE,				//CHAR
		::gl::GL_UNSIGNED_BYTE,		//UNSIGNED CHAR
		::gl::GL_INVALID_ENUM		//WCHAR_T

		};

template<class T> constexpr ::gl::GLenum getType();
template<Types::TypeInfo N> constexpr ::gl::GLenum getType();
::gl::GLenum constexpr getType(Types::TypeInfo n);

}

}

}

#include <OpGLLib/GLTypes.inl>

#endif /* OPGLLIB_GLTYPES_H_ */
