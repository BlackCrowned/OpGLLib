/*
 * State.h
 *
 *  Created on: 26.04.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_STATE_H_
#define OPGLLIB_STATE_H_

#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/Context.h>

#include <map>
#include <iostream>

namespace OpGLLib {
namespace gl {
class State {
public:
	State() = delete;
	static unsigned int genVertexArray();
	static unsigned int genVertexArray(glbinding::ContextHandle);
	static unsigned int manageVertexArray(unsigned int vao, glbinding::ContextHandle = 0);
	static bool bindVertexArray(unsigned int vao);
	static bool bindVertexArray(unsigned int vao, glbinding::ContextHandle);
	static bool deleteVertexArray(unsigned int vao);
	static bool deleteVertexArray(unsigned int vao, glbinding::ContextHandle);

	static unsigned int genBuffer();
	static unsigned int manageBuffer(unsigned int buffer);
	static bool bindBuffer(::gl::GLenum target, unsigned int buffer);
	static bool deleteBuffer(unsigned int buffer);

	static unsigned int genTexture();
	static unsigned int manageTexture(unsigned int texture);
	static bool bindTexture(::gl::GLenum target, unsigned int texture);
	static bool deleteTexture(unsigned int texture);

	struct VertexArrayObjectData {
		int instances = 0;
		glbinding::ContextHandle context = 0;
	};
private:
	struct data {
		unsigned int currentVertexArrayObject = 0;
		unsigned int currentBufferObject = 0;
		unsigned int currentTexture = 0;
	};
	static std::map<unsigned int, VertexArrayObjectData> _vertexArrayObjectInstances;
	static std::map<unsigned int, int> _bufferObjectInstances;
	static std::map<unsigned int, int> _textureInstances;
	static std::map<glbinding::ContextHandle, data> contextDependantData;
	static data& getData();
	static data& getData(glbinding::ContextHandle);
};
class CState {
public:
	CState(glbinding::ContextHandle context);
	CState(CState const& other) = default;
	~CState() = default;

	void setContext(glbinding::ContextHandle);

	unsigned int genVertexArray();
	unsigned int manageVertexArray(unsigned int vao);
	bool bindVertexArray(unsigned int vao);
	bool deleteVertexArray(unsigned int vao);

	unsigned int genBuffer();
	unsigned int manageBuffer(unsigned int buffer);
	bool bindBuffer(::gl::GLenum target, unsigned int buffer);
	bool deleteBuffer(unsigned int buffer);

private:
	glbinding::ContextHandle context;
};
}
}

#endif /* OPGLLIB_STATE_H_ */
