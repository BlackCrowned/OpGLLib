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
	Perspective(gl::GLfloat foV, gl::GLfloat aspectRatio = 1.0f, gl::GLfloat zNear = 1.0f, gl::GLfloat zFar = 500.0f);
	Perspective(glm::vec2 frustumScale, gl::GLfloat aspectRatio = 1.0f, gl::GLfloat zNear = 1.0f, gl::GLfloat zFar = 500.0f);
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

	void pushState();
	void popState();
	void seekState();

private:
	glm::mat4 perspectiveMatrix;

	gl::GLfloat foV;
	gl::GLfloat aspectRatio;
	glm::vec2 frustumScale;
	gl::GLfloat zNear;
	gl::GLfloat zFar;

	bool useFoV;

	std::stack<Perspective> stateStack;
};

#endif /* OPGLLIB_PERSPECTIVE_H_ */
