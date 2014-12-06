/*
 * Transformation.cpp
 *
 *  Created on: 22.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Transformation.h>

using namespace gl;
using namespace std;

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

glm::mat4 Transformation::getTransformationMatrix(bool noCameraTransform, bool noPerspectiveTransform) {
	if (noPerspectiveTransform && noCameraTransform) {
		return transformationMatrix;
	} else if (noPerspectiveTransform) {
		return getCameraMatrix() * transformationMatrix * getOrientationMatrix();
	} else if (noCameraTransform) {
		return getPerspectiveMatrix() * transformationMatrix * getOrientationMatrix();
	}
	return getPerspectiveMatrix() * getCameraMatrix() * transformationMatrix * getOrientationMatrix();
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

void Transformation::translateX(GLfloat x) {
	setTranslationMatrixX(x);
	transformationMatrix = getTranslationMatrix() * transformationMatrix;
}

void Transformation::translateY(GLfloat y) {
	setTranslationMatrixY(y);
	transformationMatrix = getTranslationMatrix() * transformationMatrix;
}

void Transformation::translateZ(GLfloat z) {
	setTranslationMatrixZ(z);
	transformationMatrix = getTranslationMatrix() * transformationMatrix;
}

void Transformation::scale(glm::vec3 scale) {
	setScalingMatrix(scale);
	transformationMatrix = getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleX(GLfloat x) {
	setScalingMatrixX(x);
	transformationMatrix = getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleY(GLfloat y) {
	setScalingMatrixY(y);
	transformationMatrix = getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleZ(GLfloat z) {
	setScalingMatrixZ(z);
	transformationMatrix = getScalingMatrix() * transformationMatrix;
}

void Transformation::rotate(glm::vec3 rotation) {
	setRotationMatrix(rotation);
	transformationMatrix = getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateX(GLfloat x) {
	setRotationMatrixX(x);
	transformationMatrix = getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateY(GLfloat y) {
	setRotationMatrixY(y);
	transformationMatrix = getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateZ(GLfloat z) {
	setRotationMatrixZ(z);
	transformationMatrix = getRotationMatrix() * transformationMatrix;
}

void Transformation::orient(GLfloat yaw, GLfloat pitch, GLfloat roll) {
	multOrientationMatrix(yaw, pitch, roll);
}

void Transformation::yaw(GLfloat yaw) {
	multOrientationMatrixYaw(yaw);
}

void Transformation::pitch(GLfloat pitch) {
	multOrientationMatrixPitch(pitch);
}

void Transformation::roll(GLfloat roll) {
	multOrientationMatrixRoll(roll);
}

void Transformation::multMatrix(glm::mat4 matrix) {
	transformationMatrix = matrix * transformationMatrix;
}
