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

}

