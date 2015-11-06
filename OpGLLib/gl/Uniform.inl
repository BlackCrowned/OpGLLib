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

template<class T> void Uniform1<T>::setData(T data) {
	_data = data;
}

template<> void Uniform1<float>::update() const {
		::gl::glUniform1f(_location, _data);
}
template<> void Uniform1<int>::update() const {
		::gl::glUniform1i(_location, _data);
}
template<> void Uniform1<unsigned int>::update() const {
		::gl::glUniform1ui(_location, _data);
}

template<class T> Uniform2<T>::Uniform2(int location, T data1, T data2) :
		Uniform(location), _data1(data1), _data2(data2) {

}

template<class T> void Uniform2<T>::setData(T data1, T data2) {
	_data1 = data1;
	_data2 = data2;
}

template<> void Uniform2<float>::update() const {
		::gl::glUniform2f(_location, _data1, _data2);
}
template<> void Uniform2<int>::update() const {
		::gl::glUniform2i(_location, _data1, _data2);
}
template<> void Uniform2<unsigned int>::update() const {
		::gl::glUniform2ui(_location, _data1, _data2);
}

template<class T> Uniform3<T>::Uniform3(int location, T data1, T data2, T data3) :
		Uniform(location), _data1(data1), _data2(data2), _data3(data3) {

}

template<class T> void Uniform3<T>::setData(T data1, T data2, T data3) {
	_data1 = data1;
	_data2 = data2;
	_data3 = data3;
}

template<> void Uniform3<float>::update() const {
		::gl::glUniform3f(_location, _data1, _data2, _data3);
}
template<> void Uniform3<int>::update() const {
		::gl::glUniform3i(_location, _data1, _data2, _data3);
}
template<> void Uniform3<unsigned int>::update() const {
		::gl::glUniform3ui(_location, _data1, _data2, _data3);
}

template<class T> Uniform4<T>::Uniform4(int location, T data1, T data2, T data3, T data4) :
		Uniform(location), _data1(data1), _data2(data2), _data3(data3), _data4(data4) {

}

template<class T> void Uniform4<T>::setData(T data1, T data2, T data3, T data4) {
	_data1 = data1;
	_data2 = data2;
	_data3 = data3;
	_data4 = data4;
}

template<> void Uniform4<float>::update() const {
		::gl::glUniform4f(_location, _data1, _data2, _data3, _data4);
}
template<> void Uniform4<int>::update() const {
		::gl::glUniform4i(_location, _data1, _data2, _data3, _data4);
}
template<> void Uniform4<unsigned int>::update() const {
		::gl::glUniform4ui(_location, _data1, _data2, _data3, _data4);
}

template<size_t x, class T> UniformVector<x, T>::UniformVector(int location, T const* ptr, size_t count) :
		Uniform(location), _ptr(ptr), _count(count) {

}

template<size_t x, class T> void UniformVector<x, T>::setData(T const* ptr, size_t count) {
	_ptr = ptr;
	_count = count;
}

template<> void UniformVector<1, float>::update() const {
	::gl::glUniform1fv(_location, _count, _ptr);
}
template<> void UniformVector<2, float>::update() const {
	::gl::glUniform2fv(_location, _count, _ptr);
}
template<> void UniformVector<3, float>::update() const {
	::gl::glUniform3fv(_location, _count, _ptr);
}
template<> void UniformVector<4, float>::update() const {
	::gl::glUniform4fv(_location, _count, _ptr);
}

template<> void UniformVector<1, int>::update() const {
	::gl::glUniform1iv(_location, _count, _ptr);
}
template<> void UniformVector<2, int>::update() const {
	::gl::glUniform2iv(_location, _count, _ptr);
}
template<> void UniformVector<3, int>::update() const {
	::gl::glUniform3iv(_location, _count, _ptr);
}
template<> void UniformVector<4, int>::update() const {
	::gl::glUniform4iv(_location, _count, _ptr);
}

template<> void UniformVector<1, unsigned int>::update() const {
	::gl::glUniform1uiv(_location, _count, _ptr);
}
template<> void UniformVector<2, unsigned int>::update() const {
	::gl::glUniform2uiv(_location, _count, _ptr);
}
template<> void UniformVector<3, unsigned int>::update() const {
	::gl::glUniform3uiv(_location, _count, _ptr);
}
template<> void UniformVector<4, unsigned int>::update() const {
	::gl::glUniform4uiv(_location, _count, _ptr);
}

template<size_t x, size_t y, class T> UniformMatrix<x, y, T>::UniformMatrix(int location, T const* ptr, size_t count,
		::gl::GLboolean transpose) :
		Uniform(location), _ptr(ptr), _count(count), _transpose(transpose) {

}

template<size_t x, size_t y, class T> void UniformMatrix<x, y, T>::setData(T const* ptr, size_t count, ::gl::GLboolean transpose) {
	_ptr = ptr;
	_count = count;
	_transpose = transpose;
}

template<> void UniformMatrix<2, 2, float>::update() const {
	::gl::glUniformMatrix2fv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<3, 3, float>::update() const {
	::gl::glUniformMatrix3fv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<4, 4, float>::update() const {
	::gl::glUniformMatrix4fv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<2, 3, float>::update() const {
	::gl::glUniformMatrix2x3fv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<3, 2, float>::update() const {
	::gl::glUniformMatrix3x2fv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<2, 4, float>::update() const {
	::gl::glUniformMatrix2x4fv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<4, 2, float>::update() const {
	::gl::glUniformMatrix4x2fv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<3, 4, float>::update() const {
	::gl::glUniformMatrix3x4fv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<4, 3, float>::update() const {
	::gl::glUniformMatrix4x3fv(_location, _count, _transpose, _ptr);
}

template<> void UniformMatrix<2, 2, double>::update() const {
	::gl::glUniformMatrix2dv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<3, 3, double>::update() const {
	::gl::glUniformMatrix3dv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<4, 4, double>::update() const {
	::gl::glUniformMatrix4dv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<2, 3, double>::update() const {
	::gl::glUniformMatrix2x3dv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<3, 2, double>::update() const {
	::gl::glUniformMatrix3x2dv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<2, 4, double>::update() const {
	::gl::glUniformMatrix2x4dv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<4, 2, double>::update() const {
	::gl::glUniformMatrix4x2dv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<3, 4, double>::update() const {
	::gl::glUniformMatrix3x4dv(_location, _count, _transpose, _ptr);
}
template<> void UniformMatrix<4, 3, double>::update() const {
	::gl::glUniformMatrix4x3dv(_location, _count, _transpose, _ptr);
}
}
}
