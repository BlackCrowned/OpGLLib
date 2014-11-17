/*
 * OpGLLib.h
 *
 *  Created on: 12.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_OPGLLIB_H_
#define OPGLLIB_OPGLLIB_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/LoadShaders.h>

class OpGLLib {
public:
	OpGLLib(glbinding::ContextHandle context);
	void enableCulling(gl::GLenum CullFace = gl::GL_BACK, gl::GLenum FrontFace = gl::GL_CCW);
	void disableCulling();
	void enableDepthTest(gl::GLboolean DepthMasc = gl::GL_TRUE, gl::GLenum DepthFunc = gl::GL_LEQUAL);
	void disableDepthTest();
	LoadShaders loadShaders;
private:
};

#endif /* OPGLLIB_OPGLLIB_H_ */
