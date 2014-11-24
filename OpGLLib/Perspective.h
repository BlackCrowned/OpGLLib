/*
 * Perspective.h
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#include <OpGLLib/internal.h>

#ifndef OPGLLIB_PERSPECTIVE_H_
#define OPGLLIB_PERSPECTIVE_H_

class Perspective {
public:
	Perspective();
	~Perspective();

	glm::vec2 calcFrustumScale(gl::GLfloat foV);
	glm::vec2 calcFrustumScale(gl::GLfloat foV, gl::GLfloat aspectRatio);

	void setPerspectiveMatrix(glm::mat4 perspectiveMatrix);
	void setPerspectiveMatrix(gl::GLfloat foV, gl::GLfloat zNear, gl::GLfloat zFar);
	void setPerspectiveMatrix(gl::GLfloat foV, gl::GLfloat aspectRatio, gl::GLfloat zNear, gl::GLfloat zFar);
	void setPerspectiveMatrix(glm::vec2 frustumScale, gl::GLfloat zNear, gl::GLfloat zFar);
	void updatePerspectiveMatrix();
	glm::mat4 getPerspectiveMatrix();

	void setFoV(gl::GLfloat foV);
	void setAspectRatio(gl::GLfloat aspectRatio);
	void setFrustumScale(glm::vec2 frustumScale);
	void setZNear(gl::GLfloat zNear);
	void setZFar(gl::GLfloat zFar);

private:
	glm::mat4 perspectiveMatrix;

	gl::GLfloat foV;
	gl::GLfloat aspectRatio;
	glm::vec2 frustumScale;
	gl::GLfloat zNear;
	gl::GLfloat zFar;

	bool useFoV;
};

#endif /* OPGLLIB_PERSPECTIVE_H_ */
