/*
 * Renderer.inl
 *
 *  Created on: 16.06.2015
 *      Author: mimoe
 */

namespace OpGLLib {
namespace gl {

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
	std::shared_ptr<Data::VertexSettings> vertexSettings(new Data::VertexSettings());
	vertexSettings->vertexCount = data.size();
	vertexSettings->vectorLength = data[0].length();
	vertexSettings->valueSize = sizeof(data[0][0]);
	vertexSettings->valueType = type;
	Data::setVertexSettings(&data[0][0], vertexSettings);
	Data::setBufferSettings(buffer, std::shared_ptr<Data::BufferSettings>(new Data::BufferSettings(vertexSettings)));

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

