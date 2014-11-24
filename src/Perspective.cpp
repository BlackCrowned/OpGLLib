/*
 * Perspective.cpp
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Perspective.h>

using namespace gl;

Perspective::Perspective() {
	perspectiveMatrix = glm::mat4(0);

	foV = 45.0f;
	aspectRatio = 1.0f;
	frustumScale = glm::vec2(1.0f, 1.0f);
	zNear = 1.0f;
	zFar = 500.0f;

	useFoV = true;

	updatePerspectiveMatrix();
}

Perspective::Perspective(GLfloat foV, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar) {
	perspectiveMatrix = glm::mat4(0);

	Perspective::foV = foV;
	Perspective::aspectRatio = aspectRatio;
	Perspective::frustumScale = glm::vec2(1.0f, 1.0f);
	Perspective::zNear = zNear;
	Perspective::zFar = zFar;

	useFoV = true;

	updatePerspectiveMatrix();
}

Perspective::Perspective(glm::vec2 frustumScale, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar) {
	perspectiveMatrix = glm::mat4(0);

	Perspective::foV = 45.0f;
	Perspective::aspectRatio = aspectRatio;
	Perspective::frustumScale = frustumScale;
	Perspective::zNear = zNear;
	Perspective::zFar = zFar;

	useFoV = false;

	updatePerspectiveMatrix();
}

Perspective::~Perspective() {

}

glm::vec2 Perspective::calcFrustumScale(GLfloat foV) {
	Perspective::foV = foV;
	GLfloat foVRad = glm::radians(foV);
	return glm::vec2(1.0f / glm::tan(foVRad / 2.0f), 1.0f / glm::tan(foVRad / 2.0f));
}

glm::vec2 Perspective::calcFrustumScale(GLfloat foV, GLfloat aspectRatio) {
	Perspective::foV = foV;
	Perspective::aspectRatio = aspectRatio;
	GLfloat foVRad = glm::radians(foV);
	return glm::vec2(1.0f / glm::tan(foVRad / 2.0f) / aspectRatio, 1.0f / glm::tan(foVRad / 2.0f));
}

void Perspective::setPerspectiveMatrix(glm::mat4 perspectiveMatrix) {
	Perspective::perspectiveMatrix = perspectiveMatrix;
}

void Perspective::setPerspectiveMatrix(GLfloat foV, GLfloat zNear, GLfloat zFar) {
	setPerspectiveMatrix(calcFrustumScale(foV), zNear, zFar);
}

void Perspective::setPerspectiveMatrix(GLfloat foV, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar) {
	setPerspectiveMatrix(calcFrustumScale(foV, aspectRatio), zNear, zFar);
}

void Perspective::setPerspectiveMatrix(glm::vec2 frustumScale, GLfloat zNear, GLfloat zFar) {
	Perspective::frustumScale = frustumScale;
	Perspective::zNear = zNear;
	Perspective::zFar = zFar;
	perspectiveMatrix[0].x = frustumScale.x;
	perspectiveMatrix[1].y = frustumScale.y;
	perspectiveMatrix[2].z = (zFar + zNear) / (zNear - zFar);
	perspectiveMatrix[3].z = (2 * zFar * zNear) / (zNear - zFar);
	perspectiveMatrix[2].w = -1.0f;
}

void Perspective::updatePerspectiveMatrix() {
	glm::vec2 frustumScale;
	if (useFoV) {
		frustumScale = calcFrustumScale(foV, aspectRatio);
	} else {
		frustumScale = Perspective::frustumScale;
		frustumScale.x /= aspectRatio;
	}
	perspectiveMatrix[0].x = frustumScale.x;
	perspectiveMatrix[1].y = frustumScale.y;
	perspectiveMatrix[2].z = (zFar + zNear) / (zNear - zFar);
	perspectiveMatrix[3].z = (2 * zFar * zNear) / (zNear - zFar);
	perspectiveMatrix[2].w = -1.0f;
}

glm::mat4 Perspective::getPerspectiveMatrix() {
	return perspectiveMatrix;
}

void Perspective::setAspectRatio(GLfloat aspectRatio) {
	Perspective::aspectRatio = aspectRatio;
}

void Perspective::setFoV(GLfloat foV) {
	Perspective::foV = foV;
	useFoV = true;
}

void Perspective::setFrustumScale(glm::vec2 frustumScale) {
	Perspective::frustumScale = frustumScale;
	useFoV = false;
}

void Perspective::setZNear(GLfloat zNear) {
	Perspective::zNear = zNear;
}

void Perspective::setZFar(GLfloat zFar) {
	Perspective::zFar = zFar;
}
