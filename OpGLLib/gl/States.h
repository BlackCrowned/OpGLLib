/*
 * States.h
 *
 *  Created on: 23.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_GL_STATES_H_
#define OPGLLIB_GL_STATES_H_

#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

namespace OpGLLib {
namespace gl {
class States {
public:
	States() = delete;
	~States() = delete;

	static void enableCulling(::gl::GLenum CullFace = ::gl::GL_BACK, ::gl::GLenum FrontFace = ::gl::GL_CCW);
	static void disableCulling();
	static void enableDepthTest(::gl::GLboolean DepthMasc = ::gl::GL_TRUE, ::gl::GLenum DepthFunc = ::gl::GL_LEQUAL);
	static void disableDepthTest();

private:
};
}
}

#endif /* OPGLLIB_GL_STATES_H_ */
