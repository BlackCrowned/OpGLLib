/*
 * ImageLoader.inl
 *
 *  Created on: 16.01.2015
 *      Author: Michael
 */

namespace ImageLoader {
template<class T> Image1D<T>::Image1D(size_t width) :
		dimensions( { width, 1 }), data(new vectorType[width], OpGLLib::default_delete<vectorType[]>()), offset( { 0, 1 }) {
}

template<class T> template<class U> Image1D<T>::Image1D(size_t width, std::shared_ptr<U> data, Dimensions offset) :
		dimensions( { width, 1 }), data(data), offset(offset) {
}

template<class T> Image1D<T>& Image1D<T>::operator =(Image1D<T> other) {
	std::swap(dimensions, other.dimensions);
	std::swap(data, other.data);
	std::swap(offset, other.offset);
	return *this;
}

template<class T> tvec4<T>& Image1D<T>::operator [](size_t x) {
	vectorType* tmp = data.get() + offset.width + offset.height * x;
	return *tmp;
}

template<class T> tvec4<T>& Image1D<T>::operator ()(size_t x) {
	return (*this)[x];
}

template<class T> auto Image1D<T>::getData() -> std::shared_ptr<vectorType>{
	return data;
}

template<class T> Image2D<T>::Image2D(size_t width, size_t height) :
		dimensions( { width, height }), data(new vectorType[width * height], OpGLLib::default_delete<vectorType[]>()), offset( { 0, 1 }) {
}

template<class T> template<class U> Image2D<T>::Image2D(size_t width, size_t height, std::shared_ptr<U> data, Dimensions offset) :
		dimensions( { width, height }), data(data), offset(offset) {
}

template<class T> Image2D<T>& Image2D<T>::operator =(Image2D<T> other) {
	std::swap(dimensions, other.dimensions);
	std::swap(data, other.data);
	std::swap(offset, other.offset);
	return *this;
}

template<class T> Image1D<T> Image2D<T>::operator [](size_t x) {
	return Image1D<T>(dimensions.height, data, { x, dimensions.width });
}

template<class T> tvec4<T>& Image2D<T>::operator ()(size_t x, size_t y) {
	return (*this)[x][y];
}

template<class T> auto Image2D<T>::getData() -> std::shared_ptr<vectorType>{
	return data;
}

}

