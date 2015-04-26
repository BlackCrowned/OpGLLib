/*
 * Transformation.cpp
 *
 *  Created on: 22.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Transformation.h>

using namespace std;

namespace OpGLLib {
Transformation::Transformation() :
		Matrices(), Camera(), Perspective() {
	transformationMatrix = glm::mat4(1.0f);
}

Transformation::~Transformation() {

}

void Transformation::setTransformationMatrix(glm::mat4 transformationMatrix) {
	Transformation::transformationMatrix = transformationMatrix;
}

void Transformation::resetTransformationMatrix() {
	transformationMatrix = glm::mat4(1.0f);
}

void Transformation::updateTransformationMatrix(MultiplicationOrder multiplicationOrder) {
	switch (multiplicationOrder) {
	case TRS:
		transformationMatrix = getScalingMatrix() * getRotationMatrix() * getTranslationMatrix();
		break;
	case TSR:
		transformationMatrix = getRotationMatrix() * getScalingMatrix() * getTranslationMatrix();
		break;
	case STR:
		transformationMatrix = getRotationMatrix() * getTranslationMatrix() * getScalingMatrix();
		break;
	case RTS:
		transformationMatrix = getScalingMatrix() * getTranslationMatrix() * getRotationMatrix();
		break;
	case RST:
		transformationMatrix = getTranslationMatrix() * getScalingMatrix() * getRotationMatrix();
		break;
	case SRT:
		transformationMatrix = getTranslationMatrix() * getRotationMatrix() * getScalingMatrix();
		break;
	default:
		cerr << "Wrong Multiplication-Order submitted: " << multiplicationOrder << endl;
		transformationMatrix = getTranslationMatrix() * getRotationMatrix() * getScalingMatrix();
	}
}

glm::mat4 Transformation::getTransformationMatrix(bool noCameraTransform, bool noPerspectiveTransform, bool noOrientationTransform) {
	if (noPerspectiveTransform && noCameraTransform && noOrientationTransform) {
		return transformationMatrix;
	} else if (noPerspectiveTransform && noCameraTransform) {
		return transformationMatrix * getOrientationMatrix();
	} else if (noPerspectiveTransform && noOrientationTransform) {
		return getCameraMatrix() * transformationMatrix;
	} else if (noCameraTransform && noOrientationTransform) {
		return getPerspectiveMatrix() * transformationMatrix;
	} else if (noPerspectiveTransform) {
		return getCameraMatrix() * transformationMatrix * getOrientationMatrix();
	} else if (noCameraTransform) {
		return getPerspectiveMatrix() * transformationMatrix * getOrientationMatrix();
	} else if (noOrientationTransform) {
		return getPerspectiveMatrix() * getCameraMatrix() * transformationMatrix;
	}
	return getPerspectiveMatrix() * getCameraMatrix() * transformationMatrix * getOrientationMatrix();
}

void Transformation::loadIdentityMatrix() {
	resetTransformationMatrix();
	resetTranslationMatrix();
	resetScalingMatrix();
	resetRotationMatrix();
	resetOrientationMatrix();
}

void Transformation::pushMatrix() {
	matrixStack.push(transformationMatrix);
	Matrices::pushState();
}

void Transformation::popMatrix() {
	transformationMatrix = matrixStack.top();
	matrixStack.pop();
	Matrices::popState();
}

void Transformation::seekMatrix() {
	transformationMatrix = matrixStack.top();
	Matrices::seekState();
}

void Transformation::pushCamera() {
	Camera::pushState();
}

void Transformation::popCamera() {
	Camera::popState();
}

void Transformation::seekCamera() {
	Camera::seekState();
}

void Transformation::pushPerspective() {
	Perspective::pushState();
}

void Transformation::popPerspective() {
	Perspective::popState();
}

void Transformation::seekPerpective() {
	Perspective::seekState();
}

void Transformation::translate(glm::vec3 offset) {
	setTranslationMatrix(offset);
	transformationMatrix = getTranslationMatrix() * transformationMatrix;
}

void Transformation::translateX(float x) {
	resetTranslationMatrix();
	setTranslationMatrixX(x);
	transformationMatrix = getTranslationMatrix() * transformationMatrix;
}

void Transformation::translateY(float y) {
	resetTranslationMatrix();
	setTranslationMatrixY(y);
	transformationMatrix = getTranslationMatrix() * transformationMatrix;
}

void Transformation::translateZ(float z) {
	resetTranslationMatrix();
	setTranslationMatrixZ(z);
	transformationMatrix = getTranslationMatrix() * transformationMatrix;
}

void Transformation::scale(glm::vec3 scale) {
	setScalingMatrix(scale);
	transformationMatrix = getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleX(float x) {
	setScalingMatrixX(x);
	transformationMatrix = getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleY(float y) {
	setScalingMatrixY(y);
	transformationMatrix = getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleZ(float z) {
	setScalingMatrixZ(z);
	transformationMatrix = getScalingMatrix() * transformationMatrix;
}

void Transformation::rotate(glm::vec3 rotation) {
	setRotationMatrix(rotation);
	transformationMatrix = getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateX(float x) {
	setRotationMatrixX(x);
	transformationMatrix = getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateY(float y) {
	setRotationMatrixY(y);
	transformationMatrix = getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateZ(float z) {
	setRotationMatrixZ(z);
	transformationMatrix = getRotationMatrix() * transformationMatrix;
}

void Transformation::orient(glm::vec3 orientation) {
	orient(orientation.x, orientation.y, orientation.z);
}

void Transformation::orient(float yaw, float pitch, float roll) {
	multOrientationMatrix(yaw, pitch, roll);
}

void Transformation::yaw(float yaw) {
	multOrientationMatrixYaw(yaw);
}

void Transformation::pitch(float pitch) {
	multOrientationMatrixPitch(pitch);
}

void Transformation::roll(float roll) {
	multOrientationMatrixRoll(roll);
}

void Transformation::multMatrix(glm::mat4 matrix) {
	transformationMatrix = matrix * transformationMatrix;
}
}

