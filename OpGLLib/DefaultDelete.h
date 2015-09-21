/*
 * DefaultDelete.h
 *
 *  Created on: 27.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_DEFAULTDELETE_H_
#define OPGLLIB_DEFAULTDELETE_H_

namespace OpGLLib {
template<typename T> struct default_delete {
	constexpr default_delete() noexcept = default;
	template<typename U> default_delete(default_delete<U> const&) noexcept;
	void operator ()(T* ptr) const;
};

template<typename T> struct default_delete<T[]> {
	constexpr default_delete() noexcept = default;
	template<typename U> default_delete(default_delete<U[]> const&) noexcept;
	void operator ()(T* ptr) const;
};

}

#include <OpGLLib/DefaultDelete.inl>

#endif /* OPGLLIB_DEFAULTDELETE_H_ */
