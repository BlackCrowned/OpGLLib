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

#include <OpGLLib/gl/ModelLoader.h>
#include <OpGLLib/Context.h>
#include <OpGLLib/State.h>
#include <OpGLLib/Data.h>
#include <OpGLLib/gl/Texture.h>

#include <map>

namespace OpGLLib {
namespace gl {

class Render {
public:
	Render();
	~Render();

	unsigned int setVertexArrayObject(unsigned int vao = 0);

	//Buffers

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

	//Textures

	void setTexture2D(unsigned int textureUnit, Texture2D texture, int sampler2DLocation);
	void setTexture2D(::gl::GLenum textureUnit, Texture2D texture, int sampler2DLocation);
	void unsetTexture2D(unsigned int textureUnit);
	void unsetTexture2D(::gl::GLenum textureUnit);

	void updateDrawSettings(::gl::GLenum mode);
	void updateDrawSettings(int first, int count);
	void updateDrawSettings(int count, ::gl::GLenum type, const void* indicies);
	void updateDrawSettings(bool indexedDraw);

	void enableTextures();
	void disableTextures();

	void draw();
private:
	glbinding::ContextHandle _context;
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

		bool textures = true;
		int texture2DCount = 0;
	};
	DrawSettings _drawSettings;

	std::map<unsigned int, Texture2D> _texture2Ds;
	std::map<unsigned int, int> _sampler2Ds;
};
}

}

#include <OpGLLib/gl/Render.inl>

#endif /* OPGLLIB_RENDERER_H_ */
