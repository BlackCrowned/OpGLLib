/*
 * Debug.cpp
 *
 *  Created on: 28.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Debug.h>

using namespace std;

bool Debug::logging = false;
bool Debug::limiters = false;
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
	stringstream data, adress;
	data << type;
	adress << &type;
	print(name, "bool", data.str(), adress.str());
}

void Debug::log(int& type, string name) {
	if (!logging) {
		return;
	}
	stringstream data, adress;
	data << type;
	adress << &type;
	print(name, "int", data.str(), adress.str());
}

void Debug::log(unsigned int& type, string name) {
	if (!logging) {
		return;
	}
	stringstream data, adress;
	data << type;
	adress << &type;
	print(name, "uint", data.str(), adress.str());
}

void Debug::log(float& type, string name) {
	if (!logging) {
		return;
	}
	stringstream data, adress;
	data << type;
	adress << &type;
	print(name, "float", data.str(), adress.str());
}

void Debug::log(char& type, string name) {
	if (!logging) {
		return;
	}
	stringstream data, adress;
	data << type;
	adress << &type;
	print(name, "char", data.str(), adress.str());
}

void Debug::log(char* type, string name) {
	if (!logging) {
		return;
	}
	stringstream data, adress;
	data << type;
	adress << static_cast<const void *>(&type);
	print(name, "char*", data.str(), adress.str());
}

void Debug::log(string& type, string name) {
	if (!logging) {
		return;
	}
	stringstream data, adress;
	data << type;
	adress << static_cast<const void *>(&type);
	print(name, "string", data.str(), adress.str());
}

void Debug::log(glm::vec2& type, string name) {
	if (!logging) {
		return;
	}
	float* data = glm::value_ptr(type);
	print(name, "vec2", data, 2);
}

void Debug::log(glm::vec3& type, string name) {
	if (!logging) {
		return;
	}
	float* data = glm::value_ptr(type);
	print(name, "vec3", data, 3);
}

void Debug::log(glm::vec4& type, string name) {
	if (!logging) {
		return;
	}
	float* data = glm::value_ptr(type);
	print(name, "vec4", data, 4);
}

void Debug::log(glm::ivec2& type, string name) {
	if (!logging) {
		return;
	}
	int* data = glm::value_ptr(type);
	print(name, "ivec2", data, 2);
}

void Debug::log(glm::ivec3& type, string name) {
	if (!logging) {
		return;
	}
	int* data = glm::value_ptr(type);
	print(name, "ivec3", data, 3);
}

void Debug::log(glm::ivec4& type, string name) {
	if (!logging) {
		return;
	}
	int* data = glm::value_ptr(type);
	print(name, "ivec4", data, 4);
}

void Debug::log(glm::mat3& type, string name) {
	if (!logging) {
		return;
	}
	float *array = glm::value_ptr(type);
	print(name, "mat3", array, 3, 3);
}

void Debug::log(glm::mat4& type, string name) {
	if (!logging) {
		return;
	}
	float *array = glm::value_ptr(type);
	print(name, "mat3", array, 4, 4);
}

void Debug::print(string name, string type, std::string data, std::string adress) {
	showLimiter();
	if (name == "") {
		cout << fixed << setprecision(1) << boolalpha << "[" + type + "]: " << data << " [@" << adress << "]" << endl;
	} else {
		cout << fixed << setprecision(1) << boolalpha << name << " [" + type + "]: " << data << " [@" << adress << "]" << endl;
	}
	showLimiter();
}

void Debug::print(string name, string type, float* data, int colums) {
	showLimiter();
	if (name == "") {
		cout << "[" << type << "]: ";
	} else {
		cout << name << " [" << type << "]: ";
	}
	cout << "(";
	for (auto i = 0; i < colums; i++) {
		if (i == colums - 1) {
			cout << fixed << setprecision(1) << data[i] << ")";
			continue;
		}
		cout << fixed << setprecision(1) << data[i] << "|";
	}
	cout << " [@" << data << "]" << endl;
	showLimiter();

}

void Debug::print(string name, string type, int* data, int colums) {
	showLimiter();
	if (name == "") {
		cout << "[" << type << "]: ";
	} else {
		cout << name << " [" << type << "]: ";
	}
	cout << "(";
	for (auto i = 0; i < colums; i++) {
		if (i == colums - 1) {
			cout << data[i] << ")";
			continue;
		}
		cout << data[i] << "|";
	}
	cout << " [@" << data << "]" << endl;
	showLimiter();

}

void Debug::print(string name, string type, float* array, int rows, int colums) {
	showLimiter();
	if (name == "") {
		cout << "[" << type << "]: [@" << array << "]" << endl;
	} else {
		cout << name << " [" << type << "]: [@" << array << "]" << endl;
	}
	cout << setfill('-') << setw(colums * 4 + 1) << "" << setfill(' ') << endl;
	for (auto i = 0; i < rows; i++) {
		cout << "|";
		for (auto j = 0; j < colums; j++) {
			cout << fixed << setprecision(1) << array[(j * 4) + i] << "|";
		}
		cout << endl << setfill('-') << setw(colums * 4 + 1) << "" << setfill(' ') << endl;
	}
	showLimiter();
}
