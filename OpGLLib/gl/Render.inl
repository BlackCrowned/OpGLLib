/*
 * Renderer.inl
 *
 *  Created on: 16.06.2015
 *      Author: mimoe
 */

namespace OpGLLib {
namespace gl {

template<class T> ModelRenderSetting::ModelRenderSetting(int vertexAttribute, int override, ::gl::GLboolean normalize, size_t stride,
		const void* offset, T start, ::gl::GLenum usage) :
		vertexAttribute(vertexAttribute), override(override), normalize(normalize), stride(stride), offset(offset),
				start(reinterpret_cast<size_t>(start)), usage(usage) {
}

template<class containerT> unsigned int Render::setBuffer(::gl::GLenum target, containerT& data, ::gl::GLenum type, ::gl::GLenum usage) {
	//Bind VAO
	bindVertexArrayObject();

	//Creating and binding buffer
	unsigned int buffer = State::genBuffer();
	bindBuffer(target, buffer);

	//Saving Buffer Settings
//	_bufferSettings[buffer].vertexCount = data.size();
//	_bufferSettings[buffer].vectorLength = data[0].length();
//	_bufferSettings[buffer].valueSize = sizeof(data[0][0]);
//	_bufferSettings[buffer].valueType = type;
	Data::setVertexSettings(data, type);
	Data::setBufferSettings(buffer, &data[0][0]);

	//Copying data into buffer
	::gl::glBufferData(target, data.size() * data[0].length() * sizeof(data[0][0]), &data[0][0], usage);

	return buffer;
}

template<class containerT> unsigned int Render::setVertexBuffer(containerT& data, ::gl::GLenum type, ::gl::GLenum usage) {
	return setBuffer(::gl::GL_ARRAY_BUFFER, data, type, usage);
}

template<class containerT> unsigned int Render::setIndexBuffer(containerT& data, ::gl::GLenum type, ::gl::GLenum usage) {
	return setBuffer(::gl::GL_ELEMENT_ARRAY_BUFFER, data, type, usage);
}
}
}
