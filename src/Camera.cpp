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
	lookAt(pos, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::lookAt(glm::vec3 pos, glm::vec3 forward, glm::vec3 upward, glm::vec3 right) {
	glm::vec3 directionalVector = pos - Camera::pos;
	glm::mat3 coordinateMatrix = glm::mat3(1.0f);
	coordinateMatrix[0] = right;
	coordinateMatrix[1] = upward;
	coordinateMatrix[2] = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 noYDimension = coordinateMatrix * directionalVector;
	noYDimension.y = 0.0f;
	glm::vec3 noXDimension = coordinateMatrix * directionalVector;
	noXDimension.x = 0.0f;

	std::cout << directionalVector.x << " | " << directionalVector.y << " | " << directionalVector.z << std::endl;
	std::cout << noYDimension.x << " | " << noYDimension.y << " | " << noYDimension.z << std::endl;
	std::cout << noXDimension.x << " | " << noXDimension.y << " | " << noXDimension.z << std::endl;
	std::cout << "-------------------------------------" << std::endl;

	GLfloat angleY, angleX;
	if (glm::normalize(noYDimension).x < glm::normalize(forward).x) {
		angleY = glm::acos(glm::dot(noYDimension, forward) / (glm::length(noYDimension) * glm::length(forward)));
	}
	else {
		angleY = -glm::acos(glm::dot(noYDimension, forward) / (glm::length(noYDimension) * glm::length(forward)));
	}
	if (glm::normalize(noXDimension).y < glm::normalize(forward).y) {
		angleX = -glm::acos(glm::dot(noXDimension, forward) / (glm::length(noXDimension) * glm::length(forward)));
	}
	else {
		angleX = glm::acos(glm::dot(noXDimension, forward) / (glm::length(noXDimension) * glm::length(forward)));
	}

	setRotationMatrix(glm::vec3(-angleX, -angleY, 0.0f));

}

const glm::mat4& Camera::getCameraMatrix() {
	cameraMatrix = getRotationMatrix() * getTranslationMatrix();
	return cameraMatrix;
}

