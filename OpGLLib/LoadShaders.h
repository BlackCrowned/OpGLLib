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
	GLuint LoadShader(GLenum type, const std::string shader, GLint id);
	GLuint CreateProgram(GLint id);
	GLuint GetProgram(GLint id);
private:
	static std::map<GLint, std::vector<GLuint> > shaders;
	static std::map<GLint, GLuint> programs;
};

#endif /* OPGLLIB_LOADSHADERS_H_ */
