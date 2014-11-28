/*
 * Debug.h
 *
 *  Created on: 28.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_DEBUG_H_
#define OPGLLIB_DEBUG_H_

#include <OpGLLib/internal.h>
#include <typeindex>
#include <iomanip>

class Debug{
public:
	Debug();
	~Debug();

	void enableLogging(bool state = 1);

	void enableLimiters(bool state = 1);
	void setLimiter(std::string limiter);
	void showLimiter();

	void log(bool& type, std::string name = "");
	void log(int& type, std::string name = "");
	void log(unsigned int& type, std::string name = "");
	void log(float& type, std::string name = "");
	void log(char& type, std::string name = "");
	void log(char *& type, std::string name = "");
	void log(std::string& type, std::string name = "");
	void log(glm::vec2& type, std::string name = "");
	void log(glm::vec3& type, std::string name = "");
	void log(glm::vec4& type, std::string name = "");
	void log(glm::mat3& type, std::string name = "");
	void log(glm::mat4& type, std::string name = "");
private:
	static bool logging;
	static bool limiters;
	static std::string limiter;
};
#endif /* OPGLLIB_DEBUG_H_ */
