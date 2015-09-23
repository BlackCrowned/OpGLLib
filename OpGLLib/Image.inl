/*
 * Image.inl
 *
 *  Created on: 16.01.2015
 *      Author: Michael
 */

namespace OpGLLib {

template<class T> Image<T>::Image(Dimensions dimensions, std::vector<dataType> const& data) :
		_dimensions(dimensions), _data(data) {

}

template<class T> Image<T>::Image(Dimensions dimensions, std::vector<dataType>&& data) :
		_dimensions(dimensions), _data(std::move(data)) {

}

template<class T> template<class U> Image<T>::Image(Image<U> const& other) :
		_dimensions(other._dimensions), _data(other._data) {

}

template<class T> template<class U> Image<T>::Image(Image<U>&& other) :
		_dimensions(std::move(other._dimensions)), _data(std::move(other._data)) {

}

template<class T> template<class U> Image<T>& Image<T>::operator =(Image<U> other) {
	std::swap(_dimensions, other._dimensions);
	std::swap(_data, other._data);

	return *this;
}

template<class T> auto Image<T>::get() -> std::vector<dataType>&{
	return _data;
}

template<class T> Dimensions Image<T>::getDimensions() {
	return _dimensions;
}

template<class T> void Image<T>::reset(Dimensions dimensions, std::vector<dataType>& data) {
	_dimensions = std::move(dimensions);
	_data = data;
}

//template<class T> Image<T>::Image(Dimensions dimensions, std::shared_ptr<vectorType> data, Dimensions offset) :
//		dimensions(dimensions), data(data), offset(offset) {
//
//}
//
//template<class T> Dimensions Image<T>::getDimensions() {
//	return dimensions;
//}
//
//template<class T> auto Image<T>::getData() -> std::shared_ptr<vectorType> {
//	return data;
//}
//
//template<class T> template<class U> Image<T>::Image(Image<U> const& i) {
//	dimensions = i.dimensions;
//	data = i.data;
//	offset = i.offset;
//}
//
//template<class T> template<class U> Image<T>::Image(Image<U> && i) {
//	dimensions = std::move(i.dimensions);
//	data = std::move(i.data);
//	offset = std::move(i.offset);
//}
//
//template<class T> template<class U> Image<T>& Image<T>::operator =(Image<U> other) {
//	swap(dimensions, other.dimensions);
//	swap(data, other.data);
//	swap(offset, other.offset);
//	return *this;
//}
//
//template<class T> Image1D<T>::Image1D(size_t width) :
//		Image<T>( { width, 1 },
//				std::shared_ptr<typename Image<T>::vectorType>(new typename Image<T>::vectorType[width],
//						OpGLLib::default_delete<typename Image<T>::vectorType[]>()), { 0, 1 }) {
//}
//
//template<class T> template<class U> Image1D<T>::Image1D(size_t width, std::shared_ptr<U> data, Dimensions offset) :
//		Image<T>( { width, 1 }, data, offset) {
//}
//
//template<class T> Image1D<T>::Image1D(Image1D<T> const& other) :
//		Image<T>(other) {
//
//}
//
//template<class T> Image1D<T>::Image1D(Image1D<T> && other) :
//		Image<T>(other) {
//
//}
//
//template<class T> template<class U> Image1D<T>& Image1D<T>::operator =(Image1D<U> other) {
//	std::swap(Image<T>::dimensions, other.dimensions);
//	std::swap(Image<T>::data, other.data);
//	std::swap(Image<T>::offset, other.offset);
//	return *this;
//}
//
//template<class T> tvec4<T>& Image1D<T>::operator [](size_t x) {
//	typename Image<T>::vectorType* tmp = Image<T>::data.get() + Image<T>::offset.width + Image<T>::offset.height * x;
//	return *tmp;
//}
//
//template<class T> tvec4<T>& Image1D<T>::operator ()(size_t x) {
//	return (*this)[x];
//}
//
//template<class T> Image2D<T>::Image2D(size_t width, size_t height) :
//		Image<T>( { width, height },
//				std::shared_ptr<typename Image<T>::vectorType>(new typename Image<T>::vectorType[width * height],
//						OpGLLib::default_delete<typename Image<T>::vectorType[]>()), { 0, 1 }) {
//}
//
//template<class T> template<class U> Image2D<T>::Image2D(size_t width, size_t height, std::shared_ptr<U> data, Dimensions offset) :
//		Image<T>( { width, height }, data, offset) {
//}
//
//template<class T> Image2D<T>::Image2D(Image2D<T> const& other) :
//		Image<T>(other) {
//
//}
//
//template<class T> Image2D<T>::Image2D(Image2D<T> && other) :
//		Image<T>(other) {
//
//}
//
//template<class T> template<class U> Image2D<T>& Image2D<T>::operator =(Image2D<U> other) {
//	std::swap(Image<T>::dimensions, other.dimensions);
//	std::swap(Image<T>::data, other.data);
//	std::swap(Image<T>::offset, other.offset);
//	return *this;
//}
//
//template<class T> Image1D<T> Image2D<T>::operator [](size_t x) {
//	return Image1D<T>(Image<T>::dimensions.height, Image<T>::data, { x, Image<T>::dimensions.width });
//}
//
//template<class T> tvec4<T>& Image2D<T>::operator ()(size_t x, size_t y) {
//	return (*this)[x][y];
//}

}

