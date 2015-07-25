/*
 * Time.h
 *
 *  Created on: 25.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_TIME_H_
#define OPGLLIB_TIME_H_

#include <OpGLLib/internal.h>

#include <chrono>
#include <deque>

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
	std::deque<std::chrono::milliseconds> _frameCache;
	size_t _cacheSize;
};

}
}

#endif /* OPGLLIB_TIME_H_ */
