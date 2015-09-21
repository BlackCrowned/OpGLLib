/*
 * Perspective.h
 *
 *  Created on: 24.11.2014
 *      Author: Michael
 */
#ifndef OPGLLIB_PERSPECTIVE_H_
#define OPGLLIB_PERSPECTIVE_H_

#define INCLUDE_GLM
#include <OpGLLib/internal.h>

#include <stack>

namespace OpGLLib {
class Perspective {
public:
	Perspective();
	Perspective(float foV, float aspectRatio = 1.0f, float zNear = 1.0f, float zFar = 500.0f);
	Perspective(glm::vec2 frustumScale, float aspectRatio = 1.0f, float zNear = 1.0f, float zFar = 500.0f);
	~Perspective();

	glm::vec2 calcFrustumScale(float foV);
	glm::vec2 calcFrustumScale(float foV, float aspectRatio);

	void setPerspectiveMatrix(glm::mat4 perspectiveMatrix);
	void setPerspectiveMatrix(float foV, float zNear, float zFar);
	void setPerspectiveMatrix(float foV, float aspectRatio, float zNear, float zFar);
	void setPerspectiveMatrix(glm::vec2 frustumScale, float zNear, float zFar);
	void updatePerspectiveMatrix();
	glm::mat4 getPerspectiveMatrix();

	void setFoV(float foV);
	void setAspectRatio(float aspectRatio);
	void setFrustumScale(glm::vec2 frustumScale);
	void setZNear(float zNear);
	void setZFar(float zFar);

	void pushState();
	void popState();
	void seekState();

private:
	glm::mat4 perspectiveMatrix;

	float foV;
	float aspectRatio;
	glm::vec2 frustumScale;
	float zNear;
	float zFar;

	bool useFoV;

	std::stack<Perspective> stateStack;
};
}



#endif /* OPGLLIB_PERSPECTIVE_H_ */
