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

void Camera::lookAt(glm::vec3 pos, glm::vec3 forward, glm::vec3 upward) {
	//Rotate around offset
	//cos = a * b / (|a| * |b|)

	glm::vec3 richtungsVektor = pos - Camera::pos;

	//GLfloat dotToLength = glm::dot(richtungsVektor, forward) / (glm::length(richtungsVektor) * glm::length(forward));

	GLfloat angle;
	if (glm::normalize(richtungsVektor).x < glm::normalize(forward).x) {
		angle = glm::acos(glm::dot(richtungsVektor, forward) / (glm::length(richtungsVektor) * glm::length(forward)));
	}
	else {
		angle = -glm::acos(glm::dot(richtungsVektor, forward) / (glm::length(richtungsVektor) * glm::length(forward)));
	}

	setRotationMatrix(glm::vec3(0.0f, -angle, 0.0f));

}

const glm::mat4& Camera::getCameraMatrix() {
	cameraMatrix = getRotationMatrix() * getTranslationMatrix();
	return cameraMatrix;
}
