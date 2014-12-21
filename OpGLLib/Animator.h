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

enum AnimationAttributeTypes {
	translate, scale, rotate, translateTo, scaleTo, rotateTo
};

enum AnimationAttributeInclusion {
	x = 0x0, r = 0x0, y = 0x2, g = 0x2, z = 0x4, b = 0x4, w = 0x8, a = 0x8, all = 0x10
};

enum AnimationObjectStatus {
	shown, hidden
};

enum AnimationCallbackEvents {
	start, done, update
};

enum AnimationCallbackTypes {
	function, animationObject
};

enum InterpolationFunctions {
	accelerate, decelelerate, acceleratedecelerate
};

class Animator;
class AnimationObject;
void _addCallback(Animator* animator, glm::mat4* modelMatrix, AnimationObject animationObject);

template<class T> class AnimationAttribute {
public:
	AnimationAttribute();
	AnimationAttribute(T attribute, AnimationAttributeTypes type, int inclusion = AnimationAttributeInclusion::all);
	~AnimationAttribute();

	void setAttribute(T attribute, AnimationAttributeTypes type, int inclusion = AnimationAttributeInclusion::all);
	T const& getAttribute();

	AnimationAttributeTypes getType();
	int getInclusion();

	bool operator==(AnimationAttribute<T> attribute);

private:
	T attribute;
	AnimationAttributeTypes type;
	int inclusion;
};

class AnimationObject {
public:
	AnimationObject();
	~AnimationObject();

	void addAttribute(AnimationAttribute<glm::vec4> attribute, float progressStart = 0, float progressEnd = 1.0f);
	void addAttribute(std::string attribute, AnimationAttributeTypes type, float progressStart = 0, float progressEnd = 1.0f);

	template<typename Function, typename ...Args>
	void addCallback(AnimationCallbackEvents event, Function const& func, Args const& ...args) {
		callbacks.addCallback<Function, Args...>(event, func, args..., event == update ? 0 : removeWhenFinished);
	}
	;
	void addCallback(AnimationCallbackEvents event, AnimationObject animationObject) {
		callbacks.addCallback<decltype(_addCallback), Animator*, glm::mat4*, AnimationObject>(event, _addCallback, animator, modelMatrix,
				animationObject, event == update ? 0 : removeWhenFinished);
	}

	void setStartTime(std::chrono::time_point<std::chrono::system_clock> start);
	void setDuration(std::chrono::milliseconds duration);

	void setModelMatrix(glm::mat4* modelMatrix);
	void setAnimator(Animator* animator);

	void animationStart();
	void animationUpdate();
	void animationDone();
private:
	Callbacks<int> callbacks;

	glm::mat4* modelMatrix;
	Animator* animator;

	std::deque<std::tuple<AnimationAttribute<glm::vec4>, float, float> > attributes;

	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::milliseconds duration;

	friend class Animator;
};

class Animator {
public:
	Animator();
	~Animator();

	void animate(glm::mat4 *modelMatrix, AnimationObject animationObject);
	glm::mat4* animate(AnimationObject animationObject);

	void update();

	void interpolate(std::chrono::time_point<std::chrono::system_clock> startTime, std::chrono::milliseconds duration,
			InterpolationFunctions interpolator, float start, float end);

private:
	std::map<glm::mat4*, std::deque<AnimationObject> > queue;
};

template class AnimationAttribute<glm::vec4> ;

using AnimationAttributeV4 = AnimationAttribute<glm::vec4>;

#endif /* OPGLLIB_ANIMATOR_H_ */
