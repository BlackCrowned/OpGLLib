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
	if (_vertexSettings.count(reinterpret_cast<ptrdiff_t>(addr)) > 0) {
		return;
	}

	//Store vertexSettings with key 'addr'
	_vertexSettings[reinterpret_cast<ptrdiff_t>(addr)] = vertexSettings;
}

template<class containerT> void Data::setVertexSettings(containerT& data, ::gl::GLenum type) {
	//Extract addr
	ptrdiff_t addr = reinterpret_cast<ptrdiff_t>(&data[0][0]);

	//Check for existing vertexSettings with key 'addr'
	if (_vertexSettings.count(reinterpret_cast<ptrdiff_t>(addr)) > 0) {
		return;
	}

	//Create vertexSettings and set values
	std::shared_ptr<VertexSettings> vertexSettings(new VertexSettings());
	vertexSettings->vertexCount = data.size();
	vertexSettings->vectorLength = data[0].length();
	vertexSettings->valueSize = sizeof(data[0].x);
	//vertexSettings->valueType = type;
	vertexSettings->valueType = gl::GLTypes::getType<decltype(data[0].x)>();

	//Store vertexSettings with key 'addr'
	_vertexSettings[addr] = vertexSettings;
}

template<class T> void Data::setBufferSettings(unsigned int buffer, T* addr) {
	return setBufferSettings(buffer, getVertexSettings(addr));
}

template<class T> auto Data::getVertexSettings(T* addr) -> std::shared_ptr<VertexSettings> {
	//Check if vertexSettings with key 'addr' exist
	if (_vertexSettings.count(reinterpret_cast<ptrdiff_t>(addr)) == 0) {
		return std::shared_ptr<VertexSettings>();
	}

	//Return vertexSettings with key 'addr'
	return _vertexSettings[reinterpret_cast<ptrdiff_t>(addr)];
}

template<class T> void Data::deleteVertexSettings(T* addr) {
	_vertexSettings.erase(reinterpret_cast<ptrdiff_t>(addr));
}

}

