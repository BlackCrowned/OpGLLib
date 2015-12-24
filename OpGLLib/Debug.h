/*
 * Debug.h
 *
 *  Created on: 28.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_DEBUG_H_
#define OPGLLIB_DEBUG_H_

#define INCLUDE_GLM
#include <OpGLLib/internal.h>

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Debug {
public:
	Debug();
	~Debug();

	void enableLogging(bool state = 1);

	void enableLimiters(bool state = 1);
	void setLimiter(std::string limiter);
	void showLimiter(bool ignoreState = 0);

	void log(bool& type, std::string name = "");
	void log(int& type, std::string name = "");
	void log(unsigned int& type, std::string name = "");
	void log(float& type, std::string name = "");
	void log(char& type, std::string name = "");
	void log(char * type, std::string name = "");
	void log(std::string& type, std::string name = "");
	void log(glm::vec2& type, std::string name = "");
	void log(glm::vec3& type, std::string name = "");
	void log(glm::vec4& type, std::string name = "");
	void log(glm::ivec2& type, std::string name = "");
	void log(glm::ivec3& type, std::string name = "");
	void log(glm::ivec4& type, std::string name = "");
	void log(glm::mat3& type, std::string name = "");
	void log(glm::mat4& type, std::string name = "");

	void print(std::string name, std::string type, std::string data, std::string address);
	void print(std::string name, std::string type, float* data, int colums);
	void print(std::string name, std::string type, int* data, int colums);
	void print(std::string name, std::string type, float* data, int rows, int colums);
	void print(std::string name, std::string type, int* data, int rows, int colums);
private:
	static bool logging;
	static bool limiters;
	static std::string limiter;
};

static Debug _debug;
#endif /* OPGLLIB_DEBUG_H_ */
