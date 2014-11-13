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
	OpGLLib();
	void enableCulling(GLenum CullFace = GL_BACK, GLenum FrontFace = GL_CCW);
	void disableCulling();
	LoadShaders loadShaders;
private:
};

#endif /* OPGLLIB_OPGLLIB_H_ */
