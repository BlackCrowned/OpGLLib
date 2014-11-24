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
	handleInitialized[MATRICES] = handleInitialized[PERSPECTIVE] = handleInitialized[CAMERA] = true;
	matrices = new Matrices();
	perspective = new Perspective();
	camera = new Camera();
}

Transformation::Transformation(Matrices *matrices, Perspective *perspective, Camera *camera) {
	transformationMatrix = glm::mat4(1.0f);
	handleInitialized[MATRICES] = handleInitialized[PERSPECTIVE] = handleInitialized[CAMERA] = false;
	Transformation::matrices = matrices;
	Transformation::perspective = perspective;
	Transformation::camera = camera;
}

Transformation::~Transformation() {
	if (handleInitialized[MATRICES]) {
		deleteHandle(MATRICES);
	}
	if (handleInitialized[PERSPECTIVE]) {
		deleteHandle(PERSPECTIVE);
	}
	if (handleInitialized[CAMERA]) {
		deleteHandle(CAMERA);
	}
}

void Transformation::setHandle(Matrices *newHandle) {
	if (handleInitialized[MATRICES]) {
		deleteHandle(MATRICES);
	}
	matrices = newHandle;
}

void Transformation::setHandle(Perspective *newHandle) {
	if (handleInitialized[PERSPECTIVE]) {
		deleteHandle(PERSPECTIVE);
	}
	perspective = newHandle;
}

void Transformation::setHandle(Camera *newHandle) {
	if (handleInitialized[CAMERA]) {
		deleteHandle(CAMERA);
	}
	camera = newHandle;
}

void *Transformation::getHandle(HandleType handleType) {
	switch (handleType) {
	case MATRICES:
		return matrices;
	case PERSPECTIVE:
		return perspective;
	case CAMERA:
		return camera;
	default:
		cerr << "HandleType: " << handleType << " not defined!" << endl;
		return NULL;
	}
}

void Transformation::deleteHandle(HandleType handleType) {
	switch (handleType) {
	case MATRICES:
		handleInitialized[MATRICES] = false;
		delete matrices;
		break;
	case PERSPECTIVE:
		handleInitialized[PERSPECTIVE] = false;
		delete perspective;
		break;
	case CAMERA:
		handleInitialized[CAMERA] = false;
		delete camera;
		break;
	default:
		cerr << "HandleType: " << handleType << " not defined!";
	}
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
	return perspective->getPerspectiveMatrix() * transformationMatrix;
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
