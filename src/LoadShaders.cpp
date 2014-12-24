/*
 * LoadShaders.cpp
 *
 *  Created on: 08.11.2014
 *      Author: Michael
 */

#include "../OpGLLib/LoadShaders.h"

using namespace std;
using namespace gl;

map<int, vector<unsigned int> > LoadShaders::shaders;
map<int, unsigned int> LoadShaders::programs;

LoadShaders::LoadShaders() : FileLoader() {

}

unsigned int LoadShaders::LoadShader(GLenum type, const string shader, int id) {
	if (open(shader) == NULL) {
		return -1;
	}
	const char *fileData = toCString();
	close();

	unsigned int shaderObj = glCreateShader(type);

	cout << "Compiling shader: '" << shader << "'(" << shaderObj << ")...";

	glShaderSource(shaderObj, 1, &fileData, NULL);
	glCompileShader(shaderObj);

	int status;

	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &status);

	if (status == false) {
		cerr << endl << "Failed to compile shader:" << endl;

		int infoLogLength = 0;
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

unsigned int LoadShaders::CreateProgram(int id) {
	unsigned int program = glCreateProgram();

	cout << "Creating program: '" << program << "':" << endl;

	for (auto i : shaders[id]) {
		i--;
		cout << "Attaching shader: '" << shaders[id][i] << "'...";
		glAttachShader(program, shaders[id][i]);
		cout << "Done" << endl;
	};

	cout << "Linking program: '" << program << "'...";
	glLinkProgram(program);

	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == false) {
		cerr << endl << "Failed to link program:" << endl;

		int infoLogLength;
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

unsigned int LoadShaders::GetProgram(int id) {

	return programs[id];
}
