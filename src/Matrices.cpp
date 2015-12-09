/*
 * Matrices.cpp
 *
 *  Created on: 19.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Matrices.h>

namespace OpGLLib {
	namespace gl {

		void Matrices::setTranslationMatrix(glm::mat4 translationMatrix) {
			_data.translationMatrix = translationMatrix;
		}

		void Matrices::setTranslationMatrix(glm::vec3 offset) {
			_data.offset = offset;
			_data.translationMatrix[3].x = offset.x;
			_data.translationMatrix[3].y = offset.y;
			_data.translationMatrix[3].z = offset.z;
		}

		void Matrices::resetTranslationMatrix() {
			_data.offset = glm::vec3(0, 0, 0);
			_data.translationMatrix = glm::mat4(1.0f);
		}

		void Matrices::setTranslationMatrixX(float x) {
			_data.offset.x = x;
			_data.translationMatrix[3].x = x;
		}

		void Matrices::setTranslationMatrixY(float y) {
			_data.offset.y = y;
			_data.translationMatrix[3].y = y;
		}

		void Matrices::setTranslationMatrixZ(float z) {
			_data.offset.z = z;
			_data.translationMatrix[3].z = z;
		}

		void Matrices::setScalingMatrix(glm::mat4 scalingMatrix) {
			_data.scalingMatrix = scalingMatrix;
		}

		void Matrices::setScalingMatrix(glm::vec3 scale) {
			_data.scale = scale;
			_data.scalingMatrix[0].x = scale.x;
			_data.scalingMatrix[1].y = scale.y;
			_data.scalingMatrix[2].z = scale.z;
		}

		void Matrices::resetScalingMatrix() {
			_data.scale = glm::vec3(1.0f, 1.0f, 1.0f);
			_data.scalingMatrix = glm::mat4(1.0f);
		}

		void Matrices::setScalingMatrixX(float x) {
			_data.scale.x = x;
			_data.scalingMatrix[0].x = x;
		}

		void Matrices::setScalingMatrixY(float y) {
			_data.scale.y = y;
			_data.scalingMatrix[1].y = y;
		}

		void Matrices::setScalingMatrixZ(float z) {
			_data.scale.z = z;
			_data.scalingMatrix[2].z = z;
		}

		void Matrices::setRotationMatrix(glm::mat4 rotationMatrix) {
			_data.rotationMatrix = rotationMatrix;
		}

		void Matrices::setRotationMatrix(glm::vec3 rotation) {
			_data.rotation = rotation;
			setRotationXMatrix(rotation.x);
			setRotationYMatrix(rotation.y);
			setRotationZMatrix(rotation.z);
			_data.rotationMatrix = _data.rotationXMatrix * _data.rotationYMatrix * _data.rotationZMatrix;
		}

		void Matrices::resetRotationMatrix() {
			_data.rotation = glm::vec3(0, 0, 0);
			_data.rotationMatrix = glm::mat4(1.0f);
		}

		void Matrices::setRotationMatrixX(float x) {
			_data.rotation.x = x;
			setRotationXMatrix(x);
			_data.rotationMatrix = _data.rotationXMatrix * _data.rotationYMatrix * _data.rotationZMatrix;
		}

		void Matrices::setRotationMatrixY(float y) {
			_data.rotation.y = y;
			setRotationYMatrix(y);
			_data.rotationMatrix = _data.rotationXMatrix * _data.rotationYMatrix * _data.rotationZMatrix;
		}

		void Matrices::setRotationMatrixZ(float z) {
			_data.rotation.z = z;
			setRotationZMatrix(z);
			_data.rotationMatrix = _data.rotationXMatrix * _data.rotationYMatrix * _data.rotationZMatrix;
		}

		void Matrices::updateRotationMatrix() {
			_data.rotationMatrix = _data.rotationXMatrix * _data.rotationYMatrix * _data.rotationZMatrix;
		}

		void Matrices::setRotationXMatrix(float x) {
			_data.rotationXMatrix = glm::mat4(1.0f);
			_data.rotation.x = x;
			_data.rotationXMatrix[1].y = cos(x);
			_data.rotationXMatrix[2].y = -sin(x);
			_data.rotationXMatrix[1].z = sin(x);
			_data.rotationXMatrix[2].z = cos(x);
		}

		void Matrices::setRotationYMatrix(float y) {
			_data.rotationYMatrix = glm::mat4(1.0f);
			_data.rotation.y = y;
			_data.rotationYMatrix[0].x = cos(y);
			_data.rotationYMatrix[2].x = sin(y);
			_data.rotationYMatrix[0].z = -sin(y);
			_data.rotationYMatrix[2].z = cos(y);
		}

		void Matrices::setRotationZMatrix(float z) {
			_data.rotationZMatrix = glm::mat4(1.0f);
			_data.rotation.z = z;
			_data.rotationZMatrix[0].x = cos(z);
			_data.rotationZMatrix[1].x = -sin(z);
			_data.rotationZMatrix[0].y = sin(z);
			_data.rotationZMatrix[1].y = cos(z);
		}

		void Matrices::setOrientationMatrix(glm::mat4 orientationMatrix) {
			_data.orientationQuat = glm::quat_cast(orientationMatrix);
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
			_data.orientationQuat = glm::normalize(offset);
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
			_data.orientationQuat = _data.orientationQuat * offset;
			_data.orientationQuat = glm::normalize(_data.orientationQuat);
		}

		void Matrices::multOrientationMatrix(float yaw, float pitch, float roll) {
			multOrientationMatrixYaw(yaw);
			multOrientationMatrixPitch(pitch);
			multOrientationMatrixRoll(roll);
		}

		void Matrices::setOrientationMatrixYaw(float yaw) {
			setOrientationYawMatrix(yaw);
			_data.orientationQuat = _data.yawQuat;
		}

		void Matrices::setOrientationMatrixPitch(float pitch) {
			setOrientationPitchMatrix(pitch);
			_data.orientationQuat = _data.pitchQuat;
		}

		void Matrices::setOrientationMatrixRoll(float roll) {
			setOrientationRollMatrix(roll);
			_data.orientationQuat = _data.rollQuat;
		}

		void Matrices::multOrientationMatrixYaw(float yaw) {
			setOrientationYawMatrix(yaw);
			_data.orientationQuat = glm::normalize(_data.orientationQuat * _data.yawQuat);
		}

		void Matrices::multOrientationMatrixPitch(float pitch) {
			setOrientationPitchMatrix(pitch);
			_data.orientationQuat = glm::normalize(_data.orientationQuat * _data.pitchQuat);
		}

		void Matrices::multOrientationMatrixRoll(float roll) {
			setOrientationRollMatrix(roll);
			_data.orientationQuat = glm::normalize(_data.orientationQuat * _data.rollQuat);
		}

		void Matrices::setOrientationYawMatrix(float yaw) {
			_data.yawQuat = glm::normalize(glm::quat(glm::cos(yaw / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f) * glm::sin(yaw / 2.0f)));
		}

		void Matrices::setOrientationPitchMatrix(float pitch) {
			_data.pitchQuat = glm::normalize(glm::quat(glm::cos(pitch / 2.0f), glm::vec3(0.0f, 1.0f, 0.0f) * glm::sin(pitch / 2.0f)));
		}

		void Matrices::setOrientationRollMatrix(float roll) {
			_data.rollQuat = glm::normalize(glm::quat(glm::cos(roll / 2.0f), glm::vec3(0.0f, 0.0f, -1.0f) * glm::sin(roll / 2.0f)));
		}

		const glm::mat4& Matrices::getTranslationMatrix() {
			return _data.translationMatrix;
		}

		const glm::mat4& Matrices::getScalingMatrix() {
			return _data.scalingMatrix;
		}

		const glm::mat4& Matrices::getRotationMatrix() {
			return _data.rotationMatrix;
		}

		const glm::mat4& Matrices::getOrientationMatrix() {
			_data.orientationMatrix = glm::mat4_cast(_data.orientationQuat);
			return _data.orientationMatrix;
		}

		const glm::mat4 &Matrices::getYawMatrix() {
			_data.yawMatrix = glm::mat4_cast(_data.yawQuat);
			return _data.yawMatrix;
		}

		const glm::mat4 &Matrices::getPitchMatrix() {
			_data.pitchMatrix = glm::mat4_cast(_data.pitchQuat);
			return _data.pitchMatrix;
		}

		const glm::mat4 &Matrices::getRollMatrix() {
			_data.rollMatrix = glm::mat4_cast(_data.rollQuat);
			return _data.rollMatrix;
		}

		void Matrices::pushState() {
			_stateStack.push(_data);
		}

		void Matrices::popState() {
			_data = _stateStack.top();
			_stateStack.pop();
		}

		void Matrices::seekState() {
			_data = _stateStack.top();
		}
	}
}
