/*
 * Matrices.h
 *
 *  Created on: 19.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_MATRICES_H_
#define OPGLLIB_MATRICES_H_

#define INCLUDE_GLM
#include <OpGLLib/internal.h>

#include <stack>
#include <memory>

namespace OpGLLib {
	namespace gl {
		class Matrices {
		public:
			Matrices() = default;
			~Matrices() = default;

			void setTranslationMatrix(glm::mat4 translationMatrix);
			void setTranslationMatrix(glm::vec3 offset);
			void resetTranslationMatrix();
			void setTranslationMatrixX(float x);
			void setTranslationMatrixY(float y);
			void setTranslationMatrixZ(float z);

			void setScalingMatrix(glm::mat4 scalingMatrix);
			void setScalingMatrix(glm::vec3 scale);
			void resetScalingMatrix();
			void setScalingMatrixX(float x);
			void setScalingMatrixY(float y);
			void setScalingMatrixZ(float z);

			void setRotationMatrix(glm::mat4 rotationMatrix);
			void setRotationMatrix(glm::vec3 rotation);
			void resetRotationMatrix();
			void setRotationMatrixX(float x);
			void setRotationMatrixY(float y);
			void setRotationMatrixZ(float z);
			void updateRotationMatrix();

			void setRotationXMatrix(float x);
			void setRotationYMatrix(float y);
			void setRotationZMatrix(float z);

			void setOrientationMatrix(glm::mat4 orientationMatrix);
			void setOrientationMatrix(glm::mat3 axes, glm::vec3 rotations);
			void setOrientationMatrix(glm::vec3 axis, float rotation);
			void setOrientationMatrix(float yaw, float pitch, float roll);
			void resetOrientationMatrix();
			void multOrientationMatrix(glm::mat3 axes, glm::vec3 rotations);
			void multOrientationMatrix(glm::vec3 axis, float rotation);
			void multOrientationMatrix(float yaw, float pitch, float roll);
			void setOrientationMatrixYaw(float yaw);
			void setOrientationMatrixPitch(float pitch);
			void setOrientationMatrixRoll(float roll);
			void multOrientationMatrixYaw(float yaw);
			void multOrientationMatrixPitch(float pitch);
			void multOrientationMatrixRoll(float roll);

			void setOrientationYawMatrix(float yaw);
			void setOrientationPitchMatrix(float pitch);
			void setOrientationRollMatrix(float roll);

			const glm::mat4& getTranslationMatrix();

			const glm::mat4& getScalingMatrix();

			const glm::mat4& getRotationMatrix();

			const glm::mat4& getOrientationMatrix();

			const glm::mat4 &getYawMatrix();
			const glm::mat4 &getPitchMatrix();
			const glm::mat4 &getRollMatrix();

			void pushState();
			void popState();
			void seekState();

		private:
			struct Data {
				glm::mat4 translationMatrix;
				glm::mat4 scalingMatrix;
				glm::mat4 rotationMatrix;
				glm::mat4 rotationXMatrix;
				glm::mat4 rotationYMatrix;
				glm::mat4 rotationZMatrix;
				glm::mat4 orientationMatrix;
				glm::quat orientationQuat;
				glm::mat4 yawMatrix;
				glm::quat yawQuat;
				glm::mat4 pitchMatrix;
				glm::quat pitchQuat;
				glm::mat4 rollMatrix;
				glm::quat rollQuat;

				glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f);
				glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
				glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
			};
			Data _data;

			std::stack<Data> _stateStack;
		};
	}

}

#endif /* OPGLLIB_MATRICES_H_ */
