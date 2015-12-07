/*
 * Uniform.h
 *
 *  Created on: 06.11.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_GL_UNIFORM_H_
#define OPGLLIB_GL_UNIFORM_H_


#define INCLUDE_GLBINDING
#define INCLUDE_GLM
#include <OpGLLib/internal.h>

namespace OpGLLib {
namespace gl {

class Uniform {
public:
	Uniform(int location);
	virtual ~Uniform() = default;

	int id();

	virtual void update() const = 0;

protected:
	int _location;
};

template<class T>
class Uniform1 : public Uniform{
public:
	Uniform1(int location, T data);
	Uniform1(int location, glm::detail::tvec1<T, glm::precision::highp> data);
	virtual ~Uniform1() = default;

	void setData(T data);
	void setData(glm::detail::tvec1<T, glm::precision::highp> data);

	virtual void update() const;

private:
	T _data;
};

template<class T>
class Uniform2 : public Uniform{
public:
	Uniform2(int location, T data1, T data2);
	Uniform2(int location, glm::detail::tvec2<T, glm::precision::highp> data);
	virtual ~Uniform2() = default;

	void setData(T data1, T data2);
	void setData(glm::detail::tvec2<T, glm::precision::highp> data);

	virtual void update() const;

private:
	T _data1, _data2;
};

template<class T>
class Uniform3 : public Uniform{
public:
	Uniform3(int location, T data1, T data2, T data3);
	Uniform3(int location, glm::detail::tvec3<T, glm::precision::highp> data);
	virtual ~Uniform3() = default;

	void setData(T data1, T data2, T data3);
	void setData(glm::detail::tvec3<T, glm::precision::highp> data);

	virtual void update() const;

private:
	T _data1, _data2, _data3;
};

template<class T>
class Uniform4 : public Uniform{
public:
	Uniform4(int location, T data1, T data2, T data3, T data4);
	Uniform4(int location, glm::detail::tvec4<T, glm::precision::highp> data);
	virtual ~Uniform4() = default;

	void setData(T data1, T data2, T data3, T data4);
	void setData(glm::detail::tvec4<T, glm::precision::highp> data);

	virtual void update() const;

private:
	T _data1, _data2, _data3, _data4;
};

template<size_t x, class T>
class UniformVector : public Uniform{
public:
	UniformVector(int location, T const* ptr, size_t count = 1);
	virtual ~UniformVector() = default;

	void setData(T const* ptr, size_t count = 1);

	virtual void update() const;
private:
	T const* _ptr;
	size_t _count;
};

template<size_t x, size_t y, class T>
class UniformMatrix : public Uniform{
public:
	template<size_t x_, size_t y_, class U> struct data {
		using type = void;
	};
	template<class U> struct data<2, 2, U> {
		using type = glm::detail::tmat2x2<U, glm::precision::highp>;
	};
	template<class U> struct data<2, 3, U> {
		using type = glm::detail::tmat2x3<U, glm::precision::highp>;
	};
	template<class U> struct data<3, 2, U> {
		using type = glm::detail::tmat3x2<U, glm::precision::highp>;
	};
	template<class U> struct data<2, 4, U> {
		using type = glm::detail::tmat2x4<U, glm::precision::highp>;
	};
	template<class U> struct data<4, 2, U> {
		using type = glm::detail::tmat4x2<U, glm::precision::highp>;
	};
	template<class U> struct data<3, 3, U> {
		using type = glm::detail::tmat3x3<U, glm::precision::highp>;
	};
	template<class U> struct data<3, 4, U> {
		using type = glm::detail::tmat3x4<U, glm::precision::highp>;
	};
	template<class U> struct data<4, 3, U> {
		using type = glm::detail::tmat4x3<U, glm::precision::highp>;
	};
	template<class U> struct data<4, 4, U> {
		using type = glm::detail::tmat4x4<U, glm::precision::highp>;
	};
	using data_t = typename data<x, y, T>::type;

	UniformMatrix(int location, data_t const& matrix, size_t count = 1, ::gl::GLboolean transpose = ::gl::GL_FALSE);
	virtual ~UniformMatrix() = default;

	void setData(data_t const& matrix, size_t count = 1, ::gl::GLboolean transpose = ::gl::GL_FALSE);

	virtual void update() const;

private:
	data_t _matrix;
	T const* _ptr;
	size_t _count;
	::gl::GLboolean _transpose;
};

}
}

#include <OpGLLib/gl/Uniform.inl>

#endif /* OPGLLIB_GL_UNIFORM_H_ */
