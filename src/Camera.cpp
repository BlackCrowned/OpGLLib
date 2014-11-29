/*
 * Camera.cpp
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Camera.h>

using namespace gl;

Camera::Camera() :
		Matrices() {
		cameraMatrix = glm::mat4(1.0f);
		lookAtMatrix = glm::mat4(1.0f);
}

Camera::~Camera() {

}

void Camera::resetCameraMatrix() {
	cameraMatrix = glm::mat4(1.0f);
}

void Camera::position(glm::vec3 pos) {
	Camera::pos = pos;
	setTranslationMatrix(-pos);
}

void Camera::translate(glm::vec3 offset) {
	pos += offset;
	setTranslationMatrix(-pos);
}

void Camera::translateX(GLfloat x) {
	pos.x += x;
	setTranslationMatrixX(-pos.x);
}

void Camera::translateY(GLfloat y) {
	pos.y += y;
	setTranslationMatrixY(-pos.y);
}

void Camera::translateZ(GLfloat z) {
	pos.z += z;
	setTranslationMatrixZ(-pos.z);
}

void Camera::lookAt(glm::vec3 pos) {
	lookAt(pos, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::lookAt(glm::vec3 pos, glm::vec3 up) {
	glm::vec3 ZAxis = glm::normalize(pos - Camera::pos);
	glm::vec3 XAxis = glm::normalize(glm::cross(ZAxis, up));
	glm::vec3 YAxis = glm::cross(XAxis, ZAxis);
	lookAtMatrix = glm::mat4(1.0f);

	lookAtMatrix[0].x = XAxis.x;
	lookAtMatrix[1].x = XAxis.y;
	lookAtMatrix[2].x = XAxis.z;
	lookAtMatrix[0].y = YAxis.x;
	lookAtMatrix[1].y = YAxis.y;
	lookAtMatrix[2].y = YAxis.z;
	lookAtMatrix[0].z = -ZAxis.x;
	lookAtMatrix[1].z = -ZAxis.y;
	lookAtMatrix[2].z = -ZAxis.z;

	_debug.log(lookAtMatrix, "lookAtMatrix");

}

const glm::mat4& Camera::getCameraMatrix() {
	cameraMatrix = lookAtMatrix * getTranslationMatrix();
	return cameraMatrix;
}

