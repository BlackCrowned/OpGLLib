/*
 * Camera.cpp
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Camera.h>

namespace OpGLLib {
namespace gl {
Camera::Camera() : _data({glm::mat4(), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)}), _stateStack() {
	lookAt(_data.center, _data.up, _data.cameraPos);
}

Camera::Camera(glm::vec3 center, glm::vec3 up, glm::vec3 cameraPos) : _data({glm::mat4(), center, up, cameraPos}), _stateStack() {
	lookAt(center, up, cameraPos);
}

void Camera::resetCameraMatrix() {
	_data.cameraMatrix = glm::mat4(1.0f);
}

void Camera::position(glm::vec3 cameraPos) {
	_data.cameraPos = cameraPos;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::translate(glm::vec3 offset) {
	_data.cameraPos += offset;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::translateX(float x) {
	_data.cameraPos.x += x;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::translateY(float y) {
	_data.cameraPos.y += y;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::translateZ(float z) {
	_data.cameraPos.z += z;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::strafe(glm::vec3 offset) {
	_data.center += offset;
	_data.cameraPos += offset;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::strafeX(float x) {
	_data.center.x += x;
	_data.cameraPos.x += x;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::strafeY(float y) {
	_data.center.y += y;
	_data.cameraPos.y += y;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::strafeZ(float z) {
	_data.center.z += z;
	_data.cameraPos.x += z;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::lookAt(glm::vec3 center) {
	_data.center = center;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::lookAt(glm::vec3 center, glm::vec3 up) {
	_data.center = center;
	_data.up = up;
	lookAt(_data.center, _data.up, _data.cameraPos);
}

void Camera::lookAt(glm::vec3 center, glm::vec3 up, glm::vec3 cameraPos) {
	_data.center = center;
	_data.up = up;
	_data.cameraPos = cameraPos;
	glm::vec3 zAxis = glm::normalize(_data.center - _data.cameraPos);
	glm::vec3 xAxis = glm::normalize(glm::cross(zAxis, _data.up));
	glm::vec3 yAxis = glm::cross(xAxis, zAxis);
	_data.cameraMatrix = glm::mat4(1.0f);

	_data.cameraMatrix[0].x = xAxis.x;
	_data.cameraMatrix[1].x = xAxis.y;
	_data.cameraMatrix[2].x = xAxis.z;
	_data.cameraMatrix[0].y = yAxis.x;
	_data.cameraMatrix[1].y = yAxis.y;
	_data.cameraMatrix[2].y = yAxis.z;
	_data.cameraMatrix[0].z = -zAxis.x;
	_data.cameraMatrix[1].z = -zAxis.y;
	_data.cameraMatrix[2].z = -zAxis.z;
	_data.cameraMatrix[3].x = -glm::dot(xAxis, _data.cameraPos);
	_data.cameraMatrix[3].y = -glm::dot(yAxis, _data.cameraPos);
	_data.cameraMatrix[3].z = glm::dot(zAxis, _data.cameraPos);
}

const glm::mat4& Camera::getCameraMatrix() {
	return _data.cameraMatrix;
}

void Camera::pushState() {
	_stateStack.push(_data);
}

void Camera::popState() {
	_data = _stateStack.top();
	_stateStack.pop();
}

void Camera::seekState() {
	_data = _stateStack.top();
}
}
}

