/*
 * Matrices.cpp
 *
 *  Created on: 19.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Matrices.h>

using namespace gl;

Matrices::Matrices() {
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

void Matrices::setOrientationMatrix(glm::mat4 orientationMatrix) {
	Matrices::orientationQuat = glm::quat_cast(orientationMatrix);
}

void Matrices::setOrientationMatrix(glm::mat3 axes, glm::vec3 rotations) {
	setOrientationMatrix(axes[0], rotations.x);
	multOrientationMatrix(axes[1], rotations.y);
	multOrientationMatrix(axes[2], rotations.z);
}

void Matrices::setOrientationMatrix(glm::vec3 axis, GLfloat rotation) {
	axis = axis * glm::sin(rotation / 2.0f);
	float scalar = glm::cos(rotation / 2.0f);
	glm::quat offset(scalar, axis);
	orientationQuat = glm::normalize(offset);
}

void Matrices::setOrientationMatrix(GLfloat yaw, GLfloat pitch, GLfloat roll) {
	setOrientationMatrixYaw(yaw);
	multOrientationMatrixPitch(pitch);
	multOrientationMatrixRoll(roll);
}

void Matrices::resetOrientationMatrix() {
	setOrientationMatrix(0, 0, 0);
}

void Matrices::multOrientationMatrix(glm::mat3 axes, glm::vec3 rotations) {
	multOrientationMatrix(axes[0], rotations.x);
	multOrientationMatrix(axes[1], rotations.y);
	multOrientationMatrix(axes[2], rotations.z);
}

void Matrices::multOrientationMatrix(glm::vec3 axis, GLfloat rotation) {
	//orientationQuat = orientationQuat * glm::quat(glm::cos(rotation / 2), glm::normalize(axis) * glm::sin(rotation / 2));
	axis = axis * glm::sin(rotation / 2.0f);
	float scalar = glm::cos(rotation / 2.0f);
	glm::quat offset(scalar, axis);
	orientationQuat = orientationQuat * offset;
	orientationQuat = glm::normalize(orientationQuat);
}

void Matrices::multOrientationMatrix(gl::GLfloat yaw, gl::GLfloat pitch, gl::GLfloat roll) {
	multOrientationMatrixYaw(yaw);
	multOrientationMatrixPitch(pitch);
	multOrientationMatrixRoll(roll);
}

void Matrices::setOrientationMatrixYaw(GLfloat yaw) {
	setOrientationYawMatrix(yaw);
	orientationQuat = yawQuat;
}

void Matrices::setOrientationMatrixPitch(GLfloat pitch) {
	setOrientationPitchMatrix(pitch);
	orientationQuat = pitchQuat;
}

void Matrices::setOrientationMatrixRoll(GLfloat roll) {
	setOrientationRollMatrix(roll);
	orientationQuat = rollQuat;
}

void Matrices::multOrientationMatrixYaw(GLfloat yaw) {
	setOrientationYawMatrix(yaw);
	orientationQuat = glm::normalize(orientationQuat * yawQuat);
}

void Matrices::multOrientationMatrixPitch(GLfloat pitch) {
	setOrientationPitchMatrix(pitch);
	orientationQuat = glm::normalize(orientationQuat * pitchQuat);
}

void Matrices::multOrientationMatrixRoll(GLfloat roll) {
	setOrientationRollMatrix(roll);
	orientationQuat = glm::normalize(orientationQuat * rollQuat);
}

void Matrices::setOrientationYawMatrix(GLfloat yaw) {
	yawQuat = glm::normalize(glm::quat(glm::cos(yaw / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f) * glm::sin(yaw / 2.0f)));
}

void Matrices::setOrientationPitchMatrix(GLfloat pitch) {
	pitchQuat = glm::normalize(glm::quat(glm::cos(pitch / 2.0f), glm::vec3(0.0f, 1.0f, 0.0f) * glm::sin(pitch / 2.0f)));
}

void Matrices::setOrientationRollMatrix(GLfloat roll) {
	rollQuat = glm::normalize(glm::quat(glm::cos(roll / 2.0f), glm::vec3(0.0f, 0.0f, -1.0f) * glm::sin(roll / 2.0f)));
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

const glm::mat4& Matrices::getOrientationMatrix() {
	orientationMatrix = glm::mat4_cast(orientationQuat);
	return orientationMatrix;
}

const glm::mat4 &Matrices::getYawMatrix() {
	yawMatrix = glm::mat4_cast(yawQuat);
	return yawMatrix;
}

const glm::mat4 &Matrices::getPitchMatrix() {
	pitchMatrix = glm::mat4_cast(pitchQuat);
	return pitchMatrix;
}

const glm::mat4 &Matrices::getRollMatrix() {
	rollMatrix = glm::mat4_cast(rollQuat);
	return rollMatrix;
}

void Matrices::pushState() {
	stateStack.push(*this);
}

void Matrices::popState() {
	Matrices tmp = stateStack.top();
	stateStack.pop();
	*this = tmp;
}

void Matrices::seekState() {
	Matrices tmp = stateStack.top();
	tmp.stateStack = stateStack;
	*this = tmp;
}
