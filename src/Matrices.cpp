/*
 * Matrices.cpp
 *
 *  Created on: 19.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Matrices.h>

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

void Matrices::resetTranslationMatrix() {
	offset = glm::vec3(0, 0, 0);
	translationMatrix = glm::mat4(1.0f);
}

void Matrices::setTranslationMatrixX(float x) {
	offset.x = x;
	translationMatrix[3].x = x;
}

void Matrices::setTranslationMatrixY(float y) {
	offset.y = y;
	translationMatrix[3].y = y;
}

void Matrices::setTranslationMatrixZ(float z) {
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

void Matrices::resetScalingMatrix() {
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	scalingMatrix = glm::mat4(1.0f);
}

void Matrices::setScalingMatrixX(float x) {
	scale.x = x;
	scalingMatrix[0].x = x;
}

void Matrices::setScalingMatrixY(float y) {
	scale.y = y;
	scalingMatrix[1].y = y;
}

void Matrices::setScalingMatrixZ(float z) {
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

void Matrices::resetRotationMatrix() {
	rotation = glm::vec3(0, 0, 0);
	rotationMatrix = glm::mat4(1.0f);
}

void Matrices::setRotationMatrixX(float x) {
	rotation.x = x;
	setRotationXMatrix(x);
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::setRotationMatrixY(float y) {
	rotation.y = y;
	setRotationYMatrix(y);
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::setRotationMatrixZ(float z) {
	rotation.z = z;
	setRotationZMatrix(z);
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::updateRotationMatrix() {
	rotationMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix;
}

void Matrices::setRotationXMatrix(float x) {
	rotationXMatrix = glm::mat4(1.0f);
	rotation.x = x;
	rotationXMatrix[1].y = cos(x);
	rotationXMatrix[2].y = -sin(x);
	rotationXMatrix[1].z = sin(x);
	rotationXMatrix[2].z = cos(x);
}

void Matrices::setRotationYMatrix(float y) {
	rotationYMatrix = glm::mat4(1.0f);
	rotation.y = y;
	rotationYMatrix[0].x = cos(y);
	rotationYMatrix[2].x = sin(y);
	rotationYMatrix[0].z = -sin(y);
	rotationYMatrix[2].z = cos(y);
}

void Matrices::setRotationZMatrix(float z) {
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

void Matrices::setOrientationMatrix(glm::vec3 axis, float rotation) {
	axis = axis * glm::sin(rotation / 2.0f);
	float scalar = glm::cos(rotation / 2.0f);
	glm::quat offset(scalar, axis);
	orientationQuat = glm::normalize(offset);
}

void Matrices::setOrientationMatrix(float yaw, float pitch, float roll) {
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

void Matrices::multOrientationMatrix(glm::vec3 axis, float rotation) {
	//orientationQuat = orientationQuat * glm::quat(glm::cos(rotation / 2), glm::normalize(axis) * glm::sin(rotation / 2));
	axis = axis * glm::sin(rotation / 2.0f);
	float scalar = glm::cos(rotation / 2.0f);
	glm::quat offset(scalar, axis);
	orientationQuat = orientationQuat * offset;
	orientationQuat = glm::normalize(orientationQuat);
}

void Matrices::multOrientationMatrix(float yaw, float pitch, float roll) {
	multOrientationMatrixYaw(yaw);
	multOrientationMatrixPitch(pitch);
	multOrientationMatrixRoll(roll);
}

void Matrices::setOrientationMatrixYaw(float yaw) {
	setOrientationYawMatrix(yaw);
	orientationQuat = yawQuat;
}

void Matrices::setOrientationMatrixPitch(float pitch) {
	setOrientationPitchMatrix(pitch);
	orientationQuat = pitchQuat;
}

void Matrices::setOrientationMatrixRoll(float roll) {
	setOrientationRollMatrix(roll);
	orientationQuat = rollQuat;
}

void Matrices::multOrientationMatrixYaw(float yaw) {
	setOrientationYawMatrix(yaw);
	orientationQuat = glm::normalize(orientationQuat * yawQuat);
}

void Matrices::multOrientationMatrixPitch(float pitch) {
	setOrientationPitchMatrix(pitch);
	orientationQuat = glm::normalize(orientationQuat * pitchQuat);
}

void Matrices::multOrientationMatrixRoll(float roll) {
	setOrientationRollMatrix(roll);
	orientationQuat = glm::normalize(orientationQuat * rollQuat);
}

void Matrices::setOrientationYawMatrix(float yaw) {
	yawQuat = glm::normalize(glm::quat(glm::cos(yaw / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f) * glm::sin(yaw / 2.0f)));
}

void Matrices::setOrientationPitchMatrix(float pitch) {
	pitchQuat = glm::normalize(glm::quat(glm::cos(pitch / 2.0f), glm::vec3(0.0f, 1.0f, 0.0f) * glm::sin(pitch / 2.0f)));
}

void Matrices::setOrientationRollMatrix(float roll) {
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
