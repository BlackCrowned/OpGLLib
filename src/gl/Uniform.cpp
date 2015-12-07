/*
 * Uniform.cpp
 *
 *  Created on: 06.11.2015
 *      Author: mimoe
 */

#include <OpGLLib/gl/Uniform.h>

namespace OpGLLib {
namespace gl {

Uniform::Uniform(int location) :
		_location(location) {

}

int Uniform::id() {
	return _location;
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

template<> void Uniform2<float>::update() const {
	::gl::glUniform2f(_location, _data1, _data2);
}
template<> void Uniform2<int>::update() const {
	::gl::glUniform2i(_location, _data1, _data2);
}
template<> void Uniform2<unsigned int>::update() const {
	::gl::glUniform2ui(_location, _data1, _data2);
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

template<> void Uniform4<float>::update() const {
	::gl::glUniform4f(_location, _data1, _data2, _data3, _data4);
}
template<> void Uniform4<int>::update() const {
	::gl::glUniform4i(_location, _data1, _data2, _data3, _data4);
}
template<> void Uniform4<unsigned int>::update() const {
	::gl::glUniform4ui(_location, _data1, _data2, _data3, _data4);
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
