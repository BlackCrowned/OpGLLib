/*
 * Matrices.cpp
 *
 *  Created on: 19.11.2014
 *      Author: Michael
 */

#include <OpGLLib/Matrices.h>

using namespace gl;

Matrices::Matrices() {
	perspectiveMatrix = glm::mat4(0);
	translationMatrix = glm::mat4(1.0f);
	scalingMatrix = glm::mat4(1.0f);
}

Matrices::~Matrices() {

}

glm::vec2 Matrices::calcFrustumScale(GLfloat foV) {
	GLfloat foVRad = glm::radians(foV);
	return glm::vec2(1.0f / glm::tan(foVRad / 2.0f), 1.0f / glm::tan(foVRad / 2.0f));
}

glm::vec2 Matrices::calcFrustumScale(GLfloat foV, GLfloat aspectRatio) {
	GLfloat foVRad = glm::radians(foV);
	return glm::vec2(1.0f / glm::tan(foVRad / 2.0f) / aspectRatio, 1.0f / glm::tan(foVRad / 2.0f));
}

void Matrices::setPerspectiveMatrix(glm::mat4 perspectiveMatrix) {
	Matrices::perspectiveMatrix = perspectiveMatrix;
}

void Matrices::setPerspectiveMatrix(GLfloat foV, GLfloat zNear, GLfloat zFar) {
	setPerspectiveMatrix(calcFrustumScale(foV), zNear, zFar);
}

void Matrices::setPerspectiveMatrix(GLfloat foV, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar) {
	setPerspectiveMatrix(calcFrustumScale(foV, aspectRatio), zNear, zFar);
}

void Matrices::setPerspectiveMatrix(glm::vec2 frustumScale, GLfloat zNear, GLfloat zFar) {
	perspectiveMatrix = glm::mat4(0.0f);
	perspectiveMatrix[0].x = frustumScale.x;
	perspectiveMatrix[1].y = frustumScale.y;
	perspectiveMatrix[2].z = (zFar + zNear) / (zNear - zFar);
	perspectiveMatrix[3].z = (2 * zFar * zNear) / (zNear - zFar);
	perspectiveMatrix[2].w = -1.0f;
}

void Matrices::setTranslationMatrix(glm::mat4 translationMatrix) {
	Matrices::translationMatrix = translationMatrix;
}

void Matrices::setTranslationMatrix(glm::vec3 offset) {
	translationMatrix = glm::mat4(1.0f);
	translationMatrix[3].x = offset.x;
	translationMatrix[3].y = offset.y;
	translationMatrix[3].z = offset.z;
}

void Matrices::setScalingMatrix(glm::mat4 scalingMatrix) {
	Matrices::scalingMatrix = scalingMatrix;
}

void Matrices::setScalingMatrix(glm::vec3 scale) {
	scalingMatrix = glm::mat4(1.0f);
	scalingMatrix[0].x = scale.x;
	scalingMatrix[1].y = scale.y;
	scalingMatrix[2].z = scale.z;
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
void Matrices::setRotationXMatrix(GLfloat x) {
	rotationXMatrix = glm::mat4(1.0f);
	rotation.x = x;
	rotationXMatrix[1].y = cos(x);
	rotationXMatrix[2].y = -sin(x);
	rotationXMatrix[1].z = sin(x);
	rotationXMatrix[2].z = cos(x);
}

void Matrices::setRotationYMatrix(GLfloat y) {
	rotationYMatrix = glm::mat4(1.0f);
	rotation.y = y;
	rotationYMatrix[0].x = cos(y);
	rotationYMatrix[2].x = sin(y);
	rotationYMatrix[0].z = -sin(y);
	rotationYMatrix[2].z = cos(y);
}

void Matrices::setRotationZMatrix(GLfloat z) {
	rotationZMatrix = glm::mat4(1.0f);
	rotation.z = z;
	rotationZMatrix[0].x = cos(z);
	rotationZMatrix[1].x = -sin(z);
	rotationZMatrix[0].y = sin(z);
	rotationZMatrix[1].y = cos(z);
}

glm::mat4 *Matrices::getPerspectiveMatrix() {
	return &perspectiveMatrix;
}

glm::mat4 *Matrices::getTranslationMatrix() {
	return &translationMatrix;
}

glm::mat4 *Matrices::getScalingMatrix() {
	return &scalingMatrix;
}

glm::mat4 *Matrices::getRotationMatrix() {
	return &rotationMatrix;
}
