/*
 * Transformation.cpp
 *
 *  Created on: 22.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Transformation.h>

using namespace gl;
using namespace std;

Transformation::Transformation() : Matrices(){
	transformationMatrix = glm::mat4(1.0f);
	handleInitialized[PERSPECTIVE] = handleInitialized[CAMERA] = true;
	perspective = new Perspective();
	camera = new Camera();
}

Transformation::Transformation(Perspective *perspective, Camera *camera) : Matrices(){
	transformationMatrix = glm::mat4(1.0f);
	handleInitialized[PERSPECTIVE] = handleInitialized[CAMERA] = false;
	Transformation::perspective = perspective;
	Transformation::camera = camera;
}

Transformation::~Transformation() {
	if (handleInitialized[PERSPECTIVE]) {
		deleteHandle(PERSPECTIVE);
	}
	if (handleInitialized[CAMERA]) {
		deleteHandle(CAMERA);
	}
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

glm::mat4 Transformation::getTransformationMatrix(bool noPerspectiveTransform) {
	if (noPerspectiveTransform) {
		return transformationMatrix;
	}
	return perspective->getPerspectiveMatrix() * transformationMatrix;
}

void Transformation::pushMatrix() {
	matrixStack.push(transformationMatrix);
	pushState();
}

void Transformation::popMatrix() {
	transformationMatrix = matrixStack.top();
	matrixStack.pop();
	popState();
}

void Transformation::seekMatrix() {
	transformationMatrix = matrixStack.top();
	seekState();
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

void Transformation::addMatrix(glm::mat4 matrix) {
	transformationMatrix = matrix * transformationMatrix;
}
