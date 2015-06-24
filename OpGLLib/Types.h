/*
 * Types.h
 *
 *  Created on: 24.06.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_TYPES_H_
#define OPGLLIB_TYPES_H_

#include <OpGLLib/internal.h>

#include <array>
#include <string>

namespace OpGLLib {

namespace Types {

enum class TypeInfo {
	UNDEFINED = 0,
	VOID,
	BOOL,
	SHORT,
	UNSIGNED_SHORT,
	INT,
	UNSIGNED_INT,
	LONG_INT,
	UNSIGNED_LONG_INT,
	LONG_LONG_INT,
	UNSIGNED_LONG_LONG_INT,
	FLOAT,
	DOUBLE,
	LONG_DOUBLE,
	CHAR,
	UNSIGNED_CHAR,
	WCHAR_T,
	TYPEINFO_SIZE = WCHAR_T

};

constexpr std::array<char const*, static_cast<int>(TypeInfo::TYPEINFO_SIZE) + 1> TypeNames = { "undefined", "void", "bool", "short",
		"unsigned short", "int", "unsigned int", "long int", "unsigned long int", "long long int", "unsigned long long int", "float",
		"double", "long double", "char", "unsigned char", "wchar_t" };

template<class T> constexpr TypeInfo getType();

template<class T> constexpr char const* getTypeName();
template<TypeInfo N> constexpr char const* getTypeName();
std::string getTypeName(TypeInfo n);
}

}

#include <OpGLLib/Types.inl>

#endif /* OPGLLIB_TYPES_H_ */
