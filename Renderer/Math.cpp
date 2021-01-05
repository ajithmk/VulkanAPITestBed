#include "Math.h"

void EulerToMatrix(glm::vec3 eulerAngles, glm::mat4 &destMat)
{
	float sh = sin(eulerAngles.x);
	float ch = cos(eulerAngles.x);

	float sa = sin(eulerAngles.y);
	float ca = cos(eulerAngles.y);

	float sb = sin(eulerAngles.z);
	float cb = cos(eulerAngles.z);

	destMat[0] = glm::vec4{ ch * ca, sa, -sh * ca, 0.0};
	destMat[1] = glm::vec4{ -ch * sa * cb + sh * sb, ca * cb, sh * sa * cb + ch * sb, 0.0 };
	destMat[2] = glm::vec4{ ch * sa * sb + sh * cb , -ca * sb, -sh * sa * sb + ch * cb, 0.0 };
	destMat[3] = glm::vec4{0.0, 0.0, 0.0, 1.0};
}

void AxisAngleToMatrix(glm::vec3 axis, float angle, glm::mat4 &destMat)
{
	axis = glm::normalize(axis);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float c = cos(angle);
	float s = sin(angle);
	float t = 1 - c;

	destMat[0] = glm::vec4{ t * x * x + c , t * x * y + z * s , t * x * z - y * s , 0.0 };
	destMat[1] = glm::vec4{ t * x * y - z * s , t * y * y + c , t * y * z + x * s, 0.0 };
	destMat[2] = glm::vec4{ t * x * z + y * s , t * y * z - x * s , t * z * z + c , 0.0};
	destMat[3] = glm::vec4{ 0.0, 0.0, 0.0, 1.0 };
}

void MatrixToEuler(glm::mat4 rotMatrix, glm::vec3 &eulerAngles)
{
	eulerAngles.x = atan2(-rotMatrix[0][2], rotMatrix[0][0]);
	eulerAngles.y = asin(rotMatrix[0][1]);
	eulerAngles.z = atan2(rotMatrix[2][1], rotMatrix[1][1]);
}
