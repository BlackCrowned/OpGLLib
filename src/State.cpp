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

std::map<unsigned int, State::VertexArrayObjectData> _vertexArrayObjectInstances;
std::map<unsigned int, int> _bufferObjectInstances;
std::map<glbinding::ContextHandle, State::data> State::contextDependantData;

unsigned int State::genVertexArray() {
	//Use current context
	glbinding::ContextHandle context = Context::getCurrentContext();

	//Generate VAO
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	//Manage VAO
	return manageVertexArray(vao, context);
}

unsigned int State::genVertexArray(glbinding::ContextHandle context) {
	//Save current context
	glbinding::ContextHandle curContext = Context::getCurrentContext();

	//Switch to selected context
	Context::setContext(context);

	//Generate VAO
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	//Return to previous context
	Context::setContext(curContext);

	//Manage VAO
	return manageVertexArray(vao, context);
}

unsigned int State::manageVertexArray(unsigned int vao, glbinding::ContextHandle context) {
	//TODO: *maybe* unnecessary error checking
	if (_vertexArrayObjectInstances[vao].instances < 0) {
		_vertexArrayObjectInstances[vao].instances = 0;
	}

	//Use current context if 'context' wasn't specified
	if (context == 0) {
		context = Context::getCurrentContext();
	}

	//Only set context for newly managed VAO
	if (_vertexArrayObjectInstances[vao].context == 0) {
		_vertexArrayObjectInstances[vao].context = context;
	}

	//Compare both contexts
	if (_vertexArrayObjectInstances[vao].context != context) {
		std::cerr << "State::mangeVertexArray: Contexts don't match!" << std::endl;
		return 0;
	}

	//Manage VAO
	_vertexArrayObjectInstances[vao].instances++;
	return vao;
}

bool State::bindVertexArray(unsigned int vao) {
	glbinding::ContextHandle context;

	//Check if VAO is managed and has context information
	if (_vertexArrayObjectInstances.count(vao) > 0 && _vertexArrayObjectInstances[vao].context != 0) {
		return bindVertexArray(vao, _vertexArrayObjectInstances[vao].context);
	}
	//If not use current context instead
	else {
		context = Context::getCurrentContext();
	}

	//Bind VAO
	if (getData(context).currentVertexArrayObject == vao) {
		glBindVertexArray(vao);
		return false;
	} else {
		glBindVertexArray(vao);
		getData(context).currentVertexArrayObject = vao;
		return true;
	}

}

bool State::bindVertexArray(unsigned int vao, glbinding::ContextHandle context) {
	bool ret;
	//Save current context
	glbinding::ContextHandle curContext = Context::getCurrentContext();

	//Switch to specified context
	Context::setContext(context);

	if (getData(context).currentVertexArrayObject == vao) {
		glBindVertexArray(vao);
		ret = false;
	} else {
		glBindVertexArray(vao);
		getData(context).currentVertexArrayObject = vao;
		ret = true;
	}

	//Return to previous context
	Context::setContext(curContext);

	return ret;
}

bool State::deleteVertexArray(unsigned int vao) {
	//Check if VAO is managed | If not: Delete anyways and return
	if (_vertexArrayObjectInstances[vao].instances == 0) {
		glDeleteVertexArrays(1, &vao);
		return true;
	}

	//Check if VAO has context information
	if (_vertexArrayObjectInstances[vao].context != 0) {
		return deleteVertexArray(vao, _vertexArrayObjectInstances[vao].context);
	}
	//If not use current context instead

	//Decrease VAO count
	_vertexArrayObjectInstances[vao].instances--;

	//Check if this VAO is used elsewhere
	if (_vertexArrayObjectInstances[vao].instances == 0) {
		glDeleteVertexArrays(1, &vao);
		return true;
	}
	return false;
}

bool State::deleteVertexArray(unsigned int vao, glbinding::ContextHandle context) {
	bool ret = false;

	//Save current context
	glbinding::ContextHandle curContext = Context::getCurrentContext();

	//Switch to specified context
	Context::setContext(context);

	//Check if VAO is managed | If not: Delete anyways and return with previous context
	if (_vertexArrayObjectInstances[vao].instances == 0) {
		glDeleteVertexArrays(1, &vao);
		Context::setContext(curContext);
		return true;
	}

	//Decrease VAO count
	_vertexArrayObjectInstances[vao].instances--;

	//Check if this VAO is used elsewhere
	if (_vertexArrayObjectInstances[vao].instances == 0) {
		glDeleteVertexArrays(1, &vao);
		ret = true;
	}

	//Switch to previous context
	Context::setContext(curContext);

	return ret;
}

unsigned int State::genBuffer() {
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	return manageBuffer(buffer);
}

unsigned int State::manageBuffer(unsigned int buffer) {
	if (_bufferObjectInstances[buffer] < 0) {
		_bufferObjectInstances[buffer] = 0;
	}
	_bufferObjectInstances[buffer]++;
	return buffer;
}

bool State::bindBuffer(GLenum target, unsigned int buffer) {
	//Read current Context
	glbinding::ContextHandle context = Context::getCurrentContext();

	//Bind buffers and save context dependent settings	//TODO: Only change buffers when needed
	if (getData(context).currentBufferObject == buffer) {
		glBindBuffer(target, buffer);
		return false;
	} else {
		glBindBuffer(target, buffer);
		getData(context).currentBufferObject = buffer;
		return true;
	}
}

bool State::deleteBuffer(unsigned int buffer) {
	//FIXME: Check if this buffer is still bound to an openGL-Context
	//Check if buffer is managed | If not: Delete anyways and return
	if (_bufferObjectInstances[buffer] == 0) {
		glDeleteBuffers(1, &buffer);
		return true;
	}

	//Decrease buffer count
	_bufferObjectInstances[buffer]--;

	//Check if this buffer is used elsewhere
	if (_bufferObjectInstances[buffer] == 0) {
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
	return State::genBuffer();
}

unsigned int CState::manageBuffer(unsigned int buffer) {
	return State::manageBuffer(buffer);
}

bool CState::bindBuffer(GLenum target, unsigned int buffer) {
	return State::bindBuffer(target, buffer);
}

bool CState::deleteBuffer(unsigned int buffer) {
	return State::deleteBuffer(buffer);
}

}
}
