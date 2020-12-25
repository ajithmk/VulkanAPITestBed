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
	glm::vec3 position = glm::vec3{ 0,0,0 };
	glm::mat4 cameraMatrix = glm::mat4(1.0);
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

	void RotateCamera(float deltaHeading, float deltaAttitude)
	{
		attitude_ += -deltaAttitude * camera_speed_;
		if (attitude_ > glm::half_pi<float>())
			attitude_ = glm::half_pi<float>() - 0.001f;
		if (attitude_ < -glm::half_pi<float>())
			attitude_ = -glm::half_pi<float>() + 0.001f;
		heading_ += deltaHeading * camera_speed_;
		if (deltaHeading != 0 || deltaAttitude != 0)
		{
			std::cout << std::to_string(attitude_) + "   " + "Attitude" + "\n";
			std::cout << std::to_string(heading_) + "   " + "Heading" + "\n";
		}

		EulerToMatrix(glm::vec3{ heading_, bank_, attitude_ }, cameraMatrix);
		cameraMatrix = glm::translate(cameraMatrix, position);
	}

	void TranslateCamera(float forwardBackward, float leftRight)
	{
		position += glm::vec3{ -leftRight, 0.0, -forwardBackward };
		cameraMatrix = glm::translate(cameraMatrix, position);
	}

	glm::mat4 get_camera_matrix()
	{
		return cameraMatrix;
	}
};

extern Camera camera;
