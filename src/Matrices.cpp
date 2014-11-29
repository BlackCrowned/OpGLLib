/*
 * Matrices.cpp
 *
 *  Created on: 19.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Matrices.h>

using namespace gl;

Matrices::Matrices() {
	translationMatrix = glm::mat4(1.0f);
	scalingMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	rotationXMatrix = glm::mat4(1.0f);
	rotationYMatrix = glm::mat4(1.0f);
	rotationZMatrix = glm::mat4(1.0f);

	offset = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

Matrices::~Matrices() {

}

void Matrices::setTranslationMatrix(glm::mat4 translationMatrix) {
	Matrices::translationMatrix = translationMatrix;
}

void Matrices::setTranslationMatrix(glm::vec3 offset) {
	Matrices::offset = offset;
	translationMatrix[3].x = offset.x;
	translationMatrix[3].y = offset.y;
	translationMatrix[3].z = offset.z;
}

void Matrices::setTranslationMatrixX(GLfloat x) {
	offset.x = x;
	translationMatrix[3].x = x;
}

void Matrices::setTranslationMatrixY(GLfloat y) {
	offset.y = y;
	translationMatrix[3].y = y;
}

void Matrices::setTranslationMatrixZ(GLfloat z) {
	offset.z = z;
	translationMatrix[3].z = z;
}

void Matrices::setScalingMatrix(glm::mat4 scalingMatrix) {
	Matrices::scalingMatrix = scalingMatrix;
}

void Matrices::setScalingMatrix(glm::vec3 scale) {
	Matrices::scale = scale;
	scalingMatrix[0].x = scale.x;
	scalingMatrix[1].y = scale.y;
	scalingMatrix[2].z = scale.z;
}

void Matrices::setScalingMatrixX(GLfloat x) {
	scale.x = x;
	scalingMatrix[0].x = x;
}

void Matrices::setScalingMatrixY(GLfloat y) {
	scale.y = y;
	scalingMatrix[1].y = y;
}

void Matrices::setScalingMatrixZ(GLfloat z) {
	scale.z = z;
	scalingMatrix[2].z = z;
}

void Matrices::setRotationMatrix(glm::mat4 rotationMatrix) {
	Matrices::rotationMatrix = rotationMatrix;
}

void Matrices::setRotationMatrix(glm::vec3 rotation) {
	Matrices::rotation = rotation;
	setRotationXMatrix(rotation.x);
	setRotationYMatrix(rotation.y);
	setRotationZMatrix(rotation.z);
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::setRotationMatrixX(GLfloat x) {
	rotation.x = x;
	setRotationXMatrix(x);
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::setRotationMatrixY(GLfloat y) {
	rotation.y = y;
	setRotationYMatrix(y);
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::setRotationMatrixZ(GLfloat z) {
	rotation.z = z;
	setRotationZMatrix(z);
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::updateRotationMatrix() {
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::setRotationXMatrix(GLfloat x) {
	rotationXMatrix = glm::mat4(1.0f);
	rotation.x = x;
	rotationXMatrix[1].y = cos(x);
	rotationXMatrix[2].y = -sin(x);
	rotationXMatrix[1].z = sin(x);
	rotationXMatrix[2].z = cos(x);
}

void Matrices::setRotationYMatrix(GLfloat y) {
	rotationYMatrix = glm::mat4(1.0f);
	rotation.y = y;
	rotationYMatrix[0].x = cos(y);
	rotationYMatrix[2].x = sin(y);
	rotationYMatrix[0].z = -sin(y);
	rotationYMatrix[2].z = cos(y);
}

void Matrices::setRotationZMatrix(GLfloat z) {
	rotationZMatrix = glm::mat4(1.0f);
	rotation.z = z;
	rotationZMatrix[0].x = cos(z);
	rotationZMatrix[1].x = -sin(z);
	rotationZMatrix[0].y = sin(z);
	rotationZMatrix[1].y = cos(z);
}

const glm::mat4& Matrices::getTranslationMatrix() {
	return translationMatrix;
}

const glm::mat4& Matrices::getScalingMatrix() {
	return scalingMatrix;
}

const glm::mat4& Matrices::getRotationMatrix() {
	return rotationMatrix;
}

void Matrices::pushState() {
	stateStack.push(*this);
}

void Matrices::popState() {
	Matrices tmp = stateStack.top();
	stateStack.pop();
	translationMatrix = tmp.translationMatrix;
	scalingMatrix = tmp.scalingMatrix;
	rotationMatrix = tmp.rotationMatrix;
	rotationXMatrix = tmp.rotationXMatrix;
	rotationYMatrix = tmp.rotationYMatrix;
	rotationZMatrix = tmp.rotationZMatrix;

	offset = tmp.offset;
	scale = tmp.scale;
	rotation = tmp.rotation;
}

void Matrices::seekState() {
	Matrices tmp = stateStack.top();
	translationMatrix = tmp.translationMatrix;
	scalingMatrix = tmp.scalingMatrix;
	rotationMatrix = tmp.rotationMatrix;
	rotationXMatrix = tmp.rotationXMatrix;
	rotationYMatrix = tmp.rotationYMatrix;
	rotationZMatrix = tmp.rotationZMatrix;

	offset = tmp.offset;
	scale = tmp.scale;
	rotation = tmp.rotation;
}
