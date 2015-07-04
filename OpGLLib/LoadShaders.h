/*
 * LoadShaders.h
 *
 *  Created on: 08.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_LOADSHADERS_H_
#define OPGLLIB_LOADSHADERS_H_

#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/FileLoader.h>
#include <map>
#include <vector>

class LoadShaders: public OpGLLib::FileLoader {
public:
	LoadShaders();
	unsigned int LoadShader(gl::GLenum type, const std::string shader, int id);
	unsigned int CreateProgram(int id);
	unsigned int GetProgram(int id);
private:
	static std::map<int, std::vector<unsigned int> > shaders;
	static std::map<int, unsigned int> programs;
};

//////////////////////////////////////////////////

namespace OpGLLib {
namespace gl {
class Shaders {
public:
	static unsigned int loadShader(::gl::GLenum type, const std::string shader, int id);
	static unsigned int createProgram(int id);
	static unsigned int getProgram(int id);
private:
	static std::map<int, std::vector<unsigned int> > shaders;
	static std::map<int, unsigned int> programs;
};
}
}

#endif /* OPGLLIB_LOADSHADERS_H_ */
