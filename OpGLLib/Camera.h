/*
 * Camera.h
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_CAMERA_H_
#define OPGLLIB_CAMERA_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/Debug.h>

class Camera {
public:
	Camera();
	Camera(glm::vec3 center, glm::vec3 up, glm::vec3 cameraPos);
	~Camera();

	void resetCameraMatrix();

	void position(glm::vec3 cameraPos);

	void translate(glm::vec3 offset);
	void translateX(gl::GLfloat x);
	void translateY(gl::GLfloat y);
	void translateZ(gl::GLfloat z);

	void strafe(glm::vec3 offset);
	void strafeX(gl::GLfloat x);
	void strafeY(gl::GLfloat y);
	void strafeZ(gl::GLfloat z);

	void lookAt(glm::vec3 center);
	void lookAt(glm::vec3 center, glm::vec3 up);
	void lookAt(glm::vec3 center, glm::vec3 up, glm::vec3 cameraPos);

	const glm::mat4& getCameraMatrix();

	void pushState();
	void popState();
	void seekState();

private:
	glm::mat4 cameraMatrix;

	glm::vec3 center, up, cameraPos;

	std::stack<Camera> stateStack;
};

#endif /* OPGLLIB_CAMERA_H_ */
