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
	virtual ~Uniform1() = default;

	virtual void update() const;

private:
	T _data;
};

template<class T>
class Uniform2 : public Uniform{
public:
	Uniform2(int location, T data1, T data2);
	virtual ~Uniform2() = default;

	virtual void update() const;

private:
	T _data1, _data2;
};

template<class T>
class Uniform3 : public Uniform{
public:
	Uniform3(int location, T data1, T data2, T data3);
	virtual ~Uniform3() = default;

	virtual void update() const;

private:
	T _data1, _data2, _data3;
};

template<class T>
class Uniform4 : public Uniform{
public:
	Uniform4(int location, T data1, T data2, T data3, T data4);
	virtual ~Uniform4() = default;

	virtual void update() const;

private:
	T _data1, _data2, _data3, _data4;
};

template<size_t x, class T>
class UniformVector : public Uniform{
public:
	UniformVector(int location, T const* ptr, size_t count = 1);
	virtual ~UniformVector() = default;

	virtual void update() const;

private:
	T const* _ptr;
	size_t _count;
};

template<size_t x, size_t y, class T>
class UniformMatrix : public Uniform{
public:
	UniformMatrix(int location, T const* ptr, size_t count = 1, ::gl::GLboolean transpose = ::gl::GL_FALSE);
	virtual ~UniformMatrix() = default;

	virtual void update() const;

private:
	T const* _ptr;
	size_t _count;
	::gl::GLboolean _transpose;
};

}
}

#include <OpGLLib/gl/Uniform.inl>

#endif /* OPGLLIB_GL_UNIFORM_H_ */
