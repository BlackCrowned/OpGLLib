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

namespace Renderer {
class Renderer;

class RenderObject {
public:
	RenderObject(Renderer* renderer, gl::GLenum mode, size_t start, size_t count, bool indexedDraw = false, gl::GLenum type =
			gl::GL_UNSIGNED_SHORT, const void* indicies = 0);
	RenderObject(RenderObject const& other);
	~RenderObject();

	void setVertexBufferObject(unsigned int index, unsigned int buffer);
	void setIndexBufferObject(unsigned int index, unsigned int buffer);
	unsigned int getVertexBufferObject(unsigned int index);
	unsigned int getIndexBufferObject(unsigned int index);
	void enableVertexAttribArray(unsigned int index);
	void disableVertexAttribArray(unsigned int index);

	friend class Renderer;
private:
	unsigned int vao;
	Renderer* renderer;
	gl::GLenum mode;
	size_t start;
	size_t count;
	bool indexedDraw;
	gl::GLenum type;
	const void* indicies;
	std::map<unsigned int, unsigned int> vertexBufferObjects;
	std::map<unsigned int, unsigned int> indexBufferObjects;
};

class Renderer {
public:
	Renderer();
	~Renderer();

	unsigned int genVertexArray();
	unsigned int manageVertexArray(unsigned int vao);
	bool bindVertexArray(unsigned int vao);
	bool deleteVertexArray(unsigned int vao);

	unsigned int genBuffer();
	unsigned int manageBuffer(unsigned int buffer);
	bool bindBuffer(gl::GLenum target, unsigned int buffer);
	bool deleteBuffer(unsigned int buffer);

	void genRenderObject(unsigned int id);
	void deleteRenderObject(unsigned int id);
	RenderObject& getRenderObject(unsigned int id);

	void loadMesh(unsigned int renderObjectId, unsigned int index, ModelWrapper&& modelWrapper, size_t meshId);
	void loadVertexArray(unsigned int renderObjectId, unsigned int index, size_t size, float* vertexArray, size_t vertexCount);

	void draw(unsigned int renderObjectId);


	void logRenderObject(unsigned int renderObjectId, std::string name = "");
private:
	void deleteVertexArrays();
	void deleteBuffers();
	void deleteRenderObjects();

	unsigned int currentVertexArrayObject = 0;
	unsigned int currentBufferObject = 0;
	std::map<unsigned int, int> vertexArrayObjectInstances;
	std::map<unsigned int, int> bufferObjectInstances;
	std::map<unsigned int, RenderObject*> renderObjects;
};

}

#endif /* OPGLLIB_RENDERER_H_ */
