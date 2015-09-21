/*
 * Perspective.cpp
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Perspective.h>

namespace OpGLLib {
Perspective::Perspective() {
	perspectiveMatrix = glm::mat4(0);

	foV = 45.0f;
	aspectRatio = 1.0f;
	frustumScale = glm::vec2(1.0f, 1.0f);
	zNear = 1.0f;
	zFar = 500.0f;

	useFoV = false;

	updatePerspectiveMatrix();
}

Perspective::Perspective(float foV, float aspectRatio, float zNear, float zFar) {
	perspectiveMatrix = glm::mat4(0);

	Perspective::foV = foV;
	Perspective::aspectRatio = aspectRatio;
	Perspective::frustumScale = glm::vec2(1.0f, 1.0f);
	Perspective::zNear = zNear;
	Perspective::zFar = zFar;

	useFoV = true;

	updatePerspectiveMatrix();
}

Perspective::Perspective(glm::vec2 frustumScale, float aspectRatio, float zNear, float zFar) {
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

glm::vec2 Perspective::calcFrustumScale(float foV) {
	Perspective::foV = foV;
	float foVRad = glm::radians(foV);
	return glm::vec2(1.0f / glm::tan(foVRad / 2.0f), 1.0f / glm::tan(foVRad / 2.0f));
}

glm::vec2 Perspective::calcFrustumScale(float foV, float aspectRatio) {
	Perspective::foV = foV;
	Perspective::aspectRatio = aspectRatio;
	float foVRad = glm::radians(foV);
	return glm::vec2(1.0f / glm::tan(foVRad / 2.0f) / aspectRatio, 1.0f / glm::tan(foVRad / 2.0f));
}

void Perspective::setPerspectiveMatrix(glm::mat4 perspectiveMatrix) {
	Perspective::perspectiveMatrix = perspectiveMatrix;
}

void Perspective::setPerspectiveMatrix(float foV, float zNear, float zFar) {
	setPerspectiveMatrix(calcFrustumScale(foV), zNear, zFar);
	useFoV = true;
}

void Perspective::setPerspectiveMatrix(float foV, float aspectRatio, float zNear, float zFar) {
	setPerspectiveMatrix(calcFrustumScale(foV, aspectRatio), zNear, zFar);
	useFoV = true;
}

void Perspective::setPerspectiveMatrix(glm::vec2 frustumScale, float zNear, float zFar) {
	Perspective::frustumScale = frustumScale;
	Perspective::zNear = zNear;
	Perspective::zFar = zFar;
	Perspective::useFoV = false;
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

void Perspective::setAspectRatio(float aspectRatio) {
	Perspective::aspectRatio = aspectRatio;
}

void Perspective::setFoV(float foV) {
	Perspective::foV = foV;
	useFoV = true;
}

void Perspective::setFrustumScale(glm::vec2 frustumScale) {
	Perspective::frustumScale = frustumScale;
	useFoV = false;
}

void Perspective::setZNear(float zNear) {
	Perspective::zNear = zNear;
}

void Perspective::setZFar(float zFar) {
	Perspective::zFar = zFar;
}

void Perspective::pushState() {
	stateStack.push(*this);
}

void Perspective::popState() {
	Perspective tmp = stateStack.top();
	stateStack.pop();
	perspectiveMatrix = tmp.perspectiveMatrix;
	foV = tmp.foV;
	aspectRatio = tmp.aspectRatio;
	frustumScale = tmp.frustumScale;
	zNear = tmp.zNear;
	zFar = tmp.zFar;
	useFoV = tmp.useFoV;
}

void Perspective::seekState() {
	Perspective tmp = stateStack.top();
	perspectiveMatrix = tmp.perspectiveMatrix;
	foV = tmp.foV;
	aspectRatio = tmp.aspectRatio;
	frustumScale = tmp.frustumScale;
	zNear = tmp.zNear;
	zFar = tmp.zFar;
	useFoV = tmp.useFoV;
}
}

