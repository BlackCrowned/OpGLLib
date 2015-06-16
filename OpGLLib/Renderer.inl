/*
 * Renderer.inl
 *
 *  Created on: 16.06.2015
 *      Author: mimoe
 */

namespace OpGLLib {
namespace gl {
template<class containerT> void Render::setVertexBuffer(unsigned int buffer, containerT data, ::gl::GLenum type) {
	//Binding Buffers
	bindVertexBufferObject();
	bindBuffer(::gl::GL_ARRAY_BUFFER, buffer);

	//Saving Buffer Settings
	_bufferSettings[buffer].vertexCount = data.size();
	_bufferSettings[buffer].vectorLength = data[0].length();
	_bufferSettings[buffer].valueSize = sizeof(data[0][0]);
	_bufferSettings[buffer].valueType = type;

	//Copying data into buffer
	::gl::glBufferData(::gl::GL_ARRAY_BUFFER, data.size() * data[0].length() * sizeof(data[0][0]), &data[0][0], ::gl::GL_STATIC_DRAW);
}

template<class containerT> void Render::setIndexBuffer(unsigned int buffer, containerT data, ::gl::GLenum type) {
	//Binding Buffers
	bindVertexBufferObject();
	bindBuffer(::gl::GL_ELEMENT_ARRAY_BUFFER, buffer);

	//Saving Buffer Settings
	_bufferSettings[buffer].vertexCount = data.size();
	_bufferSettings[buffer].vectorLength = data[0].length();
	_bufferSettings[buffer].valueSize = sizeof(data[0][0]);
	_bufferSettings[buffer].valueType = type;

	//Copying data into buffer
	::gl::glBufferData(::gl::GL_ELEMENT_ARRAY_BUFFER, data.size() * data[0].length() * sizeof(data[0][0]), &data[0][0],
			::gl::GL_STATIC_DRAW);
}
}
}

