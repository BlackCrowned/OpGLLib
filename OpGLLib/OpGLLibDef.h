/*
 * OpGLLibDef.h
 *
 *  Created on: 23.01.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_OPGLLIBDEF_H_
#define OPGLLIB_OPGLLIBDEF_H_

namespace OpGLLib {
template<typename T> struct default_delete {
	constexpr default_delete() noexcept = default;
	template<typename U> default_delete(default_delete<U> const&) noexcept {

	}
	void operator ()(T* ptr) const {
		delete ptr;
	}
};

template<typename T> struct default_delete<T[]> {
	constexpr default_delete() noexcept = default;
	template<typename U> default_delete(default_delete<U[]> const&) noexcept {

	}
	void operator ()(T* ptr) const {
		delete[] ptr;
	}
};

namespace Types {

enum class Endianness {
	LITTLE_ENDIAN = 0x1, BIG_ENDIAN = 0x2
};
typedef unsigned char BYTE;

template<Endianness Type = Endianness::LITTLE_ENDIAN> struct WORD {
	typedef unsigned short dataType;

	WORD();
	WORD(char* offset);
	WORD(dataType data);
	template<Endianness U> WORD(WORD<U> const& w);

	WORD<Type>& operator =(char* offset);
	WORD<Type>& operator =(dataType data);

	dataType& operator *();
	dataType& operator ->();
	BYTE operator [](int i);

	dataType data;
};
template<> WORD<Endianness::BIG_ENDIAN>::WORD(char* offset);
template<> WORD<Endianness::BIG_ENDIAN>& WORD<Endianness::BIG_ENDIAN>::operator =(char* offset);
template<> BYTE WORD<Endianness::BIG_ENDIAN>::operator [](int i);

template<Endianness Type = Endianness::LITTLE_ENDIAN> struct DWORD {
	typedef unsigned long int dataType;

	DWORD();
	DWORD(char *offset);
	DWORD(dataType data);
	template<Endianness U> DWORD(DWORD<U> const& w);

	DWORD<Type>& operator =(char* offset);
	DWORD<Type>& operator =(dataType data);

	dataType& operator *();
	dataType& operator ->();
	BYTE operator [](int i);

	dataType data;
};

template<> DWORD<Endianness::BIG_ENDIAN>::DWORD(char* offset);
template<> DWORD<Endianness::BIG_ENDIAN>& DWORD<Endianness::BIG_ENDIAN>::operator =(char* offset);
template<> BYTE DWORD<Endianness::BIG_ENDIAN>::operator [](int i);

template<Endianness Type = Endianness::LITTLE_ENDIAN> struct LONG {
	typedef long int dataType;

	LONG();
	LONG(char *offset);
	LONG(dataType data);
	template<Endianness U> LONG(LONG<U> const& w);

	LONG<Type>& operator =(char* offset);
	LONG<Type>& operator =(dataType data);
	dataType& operator *();

	dataType& operator ->();
	BYTE operator [](int i);

	dataType data;
};

template<> LONG<Endianness::BIG_ENDIAN>::LONG(char* offset);
template<> LONG<Endianness::BIG_ENDIAN>& LONG<Endianness::BIG_ENDIAN>::operator =(char* offset);
template<> BYTE LONG<Endianness::BIG_ENDIAN>::operator [](int);

template class WORD<Endianness::LITTLE_ENDIAN> ;
template class WORD<Endianness::BIG_ENDIAN> ;
template class DWORD<Endianness::LITTLE_ENDIAN> ;
template class DWORD<Endianness::BIG_ENDIAN> ;
template class LONG<Endianness::LITTLE_ENDIAN> ;
template class LONG<Endianness::BIG_ENDIAN> ;
}

template<class retType = unsigned char, class dataType = unsigned short> retType bitAccess(int ExtractBits, dataType data, int n,
		Types::Endianness Endian = Types::Endianness::LITTLE_ENDIAN) {
	if (Endian == Types::Endianness::LITTLE_ENDIAN) {
		return static_cast<retType>((data & (((1 << ExtractBits) - 1) << (n * ExtractBits))) >> (n * ExtractBits));
	} else {
		constexpr dataType sizeofDataType = sizeof(dataType) * 8;
		return static_cast<retType>((data
				& (((1 << ExtractBits) - 1) << (sizeofDataType - ExtractBits - n * ExtractBits)))
						>> (sizeofDataType - ExtractBits - n * ExtractBits));
	}
}

template<class retType = unsigned char, class dataType = unsigned short, int ExtractBits = sizeof(retType)> retType bitAccess(dataType data,
		int n, Types::Endianness Endian = Types::Endianness::LITTLE_ENDIAN) {
	if (Endian == Types::Endianness::LITTLE_ENDIAN) {
		constexpr dataType bitmask = (1 << ExtractBits) - 1;
		return static_cast<retType>((data & (bitmask << (n * ExtractBits))) >> (n * ExtractBits));
	} else {
		constexpr dataType bitmask = (1 << ExtractBits) - 1;
		constexpr dataType BEOffset = sizeof(dataType) * 8 - ExtractBits;
		return static_cast<retType>((data & (bitmask << (BEOffset - n * ExtractBits))) >> (BEOffset - n * ExtractBits));
	}
}

template<class retType = unsigned char, class dataType = unsigned short, int ExtractBits = sizeof(retType), int n = 0> retType bitAccess(
		dataType data, Types::Endianness Endian = Types::Endianness::LITTLE_ENDIAN) {
	if (Endian == Types::Endianness::LITTLE_ENDIAN) {
		constexpr dataType bitmask = (1 << ExtractBits) - 1;
		constexpr dataType shiftAmount = n * ExtractBits;
		return static_cast<retType>((data & (bitmask << shiftAmount)) >> shiftAmount);
	} else {
		constexpr dataType bitmask = (1 << ExtractBits) - 1;
		constexpr dataType shiftAmount = sizeof(dataType) * 8 - ExtractBits - n * ExtractBits;
		return static_cast<retType>((data & (bitmask << shiftAmount)) >> shiftAmount);
	}

}

template<class retType = unsigned char, class dataType = unsigned short, int ExtractBits = sizeof(retType), int n = 0, dataType data = 0,
		Types::Endianness Endian = Types::Endianness::LITTLE_ENDIAN> constexpr retType bitAccess() {
	return bitAccess<retType, dataType, Endian>(ExtractBits, data, n);
}

}

#include <OpGLLib/OpGLLibDef.inl>

#endif /* OPGLLIB_OPGLLIBDEF_H_ */
