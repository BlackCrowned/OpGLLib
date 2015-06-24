/*
 * Data.inl
 *
 *  Created on: 22.06.2015
 *      Author: mimoe
 */

namespace OpGLLib {

template<class T> Data::BufferSettings::BufferSettings(T* addr) {
	vertexSettings = Data::getVertexSettings(addr);
}

template<class T> void Data::setVertexSettings(T* addr, std::shared_ptr<VertexSettings> vertexSettings) {
	//Check for existing vertexSettings with key 'addr'
	if (_vertexSettings.count(reinterpret_cast<void*>(addr)) > 0) {
		return;
	}

	//Store vertexSettings with key 'addr'
	_vertexSettings[reinterpret_cast<void*>(addr)] = vertexSettings;
}

template<class containerT> void Data::setVertexSettings(containerT& data, ::gl::GLenum type) {
	//Extract addr
	void* addr = reinterpret_cast<void*>(&data[0][0]);

	//Check for existing vertexSettings with key 'addr'
	if (_vertexSettings.count(reinterpret_cast<void*>(addr)) > 0) {
		return;
	}

	//Create vertexSettings and set values
	std::shared_ptr<VertexSettings> vertexSettings(new VertexSettings());
	vertexSettings->vertexCount = data.size();
	vertexSettings->vectorLength = data[0].length();
	vertexSettings->valueSize = sizeof(data[0][0]);
	vertexSettings->valueType = type;

	//Store vertexSettings with key 'addr'
	_vertexSettings[addr] = vertexSettings;
}

template<class T> void Data::setBufferSettings(unsigned int buffer, T* addr) {
	return setBufferSettings(buffer, getVertexSettings(addr));
}

template<class T> auto Data::getVertexSettings(T* addr) -> std::shared_ptr<VertexSettings> {
	//Check if vertexSettings with key 'addr' exist
	if (_vertexSettings.count(reinterpret_cast<void*>(addr)) == 0) {
		return std::shared_ptr<VertexSettings>();
	}

	//Return vertexSettings with key 'addr'
	return _vertexSettings[reinterpret_cast<void*>(addr)];
}

template<class T> void Data::deleteVertexSettings(T* addr) {
	_vertexSettings.erase(reinterpret_cast<void*>(addr));
}

}

