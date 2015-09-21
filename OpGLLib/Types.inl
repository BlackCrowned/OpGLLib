/*
 * Types.inl
 *
 *  Created on: 24.06.2015
 *      Author: mimoe
 */

namespace OpGLLib {

namespace Types {

template<class T> constexpr TypeInfo getType() {
	if (std::is_same<void, T>::value) {
		return TypeInfo::VOID;
	}
	if (std::is_same<bool, T>::value) {
		return TypeInfo::BOOL;
	}
	if (std::is_same<short, T>::value) {
		return TypeInfo::SHORT;
	}
	if (std::is_same<unsigned short, T>::value) {
		return TypeInfo::UNSIGNED_SHORT;
	}
	if (std::is_same<int, T>::value) {
		return TypeInfo::INT;
	}
	if (std::is_same<unsigned int, T>::value) {
		return TypeInfo::UNSIGNED_INT;
	}
	if (std::is_same<long int, T>::value) {
		return TypeInfo::LONG_INT;
	}
	if (std::is_same<unsigned long int, T>::value) {
		return TypeInfo::UNSIGNED_LONG_INT;
	}
	if (std::is_same<long long int, T>::value) {
		return TypeInfo::LONG_LONG_INT;
	}
	if (std::is_same<unsigned long long int, T>::value) {
		return TypeInfo::UNSIGNED_LONG_LONG_INT;
	}
	if (std::is_same<float, T>::value) {
		return TypeInfo::FLOAT;
	}
	if (std::is_same<double, T>::value) {
		return TypeInfo::DOUBLE;
	}
	if (std::is_same<long double, T>::value) {
		return TypeInfo::LONG_DOUBLE;
	}
	if (std::is_same<char, T>::value) {
		return TypeInfo::CHAR;
	}
	if (std::is_same<unsigned char, T>::value) {
		return TypeInfo::UNSIGNED_CHAR;
	}
	if (std::is_same<wchar_t, T>::value) {
		return TypeInfo::WCHAR_T;
	}
	return TypeInfo::UNDEFINED;
}

template<class T> constexpr char const* getTypeName() {
	return getTypeName<getType<T>()>();
}

template<TypeInfo N> constexpr char const* getTypeName() {
	return TypeNames[static_cast<int>(N)];
}


}

}

