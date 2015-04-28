/*
 * Render.cpp
 *
 *  Created on: 10.01.2015
 *      Author: Michael
 */

#include <OpGLLib/Renderer.h>

using namespace std;
using namespace gl;

namespace OpGLLib {
namespace Renderer {

RenderObject::RenderObject(gl::CState cState, GLenum mode, size_t start, size_t count, bool indexedDraw, GLenum type,
		const void* indicies) : cState(cState){
	RenderObject::vao = RenderObject::cState.genVertexArray();
	RenderObject::mode = mode;
	RenderObject::start = start;
	RenderObject::count = count;
	RenderObject::indexedDraw = indexedDraw;
	RenderObject::type = type;
	RenderObject::indicies = indicies;
}

RenderObject::~RenderObject() {
	cState.deleteVertexArray(vao);
	for (auto i : vertexBufferObjects) {
		cState.deleteBuffer(i.second);
	}
	for (auto i : indexBufferObjects) {
		cState.deleteBuffer(i.second);
	}
	vao = 0;
	vertexBufferObjects.clear();
	indexBufferObjects.clear();
}

void RenderObject::setVertexBufferObject(unsigned int index, unsigned int buffer) {
	if (vertexBufferObjects.count(index) > 0) {
		cState.deleteBuffer(vertexBufferObjects[index]);
	}
	vertexBufferObjects[index] = buffer;
}

void RenderObject::setIndexBufferObject(unsigned int index, unsigned int buffer) {
	if (indexBufferObjects.count(index) > 0) {
		cState.deleteBuffer(indexBufferObjects[index]);
	}
	indexBufferObjects[index] = buffer;
}

unsigned int RenderObject::getVertexBufferObject(unsigned int index) {
	if (vertexBufferObjects.count(index) == 0) {
		vertexBufferObjects[index] = cState.genBuffer();
	}
	return vertexBufferObjects[index];
}

unsigned int RenderObject::getIndexBufferObject(unsigned int index) {
	if (indexBufferObjects.count(index) == 0) {
		indexBufferObjects[index] = cState.genBuffer();
	}
	return indexBufferObjects[index];
}

void RenderObject::enableVertexAttribArray(unsigned int index) {
	cState.bindVertexArray(vao);
	glEnableVertexAttribArray(index);
}

void RenderObject::disableVertexAttribArray(unsigned int index) {
	cState.bindVertexArray(vao);
	glDisableVertexAttribArray(index);
}

Renderer::Renderer() {

}

Renderer::~Renderer() {
	deleteRenderObjects();
	deleteVertexArrays();
	deleteBuffers();
}

unsigned int Renderer::genVertexArray() {
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	return manageVertexArray(vao);
}

unsigned int Renderer::manageVertexArray(unsigned int vao) {
	if (vertexArrayObjectInstances[vao] < 0) {
		vertexArrayObjectInstances[vao] = 0;
	}
	vertexArrayObjectInstances[vao]++;
	return vao;
}

bool Renderer::bindVertexArray(unsigned int vao) {
	if (currentVertexArrayObject == vao) {
		glBindVertexArray(vao);
		return false;
	} else {
		glBindVertexArray(vao);
		currentVertexArrayObject = vao;
		return true;
	}
}

bool Renderer::deleteVertexArray(unsigned int vao) {
	if (vertexArrayObjectInstances[vao] == 0) {
		return false;
	}
	vertexArrayObjectInstances[vao]--;
	if (vertexArrayObjectInstances[vao] == 0) {
		glDeleteVertexArrays(1, &vao);
		return true;
	}
	return false;
}

unsigned int Renderer::genBuffer() {
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	return manageBuffer(buffer);
}

unsigned int Renderer::manageBuffer(unsigned int buffer) {
	if (bufferObjectInstances[buffer] < 0) {
		bufferObjectInstances[buffer] = 0;
	}
	bufferObjectInstances[buffer]++;
	return buffer;
}

bool Renderer::bindBuffer(GLenum target, unsigned int buffer) {
	if (currentBufferObject == buffer) {
		glBindBuffer(target, buffer);
		return false;
	} else {
		glBindBuffer(target, buffer);
		currentBufferObject = buffer;
		return true;
	}
}

bool Renderer::deleteBuffer(unsigned int buffer) {
	if (bufferObjectInstances[buffer] == 0) {
		return false;
	}
	bufferObjectInstances[buffer]--;
	if (bufferObjectInstances[buffer] == 0) {
		glDeleteBuffers(1, &buffer);
		return true;
	}
	return false;
}

void Renderer::genRenderObject(unsigned int id) {
	renderObjects[id] = new RenderObject(gl::CState(gl::Context::getCurrentContext()), GL_TRIANGLES, 0, 0);
}

void Renderer::deleteRenderObject(unsigned int id) {
	delete renderObjects[id];
	renderObjects.erase(id);
}

RenderObject& Renderer::getRenderObject(unsigned int id) {
	if (renderObjects.count(id) == 0) {
		genRenderObject(id);
	}
	return *renderObjects[id];
}

void Renderer::loadMesh(unsigned int renderObjectId, unsigned int index, ModelBase& model, size_t meshId) {
	RenderObject& renderObject = getRenderObject(renderObjectId);
	unsigned int vbo = 0, indexBuffer = 0;
	vbo = genBuffer();
	renderObject.setVertexBufferObject(index, vbo);

	bindVertexArray(renderObject.vao);
	bindBuffer(GL_ARRAY_BUFFER, vbo);

	ObjectBase& object = *model.getObject(meshId);
	glBufferData(GL_ARRAY_BUFFER, object.getVerticesCount() * 4 * sizeof(float), &object.getVertices().at(0).x,
			GL_STATIC_DRAW);

	if (object.getIndicies().size() > 0) {
		renderObject.indexedDraw = true;
		renderObject.start = 0;
		renderObject.count = object.getIndicies().size() * 3;
		renderObject.type = object.getIndiciesType();
		renderObject.indicies = object.getIndiciesOffset();
		indexBuffer = genBuffer();
		renderObject.setIndexBufferObject(index, indexBuffer);
		bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, object.getIndicies().size() * sizeof(object.getIndicies().at(0).x) * 3,
				&object.getIndicies().at(0).x, GL_STATIC_DRAW);
	} else {
		renderObject.indexedDraw = false;
		renderObject.start = 0;
		renderObject.count = object.getVerticesCount();
	}

