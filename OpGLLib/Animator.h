/*
 * Animator.h
 *
 *  Created on: 18.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_ANIMATOR_H_
#define OPGLLIB_ANIMATOR_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/ModelLoader.h>
#include <OpGLLib/Callbacks.h>

enum AnimationAttributeTypes {
	translate, scale, rotate, transform, translateTo, scaleTo, rotateTo, transformTo
};

enum AnimationAttributeInclusion {
	x = 0x0, r = 0x0, y = 0x2, g = 0x2, z = 0x4, b = 0x4, w = 0x8, a = 0x8, all = 0x10
};

enum AnimationAttributeTarget {
	position, color
};

enum AnimationObjectStatus {
	shown, hidden
};

enum AnimationCallbackEvents {
	start, done, update
};

enum InterpolationFunctions {
	accelerate, decelelerate, acceleratedecelerate
};

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

	void addUniformAttribute(AnimationAttribute<glm::vec4> attribute, AnimationAttributeTarget target =
			AnimationAttributeTarget::position, float progressStart = 0, float progressEnd = 1.0f);
	void addUniformAttribute(std::string attribute, AnimationAttributeTypes type,
			AnimationAttributeTarget target = AnimationAttributeTarget::position, float progressStart = 0, float progressEnd = 1.0f);
	void addPerVertexAttribute(AnimationAttribute<Object> attribute, AnimationAttributeTarget target =
			AnimationAttributeTarget::position, float progressStart = 0, float progressEnd = 1.0f);

	template<typename Function, typename ...Args>
	void addCallback(AnimationCallbackEvents event, Function const& func, Args const& ...args) {
		callbacks.addCallback<Function, Args...>(event, func, args..., removeWhenFinished);
	};

	void setStartTime(std::chrono::time_point<std::chrono::system_clock> start);
	void setDuration(std::chrono::milliseconds duration);
private:
	Object *object;

	AnimationObjectStatus objectStatus;
	Object *objectVisible;

	Callbacks<int> callbacks;

	std::deque<std::tuple<AnimationAttributeTypes, int, AnimationAttributeTarget, float, float> > attributes;
	std::deque<AnimationAttribute<glm::vec4> > uniformAttributes;
	std::deque<AnimationAttribute<Object> > perVertexAttributes;

	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::milliseconds duration;
};

class Animator {
public:
	Animator();
	~Animator();

	void translate(Object *model, AnimationAttribute<glm::vec3> attribute, float progress);
	void scale(Object *model, AnimationAttribute<glm::vec3> attribute, float progress);
	void rotate(Object *model, AnimationAttribute<glm::vec3> attribute, float progress);
	void transform(Object *model, AnimationAttribute<Object> attribute, float progress);

	void interpolate(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::milliseconds duration);

private:
	std::deque<AnimationObject> queue;
};

template class AnimationAttribute<glm::vec4> ;
template class AnimationAttribute<Object> ;

using AnimationAttributeV4 = AnimationAttribute<glm::vec4>;
using AnimationAttributeO = AnimationAttribute<Object>;

#endif /* OPGLLIB_ANIMATOR_H_ */
