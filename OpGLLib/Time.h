/*
 * Time.h
 *
 *  Created on: 25.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_TIME_H_
#define OPGLLIB_TIME_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/CircularBuffer.h>

#include <chrono>

namespace OpGLLib {
namespace Time {

class FrameTime {
public:
	FrameTime();
	FrameTime(size_t cacheSize);
	~FrameTime();

	void setCacheSize(size_t size);

	void update();

	std::chrono::milliseconds getFrameTime();
	float getFrameRate();
private:
	std::chrono::time_point<std::chrono::system_clock> _lastFrame;
	OpGLLib::CircularBuffer<std::chrono::milliseconds> _frameCache;
};

}
}

#endif /* OPGLLIB_TIME_H_ */
