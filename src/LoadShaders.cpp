/*
 * LoadShaders.cpp
 *
 *  Created on: 08.11.2014
 *      Author: Michael
 */

#include "../OpGLLib/LoadShaders.h"

using namespace std;
using namespace gl;

map<GLint, vector<GLuint> > LoadShaders::shaders;
map<GLint, GLuint> LoadShaders::programs;

LoadShaders::LoadShaders() : FileLoader() {

}

GLuint LoadShaders::LoadShader(GLenum type, const string shader, GLint id) {
	if (open(shader) == NULL) {
		return -1;
	}
	const char * const& fileData = toString().c_str();
	close();

	GLuint shaderObj = glCreateShader(type);

	cout << "Compiling shader: '" << shader << "'(" << shaderObj << ")...";

	glShaderSource(shaderObj, 1, &fileData, NULL);
	glCompileShader(shaderObj);

	GLint status;

	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &status);

	if (status == false) {
		cerr << endl << "Failed to compile shader:" << endl;

		GLint infoLogLength = 0;
		glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
		char *infoLog = new char[infoLogLength];

		glGetShaderInfoLog(shaderObj, infoLogLength, NULL, infoLog);
		cerr << infoLog << endl;

		delete[] infoLog;
		return -2;
	} else {
		cout << "Done" << endl;
	}

	shaders[id].push_back(shaderObj);

	return shaderObj;
}

GLuint LoadShaders::CreateProgram(GLint id) {
	GLuint program = glCreateProgram();

	cout << "Creating program: '" << program << "':" << endl;

	for (auto i : shaders[id]) {
		i--;
		cout << "Attaching shader: '" << shaders[id][i] << "'...";
		glAttachShader(program, shaders[id][i]);
		cout << "Done" << endl;
	};

	cout << "Linking program: '" << program << "'...";
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == false) {
		cerr << endl << "Failed to link program:" << endl;

		GLint infoLogLength;
		char *infoLog;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		infoLog = new char[infoLogLength];
		glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
		cout << infoLog << endl;
		delete[] infoLog;
		return -2;
	} else {
		cout << "Done" << endl;
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
