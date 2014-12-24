/*
 * Animator.cpp
 *
 *  Created on: 18.12.2014
 *      Author: Michael
 */

#include <OpGLLib/Animator.h>

using namespace std;

void detail::addCallback(Animator*& animator, glm::mat4*& matrix, AnimationObject& animationObject) {
	animator->animate(matrix, animationObject);
}

template<class T>
AnimationAttribute<T>::AnimationAttribute() {
	type = translate;
	interpolator = acceleratedecelerate;
	progressStart = 0.0f;
	progressEnd = 1.0f;
}

template<class T>
AnimationAttribute<T>::AnimationAttribute(T attribute, AnimationAttributeTypes type, InterpolationFunctions interpolator,
		float progressStart, float progressEnd) {
	setAttribute(attribute, type, interpolator, progressStart, progressEnd);
}

template<class T>
AnimationAttribute<T>::~AnimationAttribute() {

}

template<class T>
void AnimationAttribute<T>::setAttribute(T attribute, AnimationAttributeTypes type, InterpolationFunctions interpolator,
		float progressStart, float progressEnd) {
	AnimationAttribute::attribute = attribute;
	AnimationAttribute::type = type;
	AnimationAttribute::interpolator = interpolator;
	AnimationAttribute::progressStart = progressStart;
	AnimationAttribute::progressEnd = progressEnd;
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
InterpolationFunctions AnimationAttribute<T>::getInterpolator() {
	return interpolator;
}

template<class T>
float AnimationAttribute<T>::getProgressStart() {
	return progressStart;
}

template<class T>
float AnimationAttribute<T>::getProgressEnd() {
	return progressEnd;
}

template<class T>
void AnimationAttribute<T>::reverse() {
	if (type != scale) {
		attribute = -attribute;
	} else {
		attribute = 1.0f / attribute;
	}

	switch (interpolator) {
	case accelerate:
		interpolator = decelerate;
		break;
	case decelerate:
		interpolator = accelerate;
		break;
	default:
		break;
	}
	float oldProgressStart = progressStart;
	progressStart = 1.0f - progressEnd;
	progressEnd = 1.0f - oldProgressStart;
}

AnimationObject::AnimationObject() {
	matrix = nullptr;
	animator = nullptr;
	settings = 0;
	reversed = 0;
	duration = chrono::milliseconds(1000);
	delay = chrono::milliseconds(0);
}

AnimationObject::AnimationObject(initializer_list<AnimationAttribute<glm::vec3> > attributes) {
	matrix = nullptr;
	animator = nullptr;
	settings = 0;
	duration = chrono::milliseconds(1000);
	delay = chrono::milliseconds(0);
	AnimationObject::attributes = attributes;
}

AnimationObject::~AnimationObject() {

}

void AnimationObject::addAttribute(AnimationAttribute<glm::vec3> attribute) {
	attributes.push_back(attribute);
}

void AnimationObject::setStartTime() {
	setStartTime(chrono::system_clock::now());
}

void AnimationObject::setStartTime(chrono::time_point<chrono::system_clock> start) {
	AnimationObject::start = start;
	AnimationObject::lastTick = start;
}

void AnimationObject::setDuration(chrono::milliseconds duration) {
	AnimationObject::duration = duration;
}

void AnimationObject::setDuration(int milliseconds) {
	setDuration(chrono::milliseconds(milliseconds));
}

void AnimationObject::setDelay(chrono::milliseconds delay) {
	AnimationObject::delay = delay;
}

void AnimationObject::setDelay(int milliseconds) {
	setDelay(chrono::milliseconds(milliseconds));
}

void AnimationObject::setMatrix(glm::mat4* matrix) {
	AnimationObject::matrix = matrix;
	AnimationObject::oldMatrix = *matrix;
}

void AnimationObject::setAnimator(Animator* animator) {
	AnimationObject::animator = animator;
}

void AnimationObject::setSettings(int settings) {
	AnimationObject::settings = settings;
}

void AnimationObject::reverse() {
	AnimationObject::oldMatrix = *matrix;
	for (unsigned int i = 0; i < attributes.size(); i++) {
		AnimationAttribute<glm::vec3> attribute = attributes.at(attributes.size() - 1);
		attribute.reverse();
		attributes.insert(attributes.begin() + i, attribute);
		attributes.pop_back();
	}
	reversed ^= 1;
}

void AnimationObject::animationStart() {
	callbacks.dispatchEvent(AnimationCallbackEvents::onStart);
}

void AnimationObject::animationUpdate() {
	callbacks.dispatchEvent(AnimationCallbackEvents::onUpdate);
}

void AnimationObject::animationComplete() {
	callbacks.dispatchEvent(AnimationCallbackEvents::onComplete);
	if (AnimationSettings::restart & settings) {
		callbacks.dispatchEvent(AnimationCallbackEvents::onRestart);
		setStartTime();
	}
	if (AnimationSettings::reverse & settings) {
		reverse();
		callbacks.dispatchEvent(AnimationCallbackEvents::onReverse);
		setStartTime();
	}
	if (AnimationSettings::repeat & settings) {
		callbacks.dispatchEvent(AnimationCallbackEvents::onRepeat);
		setMatrix(matrix);
		setStartTime();
	}
	if (AnimationSettings::restartOnce & settings) {
		callbacks.dispatchEvent(AnimationCallbackEvents::onRestart);
		callbacks.removeCallbacks(AnimationCallbackEvents::onRestart);
		settings ^= AnimationSettings::restartOnce;
		setStartTime();
	}
	if (AnimationSettings::reverseOnce & settings) {
		reverse();
		callbacks.dispatchEvent(AnimationCallbackEvents::onReverse);
		callbacks.removeCallbacks(AnimationCallbackEvents::onReverse);
		settings ^= AnimationSettings::reverseOnce;
		setStartTime();
	}
	if (AnimationSettings::repeatOnce & settings) {
		callbacks.dispatchEvent(AnimationCallbackEvents::onRepeat);
		callbacks.removeCallbacks(AnimationCallbackEvents::onRepeat);
		settings ^= AnimationSettings::repeatOnce;
		setMatrix(matrix);
		setStartTime();
	}
}

bool AnimationObject::complete() {
	if (lastTick.time_since_epoch() - start.time_since_epoch() >= duration + delay) {
		return true;
	}
	return false;
}

Animator::Animator() {

}

Animator::~Animator() {

}

void Animator::animate(glm::mat4* matrix, AnimationObject&& animationObject) {
	animationObject.setAnimator(this);
	animationObject.setMatrix(matrix);
	animationObject.setStartTime();

	queue[matrix].push_back(forward<AnimationObject>(animationObject));
}

void Animator::animate(glm::mat4* matrix, AnimationObject& animationObject) {
	animationObject.setAnimator(this);
	animationObject.setMatrix(matrix);
	animationObject.setStartTime();

	queue[matrix].push_back(animationObject);
}

glm::mat4* Animator::animate(AnimationObject&& animationObject) {
	glm::mat4* matrix = new glm::mat4(1.0f);

	animate(matrix, forward<AnimationObject>(animationObject));

	return matrix;
}

glm::mat4* Animator::animate(AnimationObject& animationObject) {
	glm::mat4* matrix = new glm::mat4(1.0f);

	animate(matrix, forward<AnimationObject>(animationObject));

	return matrix;
}

void Animator::stop(glm::mat4* matrix, bool stopAll, bool finish) {
	if (queue.count(matrix) < 1) {
		return;
	}
	if (stopAll && finish) {
		for (unsigned int i = 0; i < queue.at(matrix).size(); i++) {
			queue.at(matrix).at(i).setDuration(chrono::milliseconds(1));
			queue.at(matrix).at(i).setDelay(chrono::milliseconds(0));
			if (((queue.at(matrix).at(i).settings & AnimationSettings::reverse)
					|| (queue.at(matrix).at(i).settings & AnimationSettings::reverseOnce)) && !queue.at(matrix).at(i).reversed) {
				queue.at(matrix).at(i).setSettings(AnimationSettings::reverseOnce);
			} else {
				queue.at(matrix).at(i).setSettings(0);
			}
		}
	} else if (stopAll && !finish) {
		queue.at(matrix).clear();
	} else if (!stopAll && finish) {
		if (queue.at(matrix).size() >= 1) {
			queue.at(matrix).at(0).setDuration(chrono::milliseconds(1));
			queue.at(matrix).at(0).setDelay(chrono::milliseconds(0));
			if (((queue.at(matrix).at(0).settings & AnimationSettings::reverse)
					|| (queue.at(matrix).at(0).settings & AnimationSettings::reverseOnce)) && !queue.at(matrix).at(0).reversed) {
				queue.at(matrix).at(0).setSettings(AnimationSettings::reverseOnce);
			} else {
				queue.at(matrix).at(0).setSettings(0);
			}
		}
	} else if (!stopAll && !finish) {
		if (queue.at(matrix).size() >= 1) {
			queue.at(matrix).pop_front();
		}
	}
}

void Animator::update() {
	for (auto i = queue.begin(); i != queue.end(); i++) {
		glm::mat4* matrix = i->first;
		if (queue.at(matrix).size() > 0) {
			AnimationObject& animationObject = queue.at(matrix).at(0);
			animationObject.animationStart();
			animationObject.lastTick = chrono::system_clock::now();
			Transformation::loadIdentityMatrix();
			Transformation::setTransformationMatrix(animationObject.oldMatrix);
			animationObject.animationUpdate();
			for (unsigned int a = 0; a < animationObject.attributes.size(); a++) {
				AnimationAttribute<glm::vec3>& attr = animationObject.attributes.at(a);
				float progress = interpolate(animationObject.start, animationObject.duration, animationObject.delay, attr.getInterpolator(),
						attr.getProgressStart(), attr.getProgressEnd());

				switch (attr.getType()) {
				case AnimationAttributeTypes::translate:
					translate(matrix, attr, progress);
					break;
				case AnimationAttributeTypes::scale:
					scale(matrix, attr, progress);
					break;
				case AnimationAttributeTypes::rotate:
					rotate(matrix, attr, progress);
					break;
				case AnimationAttributeTypes::orient:
					orient(matrix, attr, progress);
					break;
				default:
					cerr << "Unknown AnimationAttributeType: " << attr.getType() << "!" << endl;
				}
			}
			if (animationObject.complete()) {
				animationObject.animationComplete();
				if (animationObject.complete()) {
					queue.at(matrix).pop_front();
				}
			}
		}

	}
}

void Animator::translate(glm::mat4* matrix, AnimationAttribute<glm::vec3>& attribute, float progress) {
	Transformation::translate(attribute.getAttribute() * progress);
	*matrix = Transformation::getTransformationMatrix(1, 1, 0);
}

void Animator::scale(glm::mat4* matrix, AnimationAttribute<glm::vec3>& attribute, float progress) {
	Transformation::scale(attribute.getAttribute() * progress + glm::vec3(1, 1, 1) * (1.0f - progress));
	*matrix = Transformation::getTransformationMatrix(1, 1, 0);
}

void Animator::rotate(glm::mat4* matrix, AnimationAttribute<glm::vec3>& attribute, float progress) {
	Transformation::rotate(attribute.getAttribute() * progress);
	*matrix = Transformation::getTransformationMatrix(1, 1, 0);
}

void Animator::orient(glm::mat4* matrix, AnimationAttribute<glm::vec3>& attribute, float progress) {
	Transformation::orient(attribute.getAttribute() * progress);
	*matrix = Transformation::getTransformationMatrix(1, 1, 0);
}

float Animator::interpolate(chrono::time_point<chrono::system_clock> startTime, chrono::milliseconds duration, chrono::milliseconds delay,
		InterpolationFunctions interpolator, float start, float end) {

	chrono::milliseconds timePassed = chrono::duration_cast<chrono::milliseconds>(
			chrono::system_clock::now().time_since_epoch() - startTime.time_since_epoch()) - delay;

	float progress = static_cast<float>(timePassed.count()) / static_cast<float>(duration.count());
	float scaledProgress = 0.0f;
	float interpolatedProgress = 0.0f;

	if (progress > 1.0f) {
		progress = 1.0f;
	}

	if (progress <= start) {
		scaledProgress = 0.0f;
	} else if ((progress > start) && (progress < end)) {
		scaledProgress = (progress - start) / (end - start);
	} else if (progress >= end) {
		scaledProgress = 1.0f;
	}

	switch (interpolator) {
	case InterpolationFunctions::linear:
		interpolatedProgress = scaledProgress;
		break;
	case InterpolationFunctions::decelerate:
		interpolatedProgress = sinf(scaledProgress * glm::pi<float>() / 2.0f);
		break;
	case InterpolationFunctions::accelerate:
		interpolatedProgress = 1.0f - cosf((scaledProgress) * glm::pi<float>() / 2.0f);
		break;
	case InterpolationFunctions::acceleratedecelerate:
		interpolatedProgress = sinf(scaledProgress * glm::pi<float>() / 2.0f) * sinf(scaledProgress * glm::pi<float>() / 2.0f);
		break;
	default:
		cerr << "Unknown interpolator: " << interpolator << endl;
	}

	return interpolatedProgress;
}
