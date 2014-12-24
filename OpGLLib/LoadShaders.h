/*
 * LoadShaders.h
 *
 *  Created on: 08.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_LOADSHADERS_H_
#define OPGLLIB_LOADSHADERS_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/FileLoader.h>

class LoadShaders : public FileLoader{
public:
	LoadShaders();
	unsigned int LoadShader(gl::GLenum type, const std::string shader, int id);
	unsigned int CreateProgram(int id);
	unsigned int GetProgram(int id);
private:
	static std::map<int, std::vector<unsigned int> > shaders;
	static std::map<int, unsigned int> programs;
};

#endif /* OPGLLIB_LOADSHADERS_H_ */
