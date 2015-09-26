/*
 * Data.cpp
 *
 *  Created on: 18.06.2015
 *      Author: mimoe
 */

#include <OpGLLib/Data.h>

namespace OpGLLib {

std::map<ptrdiff_t, std::shared_ptr<Data::VertexSettings>> Data::_vertexSettings;
std::map<unsigned int, std::shared_ptr<Data::BufferSettings>> Data::_bufferSettings;

Data::BufferSettings::BufferSettings(std::shared_ptr<VertexSettings>& vertexSettings) {
	Data::BufferSettings::vertexSettings = vertexSettings;
}

void Data::setBufferSettings(unsigned int buffer, std::shared_ptr<BufferSettings> bufferSettings) {
	//Check for existing bufferSettings with key 'buffer'
	if (_bufferSettings.count(buffer) > 0) {
		return;
	}

	//Store bufferSettings with key 'buffer'
	_bufferSettings[buffer] = bufferSettings;
}

void Data::setBufferSettings(unsigned int buffer, std::shared_ptr<VertexSettings> vertexSettings) {
	//Check for existing bufferSettings with key 'buffer'
	if (_bufferSettings.count(buffer) > 0) {
		return;
	}

	//Create bufferSettings and store it with key 'buffer'
	_bufferSettings[buffer] = std::shared_ptr<BufferSettings>(new BufferSettings(vertexSettings));
}

auto Data::getBufferSettings(unsigned int buffer) -> std::shared_ptr<BufferSettings>{
	//Check if bufferSettings with key 'buffer' exists
	if (_bufferSettings.count(buffer) == 0) {
		return std::shared_ptr<BufferSettings>();
	}

	//Return bufferSettings with key 'buffer'
	return _bufferSettings[buffer];
}

void Data::deleteBufferSettings(unsigned int buffer) {
	_bufferSettings.erase(buffer);
}

} /* namespace OpGLLib */
