/*
 * OpGLLibDef.cpp
 *
 *  Created on: 23.01.2015
 *      Author: Michael
 */

#include <OpGLLib/OpGLLibDef.h>

namespace OpGLLib {
namespace Types {
template <Endianness Type> WORD<Type>::WORD() : data(0){

}

template <Endianness Type> WORD<Type>::WORD(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset) << 0) | (*reinterpret_cast<BYTE*>(offset + 1) << 8);
}

template <Endianness Type> WORD<Type>::WORD(dataType data) : data(data) {

}

template <Endianness Type> template<Endianness U> WORD<Type>::WORD(WORD<U> const& w) {
	data = w.data;
}

template <Endianness Type > WORD<Type>& WORD<Type>::operator =(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset) << 0) | (*reinterpret_cast<BYTE*>(offset + 1) << 8);
	return *this;
}

template <Endianness Type>	WORD<Type>& WORD<Type>::operator =(dataType data) {
	WORD::data = data;
	return *this;
}

template <Endianness Type> auto WORD<Type>::operator *() -> dataType&{
	return data;
}

template <Endianness Type> auto WORD<Type>::operator ->() -> dataType&{
	return data;
}

template <Endianness Type> BYTE WORD<Type>::operator [](int i) {
	return static_cast<BYTE>((data & (0xFF << (i * 8))) >> (i * 8));
}

template <> WORD<Endianness::BIG_ENDIAN>::WORD(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset + 1) << 0) | (*reinterpret_cast<BYTE*>(offset) << 8);
}

template <> WORD<Endianness::BIG_ENDIAN>& WORD<Endianness::BIG_ENDIAN>::operator =(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset + 1) << 0) | (*reinterpret_cast<BYTE*>(offset) << 8);
	return *this;
}

template<> BYTE WORD<Endianness::BIG_ENDIAN>::operator [](int i) {
	return static_cast<BYTE>((data & (0xFF << (8 - i * 8))) >> (8 - i * 8));
}

template<Endianness Type> DWORD<Type>::DWORD() : data(0){

}

template<Endianness Type> 	DWORD<Type>::DWORD(char *offset) {
	data = (*reinterpret_cast<BYTE*>(offset) << 0)
			| (*reinterpret_cast<BYTE*>(offset + 1) << 8 | (*reinterpret_cast<BYTE*>(offset + 2) << 16)
					| (*reinterpret_cast<BYTE*>(offset + 3) << 24));
}

template<Endianness Type> 	DWORD<Type>::DWORD(dataType data) : data(data) {

}

template <Endianness Type> template<Endianness U> DWORD<Type>::DWORD(DWORD<U> const& w) {
	data = w.data;
}

template<Endianness Type> DWORD<Type>& DWORD<Type>::operator =(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset) << 0)
			| (*reinterpret_cast<BYTE*>(offset + 1) << 8 | (*reinterpret_cast<BYTE*>(offset + 2) << 16)
					| (*reinterpret_cast<BYTE*>(offset + 3) << 24));
	return *this;
}

template<Endianness Type>	DWORD<Type>& DWORD<Type>::operator =(dataType data) {
	DWORD::data = data;
	return *this;
}

template<Endianness Type>	auto DWORD<Type>::operator *() -> dataType&{
	return data;
}

template<Endianness Type>	auto DWORD<Type>::operator ->() -> dataType&{
	return data;
}

template<Endianness Type>	BYTE DWORD<Type>::operator [](int i) {
	return static_cast<BYTE>((data & (0xFF << (i * 8))) >> (i * 8));
}

template<> DWORD<Endianness::BIG_ENDIAN>::DWORD(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset + 3) << 0)
			| (*reinterpret_cast<BYTE*>(offset + 2) << 8 | (*reinterpret_cast<BYTE*>(offset + 1) << 16)
					| (*reinterpret_cast<BYTE*>(offset) << 24));
}
template<> DWORD<Endianness::BIG_ENDIAN>& DWORD<Endianness::BIG_ENDIAN>::operator =(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset + 3) << 0)
			| (*reinterpret_cast<BYTE*>(offset + 2) << 8 | (*reinterpret_cast<BYTE*>(offset + 1) << 16)
					| (*reinterpret_cast<BYTE*>(offset) << 24));
	return *this;
}
template<> BYTE DWORD<Endianness::BIG_ENDIAN>::operator [](int i) {
	return static_cast<BYTE>((data & (0xFF << (24 - i * 8))) >> (24 - i * 8));
}

template<Endianness Type> LONG<Type>::LONG() : data(0){

}

template<Endianness Type> 	LONG<Type>::LONG(char *offset) {
	data = (*reinterpret_cast<BYTE*>(offset) << 0)
			| (*reinterpret_cast<BYTE*>(offset + 1) << 8 | (*reinterpret_cast<BYTE*>(offset + 2) << 16)
					| (*reinterpret_cast<BYTE*>(offset + 3) << 24));
}

template<Endianness Type> 	LONG<Type>::LONG(dataType data) : data(data) {

}

template <Endianness Type> template<Endianness U> LONG<Type>::LONG(LONG<U> const& w) {
	data = w.data;
}

template<Endianness Type> LONG<Type>& LONG<Type>::operator =(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset) << 0)
			| (*reinterpret_cast<BYTE*>(offset + 1) << 8 | (*reinterpret_cast<BYTE*>(offset + 2) << 16)
					| (*reinterpret_cast<BYTE*>(offset + 3) << 24));
	return *this;
}

template<Endianness Type>	LONG<Type>& LONG<Type>::operator =(dataType data) {
	LONG::data = data;
	return *this;
}

template<Endianness Type>	auto LONG<Type>::operator *() -> dataType&{
	return data;
}

template<Endianness Type>	auto LONG<Type>::operator ->() -> dataType&{
	return data;
}

template<Endianness Type>	BYTE LONG<Type>::operator [](int i) {
	return static_cast<BYTE>((data & (0xFF << (i * 8))) >> (i * 8));
}

template<> LONG<Endianness::BIG_ENDIAN>::LONG(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset + 3) << 0)
			| (*reinterpret_cast<BYTE*>(offset + 2) << 8 | (*reinterpret_cast<BYTE*>(offset + 1) << 16)
					| (*reinterpret_cast<BYTE*>(offset) << 24));
}
template<> LONG<Endianness::BIG_ENDIAN>& LONG<Endianness::BIG_ENDIAN>::operator =(char* offset) {
	data = (*reinterpret_cast<BYTE*>(offset + 3) << 0)
			| (*reinterpret_cast<BYTE*>(offset + 2) << 8 | (*reinterpret_cast<BYTE*>(offset + 1) << 16)
					| (*reinterpret_cast<BYTE*>(offset) << 24));
	return *this;
}
template<> BYTE LONG<Endianness::BIG_ENDIAN>::operator [](int i) {
	return static_cast<BYTE>((data & (0xFF << (24 - i * 8))) >> (24 - i * 8));
}

}
}


