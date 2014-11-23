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

enum MultiplicationOrder {
	SRT = 0x1,
	RST = 0x2,
	RTS = 0x4,
	STR = 0x8,
	TSR = 0x10,
	TRS = 0x20,
};

class Transformation {
public:
	Transformation();
	Transformation(Matrices *matrices);
	~Transformation();

	void setMatricesHandle(Matrices *newHandle);
	Matrices *getMatricesHandle();
	void deleteMatricesHandle();

	void setTransformationMatrix(glm::mat4 transformationMatrix);
	void resetTransformationMatrix();
	void updateTransformationMatrix(MultiplicationOrder = SRT);
	glm::mat4 getTransformationMatrix(bool noPerspectiveTransform = false);

	void pushMatrix();
	void popMatrix();
	void seekMatrix();

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

private:
	bool handleInitialized;
	Matrices *matrices;
	glm::mat4 transformationMatrix;
	std::stack<glm::mat4> matrixStack;
	std::stack<Matrices> matricesStack;
};

#endif /* OPGLLIB_TRANSFORMATION_H_ */
