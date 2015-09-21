/*
 * Time.cpp
 *
 *  Created on: 25.07.2015
 *      Author: mimoe
 */

#include <OpGLLib/Time.h>
#include <iostream>

namespace OpGLLib {
namespace Time {

FrameTime::FrameTime() :
		_lastFrame(std::chrono::system_clock::now()), _frameCache(120) {

}

FrameTime::FrameTime(size_t cacheSize) :
		_lastFrame(std::chrono::system_clock::now()), _frameCache(cacheSize) {

}

FrameTime::~FrameTime() {

}

void FrameTime::setCacheSize(size_t size) {
	//Create new _frameCache with new size
	decltype(_frameCache) newCache(size);
	_frameCache.swap(newCache);
}

void FrameTime::update() {
	//Get current time
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

	//Calculate time difference to last frame
	std::chrono::milliseconds frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(
			now.time_since_epoch() - _lastFrame.time_since_epoch());

	//Set now to _lastFrame
	_lastFrame = now;

	//Add frameTime to _frameCache
	_frameCache.push_front(frameTime);
}

std::chrono::milliseconds FrameTime::getFrameTime() {
	std::chrono::milliseconds frameTime(0);
	//Calculate frameTime from cache
	for (auto it = _frameCache.begin(); it != _frameCache.end(); it++) {
		frameTime += *it;
	}
	frameTime /= _frameCache.size();

	return frameTime;
}

float FrameTime::getFrameRate() {
	std::chrono::milliseconds::rep frameTime = getFrameTime().count();
	return frameTime == 0 ? 1 : (1000.0f / static_cast<float>(frameTime));
}

}
}
