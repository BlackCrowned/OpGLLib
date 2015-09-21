/*
 * GLTypes.cpp
 *
 *  Created on: 24.06.2015
 *      Author: mimoe
 */

#include <OpGLLib/GLTypes.h>


namespace OpGLLib {

namespace gl {

namespace GLTypes {

::gl::GLenum constexpr getType(Types::TypeInfo n) {
	return GLTypeEnums[static_cast<int>(n)];
}

}

}

}
