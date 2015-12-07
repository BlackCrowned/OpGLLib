/*
 * Uniform.inl
 *
 *  Created on: 06.11.2015
 *      Author: mimoe
 */

namespace OpGLLib {
namespace gl {

template<class T> Uniform1<T>::Uniform1(int location, T data) :
		Uniform(location), _data(data) {

}
template<class T> Uniform1<T>::Uniform1(int location, glm::detail::tvec1<T, glm::precision::highp> data) :
		Uniform(location), _data(data.x) {

}

template<class T> void Uniform1<T>::setData(T data) {
	_data = data;
}
template<class T> void Uniform1<T>::setData(glm::detail::tvec1<T, glm::precision::highp> data) {
	_data = data.x;
}

template<class T> Uniform2<T>::Uniform2(int location, T data1, T data2) :
		Uniform(location), _data1(data1), _data2(data2) {

}
template<class T> Uniform2<T>::Uniform2(int location, glm::detail::tvec2<T, glm::precision::highp> data) :
		Uniform(location), _data1(data.x), _data2(data.y) {

}

template<class T> void Uniform2<T>::setData(T data1, T data2) {
	_data1 = data1;
	_data2 = data2;
}
template<class T> void Uniform2<T>::setData(glm::detail::tvec2<T, glm::precision::highp> data) {
	_data1 = data.x;
	_data2 = data.y;
}

template<class T> Uniform3<T>::Uniform3(int location, T data1, T data2, T data3) :
		Uniform(location), _data1(data1), _data2(data2), _data3(data3) {

}
template<class T> Uniform3<T>::Uniform3(int location, glm::detail::tvec3<T, glm::precision::highp> data) :
		Uniform(location), _data1(data.x), _data2(data.y), _data3(data.z) {

}

template<class T> void Uniform3<T>::setData(T data1, T data2, T data3) {
	_data1 = data1;
	_data2 = data2;
	_data3 = data3;
}
template<class T> void Uniform3<T>::setData(glm::detail::tvec3<T, glm::precision::highp> data) {
	_data1 = data.x;
	_data2 = data.y;
	_data3 = data.z;
}

template<class T> Uniform4<T>::Uniform4(int location, T data1, T data2, T data3, T data4) :
		Uniform(location), _data1(data1), _data2(data2), _data3(data3), _data4(data4) {

}
template<class T> Uniform4<T>::Uniform4(int location, glm::detail::tvec4<T, glm::precision::highp> data) :
		Uniform(location), _data1(data.x), _data2(data.y), _data3(data.z), _data4(data.w) {

}

template<class T> void Uniform4<T>::setData(T data1, T data2, T data3, T data4) {
	_data1 = data1;
	_data2 = data2;
	_data3 = data3;
	_data4 = data4;
}
template<class T> void Uniform4<T>::setData(glm::detail::tvec4<T, glm::precision::highp> data) {
	_data1 = data.x;
	_data2 = data.y;
	_data3 = data.z;
	_data4 = data.w;
}

template<size_t x, class T> UniformVector<x, T>::UniformVector(int location, T const* ptr, size_t count) :
		Uniform(location), _ptr(ptr), _count(count) {

}

template<size_t x, class T> void UniformVector<x, T>::setData(T const* ptr, size_t count) {
	_ptr = ptr;
	_count = count;
}

template<size_t x, size_t y, class T> UniformMatrix<x, y, T>::UniformMatrix(int location, data_t const& matrix, size_t count,
		::gl::GLboolean transpose) :
		Uniform(location), _matrix(matrix), _ptr(glm::value_ptr(_matrix)), _count(count), _transpose(transpose) {

}

template<size_t x, size_t y, class T> void UniformMatrix<x, y, T>::setData(data_t const& matrix, size_t count, ::gl::GLboolean transpose) {
	_matrix = matrix;
	_ptr = glm::value_ptr(_matrix);
	_count = count;
	_transpose = transpose;
}

}
}
