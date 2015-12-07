/*
 * Transformation.h
 *
 *  Created on: 22.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_TRANSFORMATION_H_
#define OPGLLIB_TRANSFORMATION_H_

#define INCLUDE_GLM
#include <OpGLLib/internal.h>

#include <OpGLLib/Matrices.h>
#include <OpGLLib/Perspective.h>
#include <OpGLLib/Camera.h>
#include <OpGLLib/gl/Uniform.h>

#include <iostream>

namespace OpGLLib {
enum MultiplicationOrder {
	SRT = 0x1, RST = 0x2, RTS = 0x4, STR = 0x8, TSR = 0x10, TRS = 0x20,
};

class Transformation: public Matrices, public Camera, public Perspective {
public:
	Transformation();
	~Transformation();

	void setTransformationMatrix(glm::mat4 transformationMatrix);
	void resetTransformationMatrix();
	void updateTransformationMatrix(MultiplicationOrder = SRT);
	glm::mat4 getTransformationMatrix(bool noCameraTransform = false, bool noPerspectiveTransform = false, bool noOrientationTransform =
			false);
	void updateTransformationMatrixUniform(std::shared_ptr<gl::Uniform> uniform, bool noCameraTransform = false, bool noPerspectiveTransform = false,
			bool noOrientationTransform = false);

	Matrices & matrices = static_cast<Matrices &>(*this);
	Camera & camera = static_cast<Camera &>(*this);
	Perspective & perspective = static_cast<Perspective &>(*this);

	void loadIdentityMatrix();

	void pushMatrix();
	void popMatrix();
	void seekMatrix();

	void pushCamera();
	void popCamera();
	void seekCamera();

	void pushPerspective();
	void popPerspective();
	void seekPerpective();

	void translate(glm::vec3 offset);
	void translateX(float x);
	void translateY(float y);
	void translateZ(float z);

	void scale(glm::vec3 scale);
	void scaleX(float x);
	void scaleY(float y);
	void scaleZ(float z);

	void rotate(glm::vec3 rotation);
	void rotateX(float x);
	void rotateY(float y);
	void rotateZ(float z);

	void orient(glm::vec3 orientation);
	void orient(float yaw, float pitch, float roll);
	void yaw(float yaw);
	void pitch(float pitch);
	void roll(float roll);

	void multMatrix(glm::mat4 matrix);

private:
	glm::mat4 transformationMatrix;

	std::stack<glm::mat4> matrixStack;
};
}

#endif /* OPGLLIB_TRANSFORMATION_H_ */
