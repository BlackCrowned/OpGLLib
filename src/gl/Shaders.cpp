/*
 * LoadShaders.cpp
 *
 *  Created on: 08.11.2014
 *      Author: Michael
 */

#include <OpGLLib/gl/Shaders.h>

using namespace std;
using namespace gl;

namespace OpGLLib {
namespace gl {
namespace Shaders {

GLSLProgram::GLSLProgram() :
		_id(0) {
	//Use default logger
	addObserver(getLogger());
}

GLSLProgram::GLSLProgram(OpGLLibBase* pointer) :
		OpGLLibBase(pointer), _id(0) {
	//Use default logger
	addObserver(getLogger());
}

GLSLProgram::GLSLProgram(OpGLLibBase* pointer, std::string const vertexShader, std::string const& fragmentShader) :
		OpGLLibBase(pointer) {
	//Use default logger
	addObserver(getLogger());

	compileShader(GL_VERTEX_SHADER, vertexShader);
	compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	linkShaders();
}

GLSLProgram::~GLSLProgram() {
	glDeleteProgram(_id);
}

void GLSLProgram::compileShader(GLenum type, std::string const& shader) {
	//Load file into memory
	fstream file(shader, std::ios::in | std::ios::binary);
	if (!file) {
		//Return if unrecoverable
		if (!UnableToOpenFileException(this, shader).handle()) {
			return;
		}
	}
	const char *fileData = files::dataPtr(file);
	file.close();

	//Create ShaderObj
	unsigned int shaderObj = glCreateShader(type);

	//Compile Shader
	glShaderSource(shaderObj, 1, &fileData, NULL);
	glCompileShader(shaderObj);

	delete[] fileData;

	//Error Checking
	int status;

	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &status);

	if (status == false) {
		int infoLogLength = 0;
		glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::shared_ptr<char> infoLog(new char[infoLogLength]);

		glGetShaderInfoLog(shaderObj, infoLogLength, NULL, infoLog.get());

		//Return if unrecoverable
		if (!CompileException(this, shader, infoLog).handle()) {
			return;
		}
	}

	_shaders.push_back(shaderObj);
}

void GLSLProgram::linkShaders() {
	//Create empty program
	_id = glCreateProgram();

	//Attach each shaderObj
	for (size_t i = 0; i < _shaders.size(); i++) {
		glAttachShader(_id, _shaders[i]);
	};

	//Linking program
	glLinkProgram(_id);

	//Error checking
	int status;
	glGetProgramiv(_id, GL_LINK_STATUS, &status);

	if (status == false) {
		LOG("Failed to link program: ", LoggingLevel::unrecoverableError);

		int infoLogLength;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::shared_ptr<char> infoLog(new char[infoLogLength]);

		glGetProgramInfoLog(_id, infoLogLength, NULL, infoLog.get());

		//Return if unrecoverable
		if (!LinkException(this, infoLog).handle()) {
			//Dont return to allow detaching shaders
		}
	}

	//Detach each shaderObj
	for (size_t i = 0; i < _shaders.size(); i++) {
		glDetachShader(_id, _shaders[i]);
	}

}

void GLSLProgram::useProgram() {
	glUseProgram(_id);
}

unsigned int GLSLProgram::id() {
	return _id;
}

}
}
}
