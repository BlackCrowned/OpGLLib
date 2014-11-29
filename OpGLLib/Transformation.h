/*
 * Transformation.h
 *
 *  Created on: 22.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_TRANSFORMATION_H_
#define OPGLLIB_TRANSFORMATION_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/Matrices.h>
#include <OpGLLib/Perspective.h>
#include <OpGLLib/Camera.h>

enum MultiplicationOrder {
	SRT = 0x1, RST = 0x2, RTS = 0x4, STR = 0x8, TSR = 0x10, TRS = 0x20,
};

class Transformation : public Matrices, public Camera, public Perspective{
public:
	Transformation();
	~Transformation();

	void setTransformationMatrix(glm::mat4 transformationMatrix);
	void resetTransformationMatrix();
	void updateTransformationMatrix(MultiplicationOrder = SRT);
	glm::mat4 getTransformationMatrix(bool noCameraTransform = false, bool noPerspectiveTransform = false);

	Matrices * matrices = static_cast<Matrices *>(this);
	Camera * camera = static_cast<Camera *>(this);
	Perspective * perspective = static_cast<Perspective *>(this);

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
	void translateX(gl::GLfloat x);
	void translateY(gl::GLfloat y);
	void translateZ(gl::GLfloat z);

	void scale(glm::vec3 scale);
	void scaleX(gl::GLfloat x);
	void scaleY(gl::GLfloat y);
	void scaleZ(gl::GLfloat z);

	void rotate(glm::vec3 rotation);
	void rotateX(gl::GLfloat x);
	void rotateY(gl::GLfloat y);
	void rotateZ(gl::GLfloat z);

	void addMatrix(glm::mat4 matrix);

private:
	glm::mat4 transformationMatrix;

	std::stack<glm::mat4> matrixStack;
};

#endif /* OPGLLIB_TRANSFORMATION_H_ */