	bindVertexArray(renderObject.vao);
	bindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 0, 0);
	if (renderObject.indexedDraw) {
		bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	}
}

void Renderer::loadVertexArray(unsigned int renderObjectId, unsigned int index, size_t size, float* vertexArray, size_t vertexCount) {
	RenderObject& renderObject = getRenderObject(renderObjectId);
	unsigned int vbo = genBuffer();
	renderObject.setVertexBufferObject(index, vbo);
	bindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertexArray, GL_STATIC_DRAW);

	if (renderObject.start == 0 && renderObject.count == 0) { //Assume uninitialized
		renderObject.count = vertexCount;
	}

	bindVertexArray(renderObject.vao);
	bindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, static_cast<const void *>(0));
}

void Renderer::draw(unsigned int renderObjectId) {
	RenderObject& renderObject = getRenderObject(renderObjectId);
	bindVertexArray(renderObject.vao);
	if (renderObject.indexedDraw) {
		glDrawElements(renderObject.mode, renderObject.count, renderObject.type, renderObject.indicies);
	} else {
		glDrawArrays(renderObject.mode, renderObject.start, renderObject.count);
	}
}

void Renderer::deleteVertexArrays() {
	for (auto& i : vertexArrayObjectInstances) {
		if (i.second > 0) {
			glDeleteVertexArrays(1, &i.first);
		}
	}
	vertexArrayObjectInstances.clear();
}

void Renderer::deleteBuffers() {
	for (auto& i : bufferObjectInstances) {
		if (i.second > 0) {
			glDeleteBuffers(1, &i.first);
		}
	}
	bufferObjectInstances.clear();
}

void Renderer::deleteRenderObjects() {
	for (auto& i : renderObjects) {
		delete renderObjects[i.first];
	}
	renderObjects.clear();
}

void Renderer::logRenderObject(unsigned int renderObjectId, string name) {
	RenderObject& renderObject = getRenderObject(renderObjectId);
	cout << "---" << endl;
	cout << name << " [RenderObject]: [@" << &renderObject << "]" << endl;
	cout << "RenderObject.vao: " << renderObject.vao << "( current: " << currentVertexArrayObject << ")\n";
	cout << "RenderObject.indexedDraw: " << boolalpha << renderObject.indexedDraw << "\n";
	cout << "RenderObject.start: " << renderObject.start << "\n";
	cout << "RenderObject.count: " << renderObject.count << "\n";
	cout << "RenderObject.type: " << renderObject.type << "\n";
	cout << "RenderObject.indicies: " << renderObject.indicies << "\n";
	for (auto i : renderObject.vertexBufferObjects) {
		cout << "RenderObject.vertexBufferObjects[index(" << i.first << ")]: " << i.second << "\n";
	}
	for (auto i : renderObject.indexBufferObjects) {
		cout << "RenderObject.indexBufferObjects[index(" << i.first << ")]: " << i.second << "\n";
	}
	cout << "---" << endl;
}

}
}

