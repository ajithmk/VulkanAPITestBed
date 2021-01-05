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

	// Attitude ad Bank are interchanged here as comapared to http://www.euclideanspace.com/maths/standards/index.htm
	float attitude_ = 0.0f;
	float bank_ = 0.0f;

	glm::vec4 unitY = glm::vec4{ 0.0,1.0,0.0, 0.0 };
	glm::vec4 unitX = glm::vec4{ 1.0,0.0,0.0, 0.0 };
	glm::vec4 unitZ = glm::vec4{ 0.0,0.0,1.0, 0.0 };
	glm::vec3 position = glm::vec3{ 0,0,0 };
	glm::mat4 cameraMatrix = glm::mat4(1.0);
	glm::mat4 viewMatrix = glm::mat4(1.0);
	glm::mat4 identity = glm::mat4(1.0f);
	float camera_speed_ = 1;
	float walk_speed_ = 0.5;

public:
	void SetCameraMatrix(glm::mat4 matrix)
	{
		cameraMatrix = matrix;
		glm::vec3 eulerAngles;
		MatrixToEuler(matrix, eulerAngles);
		heading_ = eulerAngles.x;
		attitude_ = eulerAngles.z;
		bank_ = eulerAngles.y;
	}

	void MouseUpdate()
	{
		float deltaAttitude = LowLevelUpdate::NormalizedDeltaMouseY;
		float deltaHeading = LowLevelUpdate::NormalizedDeltaMouseX;
		attitude_ -= deltaAttitude * camera_speed_;
		if (attitude_ > glm::half_pi<float>())
			attitude_ = glm::half_pi<float>() - 0.001f;
		if (attitude_ < -glm::half_pi<float>())
			attitude_ = -glm::half_pi<float>() + 0.001f;
		heading_ += deltaHeading * camera_speed_;
	}

	void KeyboardUpdate()
	{
		float forwardBackward = 0.0, leftRight = 0.0;
		if (LowLevelUpdate::w_pressed)
			forwardBackward = LowLevelUpdate::NormalizedDelta * walk_speed_;
		if (LowLevelUpdate::s_pressed)
			forwardBackward = -LowLevelUpdate::NormalizedDelta * walk_speed_;
		if (LowLevelUpdate::a_pressed)
			leftRight = LowLevelUpdate::NormalizedDelta * walk_speed_;
		if (LowLevelUpdate::d_pressed)
			leftRight = -LowLevelUpdate::NormalizedDelta * walk_speed_;

		UpdateCameraMatrix();
		glm::vec3 cam_forward = cameraMatrix * unitZ;
		glm::vec3 cam_right =  cameraMatrix * unitX;
		cam_forward =  glm::normalize(cam_forward);
		cam_right = glm::normalize(cam_right);
		position -= leftRight * cam_right + forwardBackward * cam_forward;
	}

	void UpdateCameraMatrix()
	{
		glm::mat4 headingMat, attitudeMat, positionMat;
		EulerToMatrix(glm::vec3{ -heading_, 0, 0 }, headingMat);
		EulerToMatrix(glm::vec3{ 0,0, attitude_ }, attitudeMat);
		positionMat = glm::translate(position);
		cameraMatrix = positionMat * headingMat * attitudeMat;
		viewMatrix = glm::inverse(cameraMatrix);
	}

	glm::mat4 get_view_matrix()
	{
		UpdateCameraMatrix();
		return viewMatrix;
	}
};

extern Camera camera;
