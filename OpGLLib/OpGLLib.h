/*
 * OpGLLib.h
 *
 *  Created on: 12.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_OPGLLIB_H_
#define OPGLLIB_OPGLLIB_H_

#define INCLUDE_GLM
#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/LoadShaders.h>
#include <OpGLLib/Matrices.h>
#include <OpGLLib/Perspective.h>
#include <OpGLLib/Camera.h>
#include <OpGLLib/Transformation.h>
#include <OpGLLib/Debug.h>

#include <chrono>
#include <deque>

namespace OpGLLib {

class OpGLLib {
public:
	OpGLLib();
	OpGLLib(glbinding::ContextHandle context);

	void _setContext(glbinding::ContextHandle context);
//
//	void enableCulling(::gl::GLenum CullFace = ::gl::GL_BACK, ::gl::GLenum FrontFace = ::gl::GL_CCW);
//	void disableCulling();
//	void enableDepthTest(::gl::GLboolean DepthMasc = ::gl::GL_TRUE, ::gl::GLenum DepthFunc = ::gl::GL_LEQUAL);
//	void disableDepthTest();

	std::chrono::milliseconds getFrameTime(int range = 1);
	float getFrameRate(int range = 1);

	//LoadShaders loadShaders;
	//Matrices matrices;
	//Perspective perspective;
	//Camera camera;
	//Transformation transformation;
private:
	std::chrono::time_point<std::chrono::system_clock> lastFrame;
	std::deque<std::chrono::milliseconds> frameDuration;
};

namespace gl {
class Context {
public:
	static void setContext(glbinding::ContextHandle context);
	static glbinding::ContextHandle getCurrentContext();
private:
	static glbinding::ContextHandle currentContext;
};
namespace States {
void enableCulling(::gl::GLenum CullFace = ::gl::GL_BACK, ::gl::GLenum FrontFace = ::gl::GL_CCW);
void disableCulling();
void enableDepthTest(::gl::GLboolean DepthMasc = ::gl::GL_TRUE, ::gl::GLenum DepthFunc = ::gl::GL_LEQUAL);
void disableDepthTest();
}
}

}

#endif /* OPGLLIB_OPGLLIB_H_ */
