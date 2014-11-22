/*
 * Matrices.h
 *
 *  Created on: 19.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_MATRICES_H_
#define OPGLLIB_MATRICES_H_

#include <OpGLLib/internal.h>

class  Matrices {
public:
	Matrices();
	~Matrices();

	glm::vec2 calcFrustumScale(gl::GLfloat foV);
	glm::vec2 calcFrustumScale(gl::GLfloat foV, gl::GLfloat aspectRatio);

	void setPerspectiveMatrix(glm::mat4 perspectiveMatrix);
	void setPerspectiveMatrix(gl::GLfloat foV, gl::GLfloat zNear, gl::GLfloat zFar);
	void setPerspectiveMatrix(gl::GLfloat foV, gl::GLfloat aspectRatio, gl::GLfloat zNear, gl::GLfloat zFar);
	void setPerspectiveMatrix(glm::vec2 frustumScale, gl::GLfloat zNear, gl::GLfloat zFar);

	void setTranslationMatrix(glm::mat4 translationMatrix);
	void setTranslationMatrix(glm::vec3 offset);

	void setScalingMatrix(glm::mat4 scalingMatrix);
	void setScalingMatrix(glm::vec3 scale);
	void setRotationMatrix(glm::mat4 rotationMatrix);
	void setRotationMatrix(glm::vec3 rotation);
	void setRotationXMatrix(gl::GLfloat x);
	void setRotationYMatrix(gl::GLfloat y);
	void setRotationZMatrix(gl::GLfloat z);

	glm::mat4 *getPerspectiveMatrix();

	glm::mat4 *getTranslationMatrix();

	glm::mat4 *getScalingMatrix();

	glm::mat4 *getRotationMatrix();
private:
	glm::mat4 perspectiveMatrix;
	glm::mat4 translationMatrix;
	glm::mat4 scalingMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 rotationXMatrix;
	glm::mat4 rotationYMatrix;
	glm::mat4 rotationZMatrix;
};

#endif /* OPGLLIB_MATRICES_H_ */