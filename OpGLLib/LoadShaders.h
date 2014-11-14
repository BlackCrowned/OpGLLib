/*
 * LoadShaders.h
 *
 *  Created on: 08.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_LOADSHADERS_H_
#define OPGLLIB_LOADSHADERS_H_

#include <OpGLLib/internal.h>

class LoadShaders {
public:
	LoadShaders();
	gl::GLuint LoadShader(gl::GLenum type, const std::string shader, gl::GLint id);
	gl::GLuint CreateProgram(gl::GLint id);
	gl::GLuint GetProgram(gl::GLint id);
private:
	static std::map<gl::GLint, std::vector<gl::GLuint> > shaders;
	static std::map<gl::GLint, gl::GLuint> programs;
};

#endif /* OPGLLIB_LOADSHADERS_H_ */
