/*
 * States.cpp
 *
 *  Created on: 23.07.2015
 *      Author: mimoe
 */

#include <OpGLLib/gl/States.h>

namespace OpGLLib {
namespace gl {

void States::enableCulling(::gl::GLenum CullFace, ::gl::GLenum FrontFace) {
	::gl::glEnable(::gl::GL_CULL_FACE);
	glCullFace(CullFace);
	glFrontFace(FrontFace);
}

void States::disableCulling() {
	::gl::glDisable(::gl::GL_CULL_FACE);
}

void States::enableDepthTest(::gl::GLboolean DepthMasc, ::gl::GLenum DepthFunc) {
	::gl::glEnable(::gl::GL_DEPTH_TEST);
	::gl::glDepthMask(DepthMasc);
	::gl::glDepthFunc(DepthFunc);
}

void States::disableDepthTest() {
	::gl::glDisable(::gl::GL_DEPTH_TEST);
}

}
}

