/*
 * Camera.cpp
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Camera.h>

namespace OpGLLib {
Camera::Camera() {
	center = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);

	lookAt(center, up, cameraPos);
}

Camera::Camera(glm::vec3 center, glm::vec3 up, glm::vec3 cameraPos) {
	Camera::center = center;
	Camera::up = up;
	Camera::cameraPos = cameraPos;

	lookAt(center, up, cameraPos);
}

Camera::~Camera() {

}

void Camera::resetCameraMatrix() {
	cameraMatrix = glm::mat4(1.0f);
}

void Camera::position(glm::vec3 cameraPos) {
	Camera::cameraPos = cameraPos;
	lookAt(center, up, cameraPos);
}

void Camera::translate(glm::vec3 offset) {
	cameraPos += offset;
	lookAt(center, up, cameraPos);
}

void Camera::translateX(float x) {
	cameraPos.x += x;
	lookAt(center, up, cameraPos);
}

void Camera::translateY(float y) {
	cameraPos.y += y;
	lookAt(center, up, cameraPos);
}

void Camera::translateZ(float z) {
	cameraPos.z += z;
	lookAt(center, up, cameraPos);
}

void Camera::strafe(glm::vec3 offset) {
	center += offset;
	cameraPos += offset;
	lookAt(center, up, cameraPos);
}

void Camera::strafeX(float x) {
	center.x += x;
	cameraPos.x += x;
	lookAt(center, up, cameraPos);
}

void Camera::strafeY(float y) {
	center.y += y;
	cameraPos.y += y;
	lookAt(center, up, cameraPos);
}

void Camera::strafeZ(float z) {
	center.z += z;
	cameraPos.x += z;
	lookAt(center, up, cameraPos);
}

void Camera::lookAt(glm::vec3 center) {
	Camera::center = center;
	lookAt(center, up, cameraPos);
}

void Camera::lookAt(glm::vec3 center, glm::vec3 up) {
	Camera::center = center;
	Camera::up = up;
	lookAt(center, up, cameraPos);
}

void Camera::lookAt(glm::vec3 center, glm::vec3 up, glm::vec3 cameraPos) {
	Camera::center = center;
	Camera::up = up;
	Camera::cameraPos = cameraPos;
	glm::vec3 zAxis = glm::normalize(center - cameraPos);
	glm::vec3 xAxis = glm::normalize(glm::cross(zAxis, up));
	glm::vec3 yAxis = glm::cross(xAxis, zAxis);
	cameraMatrix = glm::mat4(1.0f);

	cameraMatrix[0].x = xAxis.x;
	cameraMatrix[1].x = xAxis.y;
	cameraMatrix[2].x = xAxis.z;
	cameraMatrix[0].y = yAxis.x;
	cameraMatrix[1].y = yAxis.y;
	cameraMatrix[2].y = yAxis.z;
	cameraMatrix[0].z = -zAxis.x;
	cameraMatrix[1].z = -zAxis.y;
	cameraMatrix[2].z = -zAxis.z;
	cameraMatrix[3].x = -glm::dot(xAxis, cameraPos);
	cameraMatrix[3].y = -glm::dot(yAxis, cameraPos);
	cameraMatrix[3].z = glm::dot(zAxis, cameraPos);
}

const glm::mat4& Camera::getCameraMatrix() {
	return cameraMatrix;
}

void Camera::pushState() {
	stateStack.push(*this);
}

void Camera::popState() {
	Camera tmp = stateStack.top();
	stateStack.pop();
	cameraMatrix = tmp.cameraMatrix;
	center = tmp.center;
	up = tmp.up;
	cameraPos = tmp.cameraPos;
}

void Camera::seekState() {
	Camera tmp = stateStack.top();
	cameraMatrix = tmp.cameraMatrix;
	center = tmp.center;
	up = tmp.up;
	cameraPos = tmp.cameraPos;
}
}

