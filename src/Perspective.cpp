/*
 * Perspective.cpp
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Perspective.h>

namespace OpGLLib {
namespace gl {
Perspective::Perspective() : _data({glm::mat4(0), 45.0f, 1.0f, glm::vec2(1.0f, 1.0f), 1.0f, 500.0f, false}), _stateStack() {
	updatePerspectiveMatrix();
}

Perspective::Perspective(float foV, float aspectRatio, float zNear, float zFar) : _data({glm::mat4(0), foV, aspectRatio, glm::vec2(1.0f, 1.0f), zNear, zFar, true}), _stateStack() {
	updatePerspectiveMatrix();
}

Perspective::Perspective(glm::vec2 frustumScale, float aspectRatio, float zNear, float zFar) : _data({glm::mat4(0), 45.0f, aspectRatio, frustumScale, zNear, zFar, false}), _stateStack() {
	updatePerspectiveMatrix();
}

glm::vec2 Perspective::calcFrustumScale(float foV) {
	_data.foV = foV;
	float foVRad = glm::radians(foV);
	return glm::vec2(1.0f / glm::tan(foVRad / 2.0f), 1.0f / glm::tan(foVRad / 2.0f));
}

glm::vec2 Perspective::calcFrustumScale(float foV, float aspectRatio) {
	_data.foV = foV;
	_data.aspectRatio = aspectRatio;
	float foVRad = glm::radians(foV);
	return glm::vec2(1.0f / glm::tan(foVRad / 2.0f) / aspectRatio, 1.0f / glm::tan(foVRad / 2.0f));
}

void Perspective::setPerspectiveMatrix(glm::mat4 perspectiveMatrix) {
	_data.perspectiveMatrix = perspectiveMatrix;
}

void Perspective::setPerspectiveMatrix(float foV, float zNear, float zFar) {
	setPerspectiveMatrix(calcFrustumScale(foV), zNear, zFar);
	_data.useFoV = true;
}

void Perspective::setPerspectiveMatrix(float foV, float aspectRatio, float zNear, float zFar) {
	setPerspectiveMatrix(calcFrustumScale(foV, aspectRatio), zNear, zFar);
	_data.useFoV = true;
}

void Perspective::setPerspectiveMatrix(glm::vec2 frustumScale, float zNear, float zFar) {
	_data.frustumScale = frustumScale;
	_data.zNear = zNear;
	_data.zFar = zFar;
	_data.useFoV = false;
	_data.perspectiveMatrix[0].x = frustumScale.x;
	_data.perspectiveMatrix[1].y = frustumScale.y;
	_data.perspectiveMatrix[2].z = (zFar + zNear) / (zNear - zFar);
	_data.perspectiveMatrix[3].z = (2 * zFar * zNear) / (zNear - zFar);
	_data.perspectiveMatrix[2].w = -1.0f;
}

void Perspective::updatePerspectiveMatrix() {
	glm::vec2 frustumScale;
	if (_data.useFoV) {
		frustumScale = calcFrustumScale(_data.foV, _data.aspectRatio);
	} else {
		frustumScale = _data.frustumScale;
		frustumScale.x /= _data.aspectRatio;
	}
	_data.perspectiveMatrix[0].x = frustumScale.x;
	_data.perspectiveMatrix[1].y = frustumScale.y;
	_data.perspectiveMatrix[2].z = (_data.zFar + _data.zNear) / (_data.zNear - _data.zFar);
	_data.perspectiveMatrix[3].z = (2 * _data.zFar * _data.zNear) / (_data.zNear - _data.zFar);
	_data.perspectiveMatrix[2].w = -1.0f;
}

glm::mat4 Perspective::getPerspectiveMatrix() {
	return _data.perspectiveMatrix;
}

void Perspective::setAspectRatio(float aspectRatio) {
	_data.aspectRatio = aspectRatio;
}

void Perspective::setFoV(float foV) {
	_data.foV = foV;
	_data.useFoV = true;
}

void Perspective::setFrustumScale(glm::vec2 frustumScale) {
	_data.frustumScale = frustumScale;
	_data.useFoV = false;
}

void Perspective::setZNear(float zNear) {
	_data.zNear = zNear;
}

void Perspective::setZFar(float zFar) {
	_data.zFar = zFar;
}

void Perspective::pushState() {
	_stateStack.push(_data);
}

void Perspective::popState() {
	_data = _stateStack.top();
	_stateStack.pop();
}

void Perspective::seekState() {
	_data = _stateStack.top();
}
}
}

