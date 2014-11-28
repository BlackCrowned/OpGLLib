/*
 * Debug.cpp
 *
 *  Created on: 28.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Debug.h>

using namespace std;

bool Debug::logging = false;
bool Debug::limiters = true;
string Debug::limiter = "---";

Debug::Debug() {

}

Debug::~Debug() {

}

void Debug::enableLogging(bool state) {
	logging = state;
}

void Debug::enableLimiters(bool state) {
	limiters = state;
}

void Debug::setLimiter(string limiter) {
	Debug::limiter = limiter;
}

void Debug::showLimiter() {
	if (limiters) {
		cout << limiter << endl;
	}
}

void Debug::log(bool& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << boolalpha << name << "[bool]: " << type << " @" << &type << endl;
	showLimiter();
}

void Debug::log(int& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[int]: " << type << " @" << &type << endl;
	showLimiter();
}

void Debug::log(unsigned int& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[uint]: " << type << " @" << &type << endl;
	showLimiter();
}

void Debug::log(float& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[float]: " << type << " @" << &type << endl;
	showLimiter();
}

void Debug::log(char& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[char]: " << type << " @" << &type << endl;
	showLimiter();
}

void Debug::log(char*& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[char*]: " << type << " @" << &type << endl;
	showLimiter();
}

void Debug::log(string& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[string]: " << type << " @" << &type << endl;
	showLimiter();
}

void Debug::log(glm::vec2& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[vec2]: (" << type.x << "|" << type.y << ") @" << &type << endl;
	showLimiter();
}

void Debug::log(glm::vec3& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[vec3]: (" << type.x << "|" << type.y << "|" << type.z << ") @" << &type << endl;
	showLimiter();
}

void Debug::log(glm::vec4& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << name << "[vec4]: (" << type.x << "|" << type.y << "|" << type.z << "|" << type.w << ") @" << &type << endl;
	showLimiter();
}

void Debug::log(glm::mat3& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << showpoint << setprecision(3);
	cout << name << "[mat3]:" << endl;
	cout << "   1    2    3" << endl;
	cout << "X  " << type[0].x << " " << type[1].x << " " << type[2].x << endl;
	cout << "Y  " << type[0].y << " " << type[1].y << " " << type[2].y << endl;
	cout << "Z  " << type[0].z << " " << type[1].z << " " << type[2].z << endl;
	cout << "-----------------" << endl;
	showLimiter();
}

void Debug::log(glm::mat4& type, string name) {
	if (!logging) {
		return;
	}
	showLimiter();
	cout << showpoint << setprecision(3);
	cout << name << "[mat3]:" << endl;
	cout << "   1    2    3    4" << endl;
	cout << "X  " << type[0].x << " " << type[1].x << " " << type[2].x << " " << type[3].x << endl;
	cout << "Y  " << type[0].y << " " << type[1].y << " " << type[2].y << " " << type[3].y << endl;
	cout << "Z  " << type[0].z << " " << type[1].z << " " << type[2].z << " " << type[3].z << endl;
	cout << "W  " << type[0].w << " " << type[1].w << " " << type[2].w << " " << type[3].w << endl;
	cout << "----------------------" << endl;
	showLimiter();
}
