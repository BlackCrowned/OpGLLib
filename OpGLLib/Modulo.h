/*
 * Modulo.h
 *
 *  Created on: 29.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_MODULO_H_
#define OPGLLIB_MODULO_H_

#include <type_traits>

namespace OpGLLib {

template<class T>
T mod(T k, T n) {
	return ((k %= n) < 0) ? k+n : k;
}

template<class T, class R>
T mod(T k, R n) {
	static_assert(std::is_convertible<R, T>::value, "Can't convert types");
	return mod(k, static_cast<T>(n));
}

}



#endif /* OPGLLIB_MODULO_H_ */
