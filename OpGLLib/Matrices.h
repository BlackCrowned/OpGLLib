/*
 * Matrices.h
 *
 *  Created on: 19.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_MATRICES_H_
#define OPGLLIB_MATRICES_H_

#include <OpGLLib/internal.h>

class Matrices {
public:
	Matrices();
	~Matrices();

	void setTranslationMatrix(glm::mat4 translationMatrix);
	void setTranslationMatrix(glm::vec3 offset);
	void setTranslationMatrixX(gl::GLfloat x);
	void setTranslationMatrixY(gl::GLfloat y);
	void setTranslationMatrixZ(gl::GLfloat z);

	void setScalingMatrix(glm::mat4 scalingMatrix);
	void setScalingMatrix(glm::vec3 scale);
	void setScalingMatrixX(gl::GLfloat x);
	void setScalingMatrixY(gl::GLfloat y);
	void setScalingMatrixZ(gl::GLfloat z);

	void setRotationMatrix(glm::mat4 rotationMatrix);
	void setRotationMatrix(glm::vec3 rotation);
	void setRotationMatrixX(gl::GLfloat x);
	void setRotationMatrixY(gl::GLfloat y);
	void setRotationMatrixZ(gl::GLfloat z);
	void updateRotationMatrix();

	void setRotationXMatrix(gl::GLfloat x);
	void setRotationYMatrix(gl::GLfloat y);
	void setRotationZMatrix(gl::GLfloat z);

	void setOrientationMatrix(glm::mat4 orientationMatrix);
	void setOrientationMatrix(glm::mat3 axes, glm::vec3 rotations);
	void setOrientationMatrix(glm::vec3 axis, gl::GLfloat rotation);
	void setOrientationMatrix(gl::GLfloat yaw, gl::GLfloat pitch, gl::GLfloat roll);
	void resetOrientationMatrix();
	void multOrientationMatrix(glm::mat3 axes, glm::vec3 rotations);
	void multOrientationMatrix(glm::vec3 axis, gl::GLfloat rotation);
	void multOrientationMatrix(gl::GLfloat yaw, gl::GLfloat pitch, gl::GLfloat roll);
	void setOrientationMatrixYaw(gl::GLfloat yaw);
	void setOrientationMatrixPitch(gl::GLfloat pitch);
	void setOrientationMatrixRoll(gl::GLfloat roll);
	void multOrientationMatrixYaw(gl::GLfloat yaw);
	void multOrientationMatrixPitch(gl::GLfloat pitch);
	void multOrientationMatrixRoll(gl::GLfloat roll);

	void setOrientationYawMatrix(gl::GLfloat yaw);
	void setOrientationPitchMatrix(gl::GLfloat pitch);
	void setOrientationRollMatrix(gl::GLfloat roll);

	const glm::mat4& getTranslationMatrix();

	const glm::mat4& getScalingMatrix();

	const glm::mat4& getRotationMatrix();

	const glm::mat4& getOrientationMatrix();

	const glm::mat4 &getYawMatrix();
	const glm::mat4 &getPitchMatrix();
	const glm::mat4 &getRollMatrix();

	void pushState();
	void popState();
	void seekState();

private:
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	glm::mat4 scalingMatrix = glm::mat4(1.0f);
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	glm::mat4 rotationXMatrix = glm::mat4(1.0f);
	glm::mat4 rotationYMatrix = glm::mat4(1.0f);
	glm::mat4 rotationZMatrix = glm::mat4(1.0f);
	glm::mat4 orientationMatrix = glm::mat4(1.0f);
	glm::quat orientationQuat = glm::quat();
	glm::mat4 yawMatrix = glm::mat4(1.0f);
	glm::quat yawQuat = glm::quat();
	glm::mat4 pitchMatrix = glm::mat4(1.0f);
	glm::quat pitchQuat = glm::quat();
	glm::mat4 rollMatrix = glm::mat4(1.0f);
	glm::quat rollQuat = glm::quat();

	glm::vec3 offset, scale, rotation;

	std::stack<Matrices> stateStack;
};

#endif /* OPGLLIB_MATRICES_H_ */
