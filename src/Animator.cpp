/*
 * Animator.cpp
 *
 *  Created on: 18.12.2014
 *      Author: Michael
 */

#include <OpGLLib/Animator.h>

using namespace std;

void _addCallback(Animator* animator, glm::mat4* modelMatrix, AnimationObject animationObject) {
	animator->animate(modelMatrix, animationObject);
}

template<class T>
AnimationAttribute<T>::AnimationAttribute() {
	type = translate;
	inclusion = all;
}

template<class T>
AnimationAttribute<T>::AnimationAttribute(T attribute, AnimationAttributeTypes type, int inclusion) {
	AnimationAttribute::attribute = attribute;
	AnimationAttribute::type = type;
	AnimationAttribute::inclusion = inclusion;
}

template<class T>
AnimationAttribute<T>::~AnimationAttribute() {

}

template<class T>
void AnimationAttribute<T>::setAttribute(T attribute, AnimationAttributeTypes type, int inclusion) {
	AnimationAttribute::attribute = attribute;
	AnimationAttribute::type = type;
	AnimationAttribute::inclusion = inclusion;
}

template<class T>
T const& AnimationAttribute<T>::getAttribute() {
	return attribute;
}

template<class T>
AnimationAttributeTypes AnimationAttribute<T>::getType() {
	return type;
}

template<class T>
int AnimationAttribute<T>::getInclusion() {
	return inclusion;
}

AnimationObject::AnimationObject() {
	modelMatrix = nullptr;
	animator = nullptr;
}

AnimationObject::~AnimationObject() {

}

void AnimationObject::addAttribute(AnimationAttribute<glm::vec4> attribute, float progressStart, float progressEnd) {
	attributes.push_back(make_tuple(attribute, progressStart, progressEnd));
}

void AnimationObject::addAttribute(string attribute, AnimationAttributeTypes type, float progressStart, float progressEnd) {
	AnimationAttribute<glm::vec4> attr;

	if (type == AnimationAttributeTypes::translate || type == AnimationAttributeTypes::translateTo) {
		if (attribute == "hide") {
			//TODO: Store old value:

			attr.setAttribute(glm::vec4(0, 0, 0, 0), translateTo, a);
		} else if (attribute == "show") {
			//TODO: Restore old value:
		}

	} else if (type == AnimationAttributeTypes::scale || type == AnimationAttributeTypes::scaleTo) {
		if (attribute == "hide") {
			attr.setAttribute(glm::vec4(0, 0, 0, 1), scaleTo, x | y | z);
		} else if (attribute == "show") {
			//TODO: restore
		}

	} else if (type == AnimationAttributeTypes::rotate || type == AnimationAttributeTypes::rotateTo) {
		cerr << "Illegal type specified: " << type << endl;
	}

}

void AnimationObject::setStartTime(chrono::time_point<chrono::system_clock> start) {
	AnimationObject::start = start;
}

void AnimationObject::setDuration(chrono::milliseconds duration) {
	AnimationObject::duration = duration;
}

void AnimationObject::setModelMatrix(glm::mat4* modelMatrix) {
	AnimationObject::modelMatrix = modelMatrix;
}

void AnimationObject::setAnimator(Animator* animator) {
	AnimationObject::animator = animator;
}

void AnimationObject::animationStart() {
	callbacks.dispatchEvent(AnimationCallbackEvents::start);
}

void AnimationObject::animationUpdate() {
	callbacks.dispatchEvent(AnimationCallbackEvents::update);
}

void AnimationObject::animationDone() {
	callbacks.dispatchEvent(AnimationCallbackEvents::done);
}

Animator::Animator() {

}

Animator::~Animator() {

}

void Animator::animate(glm::mat4* modelMatrix, AnimationObject animationObject) {
	animationObject.setAnimator(this);
	animationObject.setModelMatrix(modelMatrix);

	queue[modelMatrix].push_back(animationObject);
}

glm::mat4* Animator::animate(AnimationObject animationObject) {
	glm::mat4* modelMatrix = new glm::mat4();

	animationObject.setAnimator(this);
	animationObject.setModelMatrix(modelMatrix);

	queue[modelMatrix].push_back(animationObject);

	return modelMatrix;
}

void Animator::update() {
	for (auto i : queue) {
		for (auto j : i.second) {
			for (auto a : j.attributes) {
				AnimationAttribute<glm::vec4>& attribute = get<0>(a);
				float &start = get<1>(a);
				float &end = get<2>(a);

			}
		}
	}
}

void Animator::interpolate(chrono::time_point<chrono::system_clock> startTime, chrono::milliseconds duration, InterpolationFunctions interpolator,
		float start, float end) {
	//chrono::milliseconds timePassed = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch().count() - startTime.time_since_epoch().count());
}
