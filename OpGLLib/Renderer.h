/*
 * Render.h
 *
 *  Created on: 10.01.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_RENDERER_H_
#define OPGLLIB_RENDERER_H_

#define INCLUDE_GML
#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <OpGLLib/ModelLoader.h>
#include <OpGLLib/Context.h>
#include <OpGLLib/State.h>

#include <map>

namespace OpGLLib {

namespace gl {

class Render {
public:
	Render();
	~Render();

	unsigned int setVertexArrayObject(unsigned int vao = 0);

	void bindVertexArrayObject();

	template<class containerT> unsigned int setBuffer(::gl::GLenum target, containerT& data, ::gl::GLenum type, ::gl::GLenum usage =
			::gl::GL_STATIC_DRAW);

	template<class containerT> unsigned int setVertexBuffer(containerT& data, ::gl::GLenum type, ::gl::GLenum usage = ::gl::GL_STATIC_DRAW);

	template<class containerT> unsigned int setIndexBuffer(containerT& data, ::gl::GLenum type, ::gl::GLenum usage = ::gl::GL_STATIC_DRAW);

	void bindBuffer(::gl::GLenum target, unsigned int& buffer);

	void setVertexAttribute(unsigned int index, unsigned int vertexBuffer, ::gl::GLboolean normalize = ::gl::GL_FALSE, size_t stride = 0,
			const void* offset = 0, int start = 0);
	void setVertexAttribute(unsigned int index, unsigned int vertexBuffer, unsigned int indexBuffer, ::gl::GLboolean normalize =
			::gl::GL_FALSE, size_t stride = 0, const void* offset = 0, const void* indicies = 0);

	void enableVertexAttribute(unsigned int index);
	void disableVertexAttribute(unsigned int index);

	void updateDrawSettings(::gl::GLenum mode);
	void updateDrawSettings(int first, int count);
	void updateDrawSettings(int count, ::gl::GLenum type, const void* indicies);
	void updateDrawSettings(bool indexedDraw);

	void draw();
private:
	unsigned int _vertexArrayObject;
	struct BufferSettings {
		int vertexCount = 0;
		int vectorLength = 0;
		int valueSize = 0;
		::gl::GLenum valueType;
	};
	std::map<size_t, BufferSettings> _bufferSettings;
	struct DrawSettings {
		::gl::GLenum mode = ::gl::GL_TRIANGLES;
		bool indexedDraw = false;
		int first = 0;
		int count = 0;
		int indiciesCount = 0;
		::gl::GLenum indiciesType;
		const void* indicies = 0;
	};
	DrawSettings _drawSettings;

};
}
namespace Renderer {
class Renderer;

class RenderObject {
public:
	RenderObject(gl::CState cState, ::gl::GLenum mode, size_t start, size_t count, bool indexedDraw = false, ::gl::GLenum type =
			::gl::GL_UNSIGNED_SHORT, const void* indicies = 0);
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
	gl::CState cState;
	::gl::GLenum mode;
	size_t start;
	size_t count;
	bool indexedDraw;
	::gl::GLenum type;
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
	bool bindBuffer(::gl::GLenum target, unsigned int buffer);
	bool deleteBuffer(unsigned int buffer);

	unsigned int genTexture();
	unsigned int manageTexture(unsigned int texture);
	bool bindTexture(unsigned int texture);
	bool deleteTexture(unsigned int texture);

	void genRenderObject(unsigned int id);
	void deleteRenderObject(unsigned int id);
	RenderObject& getRenderObject(unsigned int id);

	void loadMesh(unsigned int renderObjectId, unsigned int index, std::shared_ptr<ModelBase> model, size_t meshId);
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
}

#include <OpGLLib/Renderer.inl>

#endif /* OPGLLIB_RENDERER_H_ */
