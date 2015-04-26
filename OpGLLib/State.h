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

namespace OpGLLib {
namespace gl {
class State {
public:
	State() = delete;
	static unsigned int genVertexArray(glbinding::ContextHandle = 0);
	static unsigned int manageVertexArray(unsigned int vao, glbinding::ContextHandle = 0);
	static bool bindVertexArray(unsigned int vao, glbinding::ContextHandle = 0);
	static bool deleteVertexArray(unsigned int vao, glbinding::ContextHandle = 0);

	static unsigned int genBuffer(glbinding::ContextHandle = 0);
	static unsigned int manageBuffer(unsigned int buffer, glbinding::ContextHandle = 0);
	static bool bindBuffer(::gl::GLenum target, unsigned int buffer, glbinding::ContextHandle = 0);
	static bool deleteBuffer(unsigned int buffer, glbinding::ContextHandle = 0);

//	static unsigned int genTexture();
//	static unsigned int manageTexture(unsigned int texture);
//	static bool bindTexture(unsigned int texture);
//	static bool deleteTexture(unsigned int texture);
private:
	struct data {
		unsigned int currentVertexArrayObject = 0;
		unsigned int currentBufferObject = 0;
		std::map<unsigned int, int> vertexArrayObjectInstances;
		std::map<unsigned int, int> bufferObjectInstances;
	};
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
