/*
 * Animator.h
 *
 *  Created on: 18.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_ANIMATOR_H_
#define OPGLLIB_ANIMATOR_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/Callbacks.h>
#include <OpGLLib/Transformation.h>
#include <OpGLLib/Debug.h>

enum AnimationAttributeTypes {
	translate, scale, rotate, orient
};

enum AnimationObjectStatus {
	shown, hidden
};

enum AnimationCallbackEvents {
	onStart = 0x1, onUpdate = 0x2, onComplete = 0x4, onRestart = 0x8, onReverse = 0x10, onRepeat = 0x20,
};

enum AnimationCallbackTypes {
	function, animationObject
};

enum AnimationSettings {
	restart = 0x1, reverse = 0x2, restartOnce = 0x4, reverseOnce = 0x8, repeat = 0x10, repeatOnce = 0x20
};

enum InterpolationFunctions {
	linear, accelerate, decelerate, acceleratedecelerate
};

class Animator;
class AnimationObject;

namespace detail {
void addCallback(Animator*& animator, glm::mat4*& matrix, AnimationObject& animationObject);
}

template<class T> class AnimationAttribute {
public:
	AnimationAttribute();
	AnimationAttribute(T attribute, AnimationAttributeTypes type = translate, InterpolationFunctions interpolator = acceleratedecelerate,
			float progressStart = 0.0f, float progressEnd = 1.0f);
	~AnimationAttribute();

	void setAttribute(T attribute, AnimationAttributeTypes type = translate, InterpolationFunctions interpolator = acceleratedecelerate,
			float progressStart = 0.0f, float progressEnd = 1.0f);

	T const& getAttribute();
	AnimationAttributeTypes getType();
	InterpolationFunctions getInterpolator();
	float getProgressStart();
	float getProgressEnd();

	void reverse();

private:
	T attribute;
	AnimationAttributeTypes type;
	InterpolationFunctions interpolator;
	float progressStart;
	float progressEnd;
};

class AnimationObject {
public:
	AnimationObject();
	AnimationObject(std::initializer_list<AnimationAttribute<glm::vec3> > attributes);
	~AnimationObject();

	void addAttribute(AnimationAttribute<glm::vec3> attribute);

	template<typename R = void, typename ...Args>
	void addCallback(AnimationCallbackEvents event, std::function<R(Args...)> const& func, Args&& ...args) {
		callbacks.addCallback<R, Args...>(event, func, args...,
				((event == onUpdate) || (event == onRestart) || (event == onReverse)) ? 0 : removeWhenFinished);
	}
	;
	template<typename Function, typename ...Args>
	void addCallback(AnimationCallbackEvents event, Function const& func, Args&& ...args) {
		callbacks.addCallback<Function, Args...>(event, func, args...,
				((event == onUpdate) || (event == onRestart) || (event == onReverse)) ? 0 : removeWhenFinished);
	}
	;
	template<typename R = void, typename Function, typename ...Args>
	void addCallback(AnimationCallbackEvents event, Function const& func, Args&& ...args) {
		callbacks.addCallback<R, Function, Args...>(event, func, args...,
				((event == onUpdate) || (event == onRestart) || (event == onReverse)) ? 0 : removeWhenFinished);
	}
	;
	void addCallback(AnimationCallbackEvents event, AnimationObject& animationObject) {
		callbacks.addCallback<void, Animator*&, glm::mat4*&, AnimationObject&>(event, detail::addCallback, std::ref(animator),
				std::ref(matrix), std::ref(animationObject),
				((event == onUpdate) || (event == onRestart) || (event == onReverse)) ? 0 : removeWhenFinished);
	}

	void setStartTime();
	void setStartTime(std::chrono::time_point<std::chrono::system_clock> start);
	void setDuration(std::chrono::milliseconds duration);
	void setDuration(int milliseconds);
	void setDelay(std::chrono::milliseconds delay);
	void setDelay(int milliseconds);

	void setMatrix(glm::mat4* matrix);
	void setAnimator(Animator* animator);

	void setSettings(int settings);

	void reverse();

	void animationStart();
	void animationUpdate();
	void animationComplete();

	bool complete();
private:
	Callbacks<int> callbacks;

	glm::mat4 oldMatrix;

	glm::mat4* matrix;
	Animator* animator;

	std::deque<AnimationAttribute<glm::vec3> > attributes;

	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> lastTick;
	std::chrono::milliseconds duration;
	std::chrono::milliseconds delay;

	int settings;
	int reversed;

	friend class Animator;
};

class Animator: private Transformation {
public:
	Animator();
	~Animator();

	void animate(glm::mat4* matrix, AnimationObject&& animationObject);
	void animate(glm::mat4* matrix, AnimationObject& animationObject);
	glm::mat4* animate(AnimationObject&& animationObject);
	glm::mat4* animate(AnimationObject& animationObject);

	void stop(glm::mat4* matrix, bool stopAll, bool finish);

	void update();

	void translate(glm::mat4* matrix, AnimationAttribute<glm::vec3>& attribute, float progress);
	void scale(glm::mat4* matrix, AnimationAttribute<glm::vec3>& attribute, float progress);
	void rotate(glm::mat4* matrix, AnimationAttribute<glm::vec3>& attribute, float progress);
	void orient(glm::mat4* matrix, AnimationAttribute<glm::vec3>& attribute, float progress);

	float interpolate(std::chrono::time_point<std::chrono::system_clock> startTime, std::chrono::milliseconds duration,
			std::chrono::milliseconds delay, InterpolationFunctions interpolator, float start, float end);

private:
	std::map<glm::mat4*, std::deque<AnimationObject> > queue;
};

template class AnimationAttribute<glm::vec3> ;

using AnimationAttributeV3 = AnimationAttribute<glm::vec3>;

#endif /* OPGLLIB_ANIMATOR_H_ */
