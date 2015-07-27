/*
 * LoadShaders.h
 *
 *  Created on: 08.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_SHADERS_H_
#define OPGLLIB_SHADERS_H_

#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/FileLoader.h>
#include <OpGLLib/Logging.h>

#include <deque>

namespace OpGLLib {
namespace gl {
namespace Shaders {

class GLSLProgram {
public:
	GLSLProgram();
	GLSLProgram(std::string const vertexShader, std::string const fragmentShader);
	~GLSLProgram();

	void compileShader(::gl::GLenum type, std::string const shader);
	void linkShaders();
	void useProgram();

	unsigned int id();
private:
	std::deque<unsigned int> _shaders;
	unsigned int _id;
};

}
}
}

#endif /* OPGLLIB_SHADERS_H_ */
