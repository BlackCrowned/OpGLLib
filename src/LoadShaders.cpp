/*
 * LoadShaders.cpp
 *
 *  Created on: 08.11.2014
 *      Author: Michael
 */

#include "../OpGLLib/LoadShaders.h"

using namespace gl;

std::map<GLint, std::vector<GLuint> > LoadShaders::shaders;
std::map<GLint, GLuint> LoadShaders::programs;

LoadShaders::LoadShaders() {

}

GLuint LoadShaders::LoadShader(GLenum type, const std::string shader, GLint id) {
	std::fstream file;
	char *fileData;

	file.open(shader.c_str(), std::ios::in | std::ios::binary);

	if (!file) {
		std::cerr << "Failed to open file: " << shader << std::endl;
		return -1;
	} else {
		std::cout << "Compiling shader: '" << shader << "'...";
	}

	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	fileData = new char[fileSize + 1];
	file.read(fileData, fileSize);
	file.close();
	fileData[fileSize] = '\0';

	GLuint shaderObj = glCreateShader(type);
	glShaderSource(shaderObj, 1, &fileData, NULL);
	glCompileShader(shaderObj);

	delete[] fileData;

	GLint status;

	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &status);

	if (status == false) {
		std::cerr << std::endl << "Failed to compile shader:" << std::endl;

		GLint infoLogLength = 0;
		glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
		char *infoLog = new char[infoLogLength];

		glGetShaderInfoLog(shaderObj, infoLogLength, NULL, infoLog);
		std::cerr << infoLog << std::endl;

		delete[] infoLog;
		return -2;
	} else {
		std::cout << "Done" << std::endl;
	}

	shaders[id].push_back(shaderObj);

	return shaderObj;
}

GLuint LoadShaders::CreateProgram(GLint id) {
	GLuint program = glCreateProgram();

	std::cout << "Creating program: '" << program << "':" << std::endl;

	for (auto i : shaders[id]) {
		i--;
		std::cout << "Attaching shader: '" << shaders[id][i] << "'...";
		glAttachShader(program, shaders[id][i]);
		std::cout << "Done" << std::endl;
	};

	std::cout << "Linking program: '" << program << "'...";
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == false) {
		std::cerr << std::endl << "Failed to link program:" << std::endl;

		GLint infoLogLength;
		char *infoLog;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		infoLog = new char[infoLogLength];
		glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
		std::cout << infoLog << std::endl;
		delete[] infoLog;
		return -2;
	} else {
		std::cout << "Done" << std::endl;
	}

	for (auto i : shaders[id]) {
		i--;
		glDetachShader(program, shaders[id][i]);
	}

	programs[id] = program;

	return program;
}

GLuint LoadShaders::GetProgram(GLint id) {

	return programs[id];
}
