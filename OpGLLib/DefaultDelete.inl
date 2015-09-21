/*
 * DefaultDelete.inl
 *
 *  Created on: 27.07.2015
 *      Author: mimoe
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

}


