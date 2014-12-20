/*
 * Animator.cpp
 *
 *  Created on: 18.12.2014
 *      Author: Michael
 */

#include <OpGLLib/Animator.h>

using namespace std;

//template <class T, AnimationAttributeTypes attributeType>
//AnimationAttribute<T, attributeType>::AnimationAttribute() {
//
//}

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

}

AnimationObject::~AnimationObject() {

}

void AnimationObject::addUniformAttribute(AnimationAttribute<glm::vec4> attribute, AnimationAttributeTarget target, float progressStart, float progressEnd) {
	uniformAttributes.push_back(move(attribute));
	attributes.push_back(make_tuple(attribute.getType(), uniformAttributes.size() - 1, target, progressStart, progressEnd));
}

void AnimationObject::addUniformAttribute(string attribute, AnimationAttributeTypes type, AnimationAttributeTarget target, float progressStart, float progressEnd) {
	AnimationAttribute<glm::vec4> attr;

	if (type == translate || type == translateTo) {
		if (attribute == "hide") {
			//TODO: Store old value:

			attr.setAttribute(glm::vec4(0, 0, 0, 0), translateTo, a);
		}
		else if (attribute == "show") {
			//TODO: Restore old value:
		}

	}
	else if(type == scale || type == scaleTo) {
		if (attribute == "hide") {
			attr.setAttribute(glm::vec4(0, 0, 0, 1), scaleTo, x | y | z);
		}
		else if (attribute == "show") {
			//TODO: restore
		}

	}
	else if(type == rotate || type == rotateTo) {
		cerr << "Illegal type specified: " << type << endl;
	}

}

void AnimationObject::addPerVertexAttribute(AnimationAttribute<Object> attribute, AnimationAttributeTarget target, float progressStart, float progressEnd) {
	perVertexAttributes.push_back(move(attribute));
	attributes.push_back(make_tuple(attribute.getType(), perVertexAttributes.size() - 1, target, progressStart, progressEnd));
}

void AnimationObject::setStartTime(chrono::time_point<chrono::system_clock> start) {
	AnimationObject::start = start;
}

void AnimationObject::setDuration(chrono::milliseconds duration) {
	AnimationObject::duration = duration;
}

Animator::Animator() {

}

Animator::~Animator() {

}
