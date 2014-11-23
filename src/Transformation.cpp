/*
 * Transformation.cpp
 *
 *  Created on: 22.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Transformation.h>

using namespace gl;
using namespace std;

Transformation::Transformation() {
	transformationMatrix = glm::mat4(1.0f);
	handleInitialized = true;
	Transformation::matrices = new Matrices();
}

Transformation::Transformation(Matrices *matrices) {
	transformationMatrix = glm::mat4(1.0f);
	handleInitialized = false;
	Transformation::matrices = matrices;
}

Transformation::~Transformation() {
	if (handleInitialized) {
		deleteMatricesHandle();
	}
}

void Transformation::setMatricesHandle(Matrices *newHandle) {
	if (handleInitialized) {
		deleteMatricesHandle();
	}
	matrices = newHandle;
}

Matrices *Transformation::getMatricesHandle() {
	return matrices;
}

void Transformation::deleteMatricesHandle() {
	handleInitialized = false;
	delete matrices;
}

void Transformation::setTransformationMatrix(glm::mat4 transformationMatrix) {
	Transformation::transformationMatrix = transformationMatrix;
}

void Transformation::resetTransformationMatrix() {
	transformationMatrix = glm::mat4(1.0f);
}

void Transformation::updateTransformationMatrix(MultiplicationOrder multiplicationOrder) {
	switch(multiplicationOrder) {
	case TRS:
		transformationMatrix = matrices->getScalingMatrix() * matrices->getRotationMatrix() * matrices->getTranslationMatrix();
		break;
	case TSR:
		transformationMatrix = matrices->getRotationMatrix() * matrices->getScalingMatrix() * matrices->getTranslationMatrix();
		break;
	case STR:
		transformationMatrix = matrices->getRotationMatrix() * matrices->getTranslationMatrix() * matrices->getScalingMatrix();
		break;
	case RTS:
		transformationMatrix = matrices->getScalingMatrix() * matrices->getTranslationMatrix() * matrices->getRotationMatrix();
		break;
	case RST:
		transformationMatrix = matrices->getTranslationMatrix() * matrices->getScalingMatrix() * matrices->getRotationMatrix();
		break;
	case SRT:
		transformationMatrix = matrices->getTranslationMatrix() * matrices->getRotationMatrix() * matrices->getScalingMatrix();
		break;
	default:
		cerr << "Wrong Multiplication-Order submitted: " << multiplicationOrder << endl;
		transformationMatrix = matrices->getTranslationMatrix() * matrices->getRotationMatrix() * matrices->getScalingMatrix();
	}
}

glm::mat4 Transformation::getTransformationMatrix(bool noPerspectiveTransform) {
	if (noPerspectiveTransform) {
		return transformationMatrix;
	}
	return matrices->getPerspectiveMatrix() * transformationMatrix;
}

void Transformation::pushMatrix() {
	matrixStack.push(transformationMatrix);
	matricesStack.push(*matrices);
}

void Transformation::popMatrix() {
	transformationMatrix = matrixStack.top();
	matrixStack.pop();
	*matrices = matricesStack.top();
	matricesStack.pop();
}

void Transformation::seekMatrix() {
	transformationMatrix = matrixStack.top();
	*matrices = matricesStack.top();
}

void Transformation::translate(glm::vec3 offset) {
	matrices->setTranslationMatrix(offset);
	transformationMatrix = matrices->getTranslationMatrix() * transformationMatrix;
}

void Transformation::translateX(GLfloat x) {
	matrices->setTranslationMatrixX(x);
	transformationMatrix = matrices->getTranslationMatrix() * transformationMatrix;
}

void Transformation::translateY(GLfloat y) {
	matrices->setTranslationMatrixY(y);
	transformationMatrix = matrices->getTranslationMatrix() * transformationMatrix;
}

void Transformation::translateZ(GLfloat z) {
	matrices->setTranslationMatrixZ(z);
	transformationMatrix = matrices->getTranslationMatrix() * transformationMatrix;
}

void Transformation::scale(glm::vec3 scale) {
	matrices->setScalingMatrix(scale);
	transformationMatrix = matrices->getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleX(GLfloat x) {
	matrices->setScalingMatrixX(x);
	transformationMatrix = matrices->getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleY(GLfloat y) {
	matrices->setScalingMatrixY(y);
	transformationMatrix = matrices->getScalingMatrix() * transformationMatrix;
}

void Transformation::scaleZ(GLfloat z) {
	matrices->setScalingMatrixZ(z);
	transformationMatrix = matrices->getScalingMatrix() * transformationMatrix;
}

void Transformation::rotate(glm::vec3 rotation) {
	matrices->setRotationMatrix(rotation);
	transformationMatrix = matrices->getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateX(GLfloat x) {
	matrices->setRotationMatrixX(x);
	transformationMatrix = matrices->getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateY(GLfloat y) {
	matrices->setRotationMatrixY(y);
	transformationMatrix = matrices->getRotationMatrix() * transformationMatrix;
}

void Transformation::rotateZ(GLfloat z) {
	matrices->setRotationMatrixZ(z);
	transformationMatrix = matrices->getRotationMatrix() * transformationMatrix;
}
