/*
 * OpGLLibDef.h
 *
 *  Created on: 23.01.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_OPGLLIBDEF_H_
#define OPGLLIB_OPGLLIBDEF_H_

namespace OpGLLib {
namespace Types {

enum class Endianness {
	LITTLE_ENDIAN = 0x1, BIG_ENDIAN = 0x2
};

}

template<class retType = unsigned char, class dataType = unsigned short> retType bitAccess(int ExtractBits, dataType data, int n,
		Types::Endianness Endian = Types::Endianness::LITTLE_ENDIAN);

template<class retType = unsigned char, class dataType = unsigned short, int ExtractBits = sizeof(retType)> retType bitAccess(dataType data,
		int n, Types::Endianness Endian = Types::Endianness::LITTLE_ENDIAN);

template<class retType = unsigned char, class dataType = unsigned short, int ExtractBits = sizeof(retType), int n = 0> retType bitAccess(
		dataType data, Types::Endianness Endian = Types::Endianness::LITTLE_ENDIAN);

template<class retType = unsigned char, class dataType = unsigned short, int ExtractBits = sizeof(retType), int n = 0, dataType data = 0,
		Types::Endianness Endian = Types::Endianness::LITTLE_ENDIAN> constexpr retType bitAccess();

}

#include <OpGLLib/OpGLLibDef.inl>

#endif /* OPGLLIB_OPGLLIBDEF_H_ */
