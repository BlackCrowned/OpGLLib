/*
 * OpGLLibDef.inl
 *
 *  Created on: 24.01.2015
 *      Author: Michael
 */

namespace OpGLLib {

template<typename T> template<typename U> default_delete<T>::default_delete(default_delete<U> const&) noexcept {

}

template<typename T> void default_delete<T>::operator ()(T* ptr) const {
	delete ptr;
}

template<typename T> template<typename U> default_delete<T[]>::default_delete(OpGLLib::default_delete<U[]> const&) noexcept {

}

template<typename T> void default_delete<T[]>::operator ()(T* ptr) const {
	delete[] ptr;
}

namespace Types {

}

template<class retType = unsigned char, class dataType = unsigned short> retType bitAccess(int ExtractBits, dataType data, int n,
		Types::Endianness Endian) {
	if (Endian == Types::Endianness::LITTLE_ENDIAN) {
		return static_cast<retType>((data & (((1 << ExtractBits) - 1) << (n * ExtractBits))) >> (n * ExtractBits));
	} else {
		constexpr dataType sizeofDataType = sizeof(dataType) * 8;
		return static_cast<retType>((data & (((1 << ExtractBits) - 1) << (sizeofDataType - ExtractBits - n * ExtractBits)))
				>> (sizeofDataType - ExtractBits - n * ExtractBits));
	}
}

template<class retType = unsigned char, class dataType = unsigned short, int ExtractBits = sizeof(retType)> retType bitAccess(dataType data,
		int n, Types::Endianness Endian) {
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
		dataType data, Types::Endianness Endian) {
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
