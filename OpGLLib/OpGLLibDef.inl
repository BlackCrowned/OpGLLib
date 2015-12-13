/*
 * OpGLLibDef.inl
 *
 *  Created on: 24.01.2015
 *      Author: Michael
 */

namespace OpGLLib {
namespace Types {

}

template<class retType, class dataType> retType bitAccess(int ExtractBits, dataType data, int n,
		Types::Endianness Endian) {
	if (Endian == Types::Endianness::LITTLE_ENDIAN) {
		return static_cast<retType>((data & (((1 << ExtractBits) - 1) << (n * ExtractBits))) >> (n * ExtractBits));
	} else {
		constexpr dataType sizeofDataType = sizeof(dataType) * 8;
		return static_cast<retType>((data & (((1 << ExtractBits) - 1) << (sizeofDataType - ExtractBits - n * ExtractBits)))
				>> (sizeofDataType - ExtractBits - n * ExtractBits));
	}
}

template<class retType, class dataType, int ExtractBits> retType bitAccess(dataType data,
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

template<class retType, class dataType, int ExtractBits, int n> retType bitAccess(
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

template<class retType, class dataType, int ExtractBits, int n, dataType data,
		Types::Endianness Endian> constexpr retType bitAccess() {
	return bitAccess<retType, dataType, Endian>(ExtractBits, data, n);
}

}
