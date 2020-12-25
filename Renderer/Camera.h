#pragma once

#include <glm\matrix.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtx\transform.hpp>
#include <iostream>
#include <string>
#include "Math.h"

class Camera {
private:
	float heading_ = 0.0f;
	float attitude_ = 0.0f;
	float bank_ = 0.0f;
	float yaw = heading_;
	float pitch = attitude_;
	float roll = bank_;
	glm::vec4 unitY = glm::vec4{ 0.0,1.0,0.0, 0.0 };
	glm::vec4 unitX = glm::vec4{ 1.0,0.0,0.0, 0.0 };
	glm::vec4 unitZ = glm::vec4{ 0.0,0.0,1.0, 0.0 };
	glm::vec3 position = glm::vec3{ 0,0,0 };
	glm::mat4 cameraMatrix = glm::mat4(1.0);
	glm::mat4 identity = glm::mat4(1.0f);
	float camera_speed_ = 1;

public:
	void SetCameraMatrix(glm::mat4 matrix)
	{
		cameraMatrix = matrix;
		glm::vec3 eulerAngles;
		MatrixToEuler(matrix, eulerAngles);
		heading_ = eulerAngles.x;
		attitude_ = eulerAngles.y;
		bank_ = eulerAngles.z;
	}

	void MouseUpdate()
	{
		float deltaAttitude = LowLevelUpdate::NormalizedDeltaMouseY;
		float deltaHeading = LowLevelUpdate::NormalizedDeltaMouseX;
		attitude_ += deltaAttitude * camera_speed_;
		if (attitude_ > glm::half_pi<float>())
			attitude_ = glm::half_pi<float>() - 0.001f;
		if (attitude_ < -glm::half_pi<float>())
			attitude_ = -glm::half_pi<float>() + 0.001f;
		heading_ += deltaHeading * camera_speed_;
		if (deltaHeading != 0 || deltaAttitude != 0)
		{
			//std::cout << std::to_string(attitude_) + "   " + "Attitude" + "\n";
			//std::cout << std::to_string(heading_) + "   " + "Heading" + "\n";
		}

		glm::mat4 headingMat, attitudeMat, testMatrix, testMatrix1;
		EulerToMatrix(glm::vec3{ heading_, 0, 0 }, headingMat);
		EulerToMatrix(glm::vec3{ 0,0, attitude_ }, attitudeMat);
		testMatrix1 = headingMat * attitudeMat;
		cameraMatrix = attitudeMat * headingMat;
		EulerToMatrix(glm::vec3{ heading_, bank_, attitude_ }, testMatrix);
		cameraMatrix[3] = glm::vec4{ 0.0, 0.0, 0.0, 1.0 };
		cameraMatrix = glm::translate(cameraMatrix, position);
	}

	void KeyboardUpdate()
	{
		float forwardBackward = 0.0, leftRight = 0.0;
		if (LowLevelUpdate::w_pressed)
			forwardBackward = LowLevelUpdate::NormalizedDelta;
		if (LowLevelUpdate::s_pressed)
			forwardBackward = -LowLevelUpdate::NormalizedDelta;
		if (LowLevelUpdate::a_pressed)
			leftRight = LowLevelUpdate::NormalizedDelta;
		if (LowLevelUpdate::d_pressed)
			leftRight = -LowLevelUpdate::NormalizedDelta;

		glm::mat4 inv_camera_mat = glm::inverse(cameraMatrix);
		glm::vec3 cam_forward = inv_camera_mat * unitZ;
		glm::vec3 cam_right = inv_camera_mat * unitX;
		cam_forward =  glm::normalize(cam_forward);
		cam_right = glm::normalize(cam_right);
		position += leftRight * cam_right + forwardBackward * cam_forward ;
		//std::cout << std::to_string(position.x) + "   " + std::to_string(position.y) + "   " + std::to_string(position.z) + "   " + "deltaPos" + "\n";
		cameraMatrix[3] = glm::vec4{ 0.0, 0.0, 0.0, 1.0 };
		cameraMatrix = glm::translate(cameraMatrix, position);
	}

	glm::mat4 get_camera_matrix()
	{
		return cameraMatrix;
	}
};

extern Camera camera;
