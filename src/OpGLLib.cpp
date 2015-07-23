#include <OpGLLib/OpGLLib.h>

using namespace std;
using namespace gl;

namespace OpGLLib {

OpGLLib::OpGLLib() {
#ifndef RElEASE
	_debug.enableLogging();
#endif
}

OpGLLib::OpGLLib(glbinding::ContextHandle context) {
	_setContext(context);
#ifndef RElEASE
	_debug.enableLogging();
#endif
}

void OpGLLib::_setContext(glbinding::ContextHandle context) {
	glbinding::Binding::useContext(context);
}

chrono::milliseconds OpGLLib::getFrameTime(int range) {
	chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
	chrono::milliseconds duration = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch() - lastFrame.time_since_epoch());
	if (lastFrame.time_since_epoch().count() == 0) {
		lastFrame = now;
		return chrono::milliseconds(0);
	}
	frameDuration.push_front(duration);
	lastFrame = now;
	if (range == 1) {
		if (frameDuration.size() > 1000) {
			frameDuration.resize(150);
		}
		return duration;
	}
	else if (range > 1) {
		int frameDurationSize = frameDuration.size();
		if (frameDurationSize > range * 12) {
			frameDuration.resize(range * 10);
		}
		if (frameDurationSize > range) {
			for (int i = 1; i < range; i++) {
				duration += frameDuration.at(i);
			}
			return duration / range;
		}
		else {
			for (int i = 1; i < frameDurationSize; i++) {
				duration += frameDuration.at(i);
			}
			return duration / frameDurationSize;
		}
	}
	else {
		return chrono::milliseconds(0);
	}

}

float OpGLLib::getFrameRate(int range) {
	int frameTime = getFrameTime(range).count();
	return frameTime == 0 ? 1 : 1000.0f / frameTime;
}
}
