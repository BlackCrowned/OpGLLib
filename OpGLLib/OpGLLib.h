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
#include <OpGLLib/Matrices.h>
#include <OpGLLib/Perspective.h>
#include <OpGLLib/Camera.h>
#include <OpGLLib/Transformation.h>
#include <OpGLLib/Debug.h>

class OpGLLib {
public:
	OpGLLib();
	OpGLLib(glbinding::ContextHandle context);

	void setContext(glbinding::ContextHandle context);

	void enableCulling(gl::GLenum CullFace = gl::GL_BACK, gl::GLenum FrontFace = gl::GL_CCW);
	void disableCulling();
	void enableDepthTest(gl::GLboolean DepthMasc = gl::GL_TRUE, gl::GLenum DepthFunc = gl::GL_LEQUAL);
	void disableDepthTest();

	LoadShaders loadShaders;
	Matrices matrices;
	Perspective perspective;
	Camera camera;
	Transformation transformation;
private:
};

#endif /* OPGLLIB_OPGLLIB_H_ */
