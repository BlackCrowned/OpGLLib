/*
 * Render.h
 *
 *  Created on: 10.01.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_RENDERER_H_
#define OPGLLIB_RENDERER_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/ModelLoader.h>

class Renderer;

class RenderObject {
public:
	RenderObject(gl::GLenum mode, size_t start, size_t count, bool indexedDraw = false, gl::GLenum type = gl::GL_UNSIGNED_SHORT, const void* indicies = 0);
	~RenderObject();

	void addBufferObject(unsigned int);

	friend class Renderer;
private:
	unsigned int vao;
	gl::GLenum mode;
	size_t start;
	size_t count;
	bool indexedDraw;
	gl::GLenum type;
	const void* indicies;
	std::deque<unsigned int> bufferObjects;
};

class Renderer {
public:
	Renderer();
	~Renderer();

	bool bindVertexArray(unsigned int vao);
	bool bindVertexBuffer(unsigned int vbo);
	bool bindBuffer(gl::GLenum target, unsigned int buffer);

	void genRenderObject(unsigned int id);
	void deleteRenderObject(unsigned int id);
	RenderObject& getRenderObject(unsigned int id);

	void loadMesh(unsigned int renderObjectId, unsigned int index, ModelWrapper&& modelWrapper, size_t meshId);

	void draw(unsigned int renderObjectId);

private:
	unsigned int currentVertexArrayObject = 0;
	unsigned int currentVertexBufferObject = 0;
	unsigned int currentBuffeObject = 0;
	std::map<unsigned int, RenderObject*> renderObjects;
};

#endif /* OPGLLIB_RENDERER_H_ */
