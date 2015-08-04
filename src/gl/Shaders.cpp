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

CompileException::CompileException(OpGLLibBase* pointer, std::string const& shader, std::shared_ptr<char> const& infoLog) :
		Exception(pointer), _shader(shader), _infoLog(infoLog) {

}

ExceptionType CompileException::what() {
	return ExceptionType::GL_SHADERS_COMPILE_EXCEPTION;
}

std::string CompileException::toString() {
	return "Failed to compile shader " + _shader;
}

bool CompileException::handle() {
	notify(toString(), LoggingLevel::unrecoverableError);
	notify(_infoLog.get(), LoggingLevel::debug);

	//This error is unrecoverable
	return false;
}

LinkException::LinkException(OpGLLibBase* pointer, std::shared_ptr<char> const& infoLog) :
		Exception(pointer), _infoLog(infoLog) {

}

ExceptionType LinkException::what() {
	return ExceptionType::GL_SHADERS_LINK_EXCEPTION;
}

std::string LinkException::toString() {
	return "Failed to link program";
}

bool LinkException::handle() {
	notify(toString(), LoggingLevel::unrecoverableError);
	notify(_infoLog.get(), LoggingLevel::debug);

	//This error is unrecoverable
	return false;
}

GLSLProgram::GLSLProgram() :
		OpGLLibBase(), _id(0) {
}

GLSLProgram::GLSLProgram(OpGLLibBase const* pointer) :
		OpGLLibBase(pointer), _id(0) {
}

GLSLProgram::GLSLProgram(OpGLLibBase const* pointer, std::string const vertexShader, std::string const& fragmentShader) :
		OpGLLibBase(pointer), _id(0) {
	compileShader(GL_VERTEX_SHADER, vertexShader);
	compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	linkShaders();
}

GLSLProgram::~GLSLProgram() {
	glDeleteProgram(_id);
}

void GLSLProgram::reset() {
	GLSLProgram newGLSLProgram;
	swap(newGLSLProgram);
}

void GLSLProgram::reset(OpGLLibBase const* pointer) {
	GLSLProgram newGLSLProgram(pointer);
	swap(newGLSLProgram);
}

void GLSLProgram::compileShader(GLenum type, std::string const& shader) {
	//Load file into memory
	fstream file(shader, std::ios::in | std::ios::binary);
	if (!file) {
		//Return if unrecoverable
		if (!OpenFileException(this, shader).handle()) {
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

void GLSLProgram::swap(GLSLProgram& other) {
	std::swap(_shaders, other._shaders);
	std::swap(_id, other._id);
}

}
}
}
