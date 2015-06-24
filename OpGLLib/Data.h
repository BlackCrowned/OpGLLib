/*
 * Data.h
 *
 *  Created on: 18.06.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_DATA_H_
#define OPGLLIB_DATA_H_

#define INCLUDE_GLM
#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

#include <map>
#include <memory>

namespace OpGLLib {

class Data {
public:
	Data() = delete;
	~Data() = delete;

	class VertexSettings {
	public:
		int vertexCount = 0;
		int vectorLength = 0;
		int valueSize = 0;
		::gl::GLenum valueType;
	};

	class BufferSettings {
	public:
		template<class T>BufferSettings(T* addr);
		BufferSettings(std::shared_ptr<VertexSettings>&);
		std::shared_ptr<VertexSettings> vertexSettings;
	};

	template<class T>static std::shared_ptr<VertexSettings> getVertexSettings(T* addr);

	static std::shared_ptr<BufferSettings> getBufferSettings(unsigned int buffer);


	template<class T>static void setVertexSettings(T* addr, std::shared_ptr<VertexSettings> vertexSettings);
	template<class containerT> static void setVertexSettings(containerT& data, ::gl::GLenum type);

	static void setBufferSettings(unsigned int buffer, std::shared_ptr<BufferSettings> bufferSettings);
	static void setBufferSettings(unsigned int buffer, std::shared_ptr<VertexSettings> vertexSettings);
	template<class T>static void setBufferSettings(unsigned int buffer, T* addr);

	template<class T>static void deleteVertexSettings(T* addr);

	static void deleteBufferSettings(unsigned int buffer);

private:
	static std::map<void*, std::shared_ptr<VertexSettings>> _vertexSettings;
	static std::map<unsigned int, std::shared_ptr<BufferSettings>> _bufferSettings;
};

}

#include <OpGLLib/Data.inl>

#endif /* OPGLLIB_DATA_H_ */
