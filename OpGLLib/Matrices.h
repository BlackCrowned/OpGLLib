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

	const glm::mat4& getTranslationMatrix();

	const glm::mat4& getScalingMatrix();

	const glm::mat4& getRotationMatrix();

private:
	glm::mat4 translationMatrix;
	glm::mat4 scalingMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 rotationXMatrix;
	glm::mat4 rotationYMatrix;
	glm::mat4 rotationZMatrix;

	glm::vec3 offset, scale, rotation;
};

#endif /* OPGLLIB_MATRICES_H_ */
