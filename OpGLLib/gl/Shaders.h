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
#include <OpGLLib/Exception.h>
#include <OpGLLib/OpGLLib.h>

#include <deque>

namespace OpGLLib {
namespace gl {
namespace Shaders {

/*
 * Required exceptions
 */

class CompileException: public Exception {
public:
	CompileException(OpGLLibBase const* pointer, std::string const& shader, std::shared_ptr<char> const& infoLog);
	virtual ~CompileException() = default;

	virtual ExceptionType what();
	virtual std::string toString();

	virtual bool handle();

private:
	std::string const& _shader;
	std::shared_ptr<char> const& _infoLog;
};

class LinkException: public Exception {
public:
	LinkException(OpGLLibBase const* pointer, std::shared_ptr<char> const& infoLog);
	virtual ~LinkException() = default;

	virtual ExceptionType what();
	virtual std::string toString();

	virtual bool handle();
private:
	std::shared_ptr<char> const& _infoLog;
};


/*
 * Main class
 */

class GLSLProgram: public OpGLLibBase {
public:
	GLSLProgram();
	GLSLProgram(OpGLLibBase const* pointer);
	GLSLProgram(OpGLLibBase const* pointer, std::string const vertexShader, std::string const& fragmentShader);
	~GLSLProgram();

	void reset();
	void reset(OpGLLibBase const* pointer);

	void compileShader(::gl::GLenum type, std::string const& shader);
	void linkShaders();
	void useProgram();

	unsigned int id();

	void swap(GLSLProgram& other);
private:
	std::deque<unsigned int> _shaders;
	unsigned int _id;
};

}
}
}

#endif /* OPGLLIB_SHADERS_H_ */
