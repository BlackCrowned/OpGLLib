/*
 * State.cpp
 *
 *  Created on: 26.04.2015
 *      Author: Michael
 */

#include <OpGLLib/State.h>


using namespace gl;

namespace OpGLLib {
namespace gl{

std::map<glbinding::ContextHandle, State::data> State::contextDependantData;

unsigned int State::genVertexArray(glbinding::ContextHandle context) {
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	return manageVertexArray(vao, context);
}

unsigned int State::manageVertexArray(unsigned int vao, glbinding::ContextHandle context) {
	if (getData(context).vertexArrayObjectInstances[vao] < 0) {
		getData(context).vertexArrayObjectInstances[vao] = 0;
	}
	getData(context).vertexArrayObjectInstances[vao]++;
	return vao;
}

bool State::bindVertexArray(unsigned int vao, glbinding::ContextHandle context) {
	if (getData(context).currentVertexArrayObject == vao) {
		glBindVertexArray(vao);
		return false;
	} else {
		glBindVertexArray(vao);
		getData(context).currentVertexArrayObject = vao;
		return true;
	}
}

bool State::deleteVertexArray(unsigned int vao, glbinding::ContextHandle context) {
	if (getData(context).vertexArrayObjectInstances[vao] == 0) {
		return false;
	}
	getData(context).vertexArrayObjectInstances[vao]--;
	if (getData(context).vertexArrayObjectInstances[vao] == 0) {
		glDeleteVertexArrays(1, &vao);
		return true;
	}
	return false;
}

unsigned int State::genBuffer(glbinding::ContextHandle context) {
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	return manageBuffer(buffer, context);
}

unsigned int State::manageBuffer(unsigned int buffer, glbinding::ContextHandle context) {
	if (getData(context).bufferObjectInstances[buffer] < 0) {
		getData(context).bufferObjectInstances[buffer] = 0;
	}
	getData(context).bufferObjectInstances[buffer]++;
	return buffer;
}

bool State::bindBuffer(GLenum target, unsigned int buffer, glbinding::ContextHandle context) {
	if (getData(context).currentBufferObject == buffer) {
		glBindBuffer(target, buffer);
		return false;
	} else {
		glBindBuffer(target, buffer);
		getData(context).currentBufferObject = buffer;
		return true;
	}
}

bool State::deleteBuffer(unsigned int buffer, glbinding::ContextHandle context) {
	if (getData(context).bufferObjectInstances[buffer] == 0) {
		return false;
	}
	getData().bufferObjectInstances[buffer]--;
	if (getData(context).bufferObjectInstances[buffer] == 0) {
		glDeleteBuffers(1, &buffer);
		return true;
	}
	return false;
}

State::data& State::getData(glbinding::ContextHandle context) {
	if (context == 0) {
		return getData();
	}
	return contextDependantData[context];
}

State::data& State::getData() {
	return getData(OpGLLib::gl::Context::getCurrentContext());
}

CState::CState(glbinding::ContextHandle context) : context(context){

}

void CState::setContext(glbinding::ContextHandle context) {
	CState::context = context;
}

unsigned int CState::genVertexArray() {
	return State::genVertexArray(context);
}

unsigned int CState::manageVertexArray(unsigned int vao) {
	return State::manageVertexArray(vao, context);
}

bool CState::bindVertexArray(unsigned int vao) {
	return State::bindVertexArray(vao, context);
}

bool CState::deleteVertexArray(unsigned int vao) {
	return State::deleteVertexArray(vao, context);
}

unsigned int CState::genBuffer() {
	return State::genBuffer(context);
}

unsigned int CState::manageBuffer(unsigned int buffer) {
	return State::manageBuffer(buffer, context);
}

bool CState::bindBuffer(GLenum target, unsigned int buffer) {
	return State::bindBuffer(target, buffer, context);
}

bool CState::deleteBuffer(unsigned int buffer) {
	return State::deleteBuffer(buffer, context);
}

}
}
