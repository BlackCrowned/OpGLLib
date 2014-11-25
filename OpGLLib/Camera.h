/*
 * Camera.h
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_CAMERA_H_
#define OPGLLIB_CAMERA_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/Matrices.h>

class Camera: private Matrices {
public:
	Camera();
	~Camera();

	void resetCameraMatrix();

	void position(glm::vec3 pos);

	void translate(glm::vec3 offset);
	void translateX(gl::GLfloat x);
	void translateY(gl::GLfloat y);
	void translateZ(gl::GLfloat z);

	void lookAt(glm::vec3 pos, glm::vec3 forward, glm::vec3 upward);

	const glm::mat4& getCameraMatrix();

private:
	glm::mat4 cameraMatrix;

	glm::vec3 pos;
};

#endif /* OPGLLIB_CAMERA_H_ */
