/*
 * Render.cpp
 *
 *  Created on: 10.01.2015
 *      Author: Michael
 */

#include <OpGLLib/Renderer.h>

using namespace std;
using namespace gl;

RenderObject::RenderObject(GLenum mode, size_t start, size_t count, bool indexedDraw, GLenum type, const void* indicies) {
	glGenVertexArrays(1, &vao);
	RenderObject::mode = mode;
	RenderObject::start = start;
	RenderObject::count = count;
	RenderObject::indexedDraw = indexedDraw;
	RenderObject::type = type;
	RenderObject::indicies = indicies;
}

RenderObject::~RenderObject() {
	glDeleteVertexArrays(1, &vao);
	for (size_t i = 0; i < bufferObjects.size(); i++) {
		glDeleteBuffers(1, &bufferObjects[i]);
	}
	vao = 0;
	bufferObjects.clear();
}

void RenderObject::addBufferObject(unsigned int vbo) {
	bufferObjects.push_back(vbo);
}

Renderer::Renderer() {

}

Renderer::~Renderer() {

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

bool Renderer::bindVertexBuffer(unsigned vbo) {
	if (currentVertexBufferObject == vbo) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		return false;
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		currentVertexBufferObject = vbo;
		return true;
	}
}

bool Renderer::bindBuffer(GLenum target, unsigned int buffer) {
	if (currentBuffeObject == buffer) {
		glBindBuffer(target, buffer);
		return false;
	} else {
		glBindBuffer(target, buffer);
		currentBuffeObject = buffer;
		return true;
	}
}

void Renderer::genRenderObject(unsigned int id) {
	renderObjects[id] = new RenderObject(GL_TRIANGLES, 0, 0);
}

void Renderer::deleteRenderObject(unsigned int id) {
	delete renderObjects[id];
	renderObjects.erase(id);
}

RenderObject& Renderer::getRenderObject(unsigned int id) {
	return *renderObjects[id];
}

void Renderer::loadMesh(unsigned int renderObjectId, unsigned int index, ModelWrapper&& model, size_t meshId) {
	RenderObject& renderObject = getRenderObject(renderObjectId);
	unsigned int vbo, indexBuffer;
	glGenBuffers(1, &vbo);
	renderObject.addBufferObject(vbo);

	bindVertexBuffer(vbo);

	std::unique_ptr<ObjectWrapper> objectWrapper = (&model)->getObjectWrapper(meshId);
	glBufferData(GL_ARRAY_BUFFER, objectWrapper->getVerticesCount() * 4 * sizeof(float), &objectWrapper->getVertices()->at(0).x,
			GL_STATIC_DRAW);

	if (objectWrapper->getIndicies()->size() > 0) {
		renderObject.indexedDraw = true;
		renderObject.start = 0;
		renderObject.count = objectWrapper->getIndicies()->size() * 3;
		renderObject.type = objectWrapper->getIndiciesType();
		renderObject.indicies = objectWrapper->getIndiciesOffset();
		glGenBuffers(1, &indexBuffer);
		renderObject.addBufferObject(indexBuffer);
		bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objectWrapper->getIndicies()->size() * sizeof(objectWrapper->getIndicies()->at(0).x) * 3,
				&objectWrapper->getIndicies()->at(0).x, GL_STATIC_DRAW);
	} else {
		renderObject.indexedDraw = false;
		renderObject.start = 0;
		renderObject.count = objectWrapper->getVerticesCount();
	}

	bindVertexArray(renderObject.vao);
	bindVertexBuffer(vbo);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 0, 0);
	if (renderObject.indexedDraw) {
		bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	}

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
