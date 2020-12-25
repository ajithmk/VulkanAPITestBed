#include "Math.h"

void EulerToMatrix(glm::vec3 eulerAngles, glm::mat4 &destMat)
{
	float sh = sin(eulerAngles.x);
	float ch = cos(eulerAngles.x);

	float sa = sin(eulerAngles.y);
	float ca = cos(eulerAngles.y);

	float sb = sin(eulerAngles.z);
	float cb = cos(eulerAngles.z);

	/*destMat[0][0] = ch * ca;
	destMat[0][1] = -ch * sa * cb + sh * sb;
	destMat[0][2] = ch * sa * sb + sh * cb;
	destMat[0][3] = 0.0;
	destMat[1][0] = sa;
	destMat[1][1] = ca * cb;
	destMat[1][2] = -ca * sb;
	destMat[1][3] = 0.0;
	destMat[2][0] = -sh * ca;
	destMat[2][1] = sh * sa * cb + ch * sb;
	destMat[2][2] = -sh * sa * sb + ch * cb;
	destMat[2][3] = 0.0;
	destMat[3][0] = 0.0;
	destMat[3][1] = 0.0;
	destMat[3][2] = 0.0;
	destMat[3][3] = 1.0;*/

	destMat[0][0] = ch * ca;
	destMat[1][0] = -ch * sa * cb + sh * sb;
	destMat[2][0] = ch * sa * sb + sh * cb;
	destMat[3][0] = 0.0;
	destMat[0][1] = sa;
	destMat[1][1] = ca * cb;
	destMat[2][1] = -ca * sb;
	destMat[3][1] = 0.0;
	destMat[0][2] = -sh * ca;
	destMat[1][2] = sh * sa * cb + ch * sb;
	destMat[2][2] = -sh * sa * sb + ch * cb;
	destMat[3][2] = 0.0;
	destMat[0][3] = 0.0;
	destMat[1][3] = 0.0;
	destMat[2][3] = 0.0;
	destMat[3][3] = 1.0;

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

	/*destMat[0][0] = t * x * x + c;
	destMat[0][1] = t * x * y - z * s;
	destMat[0][2] = t * x * z + y * s;
	destMat[0][3] = 0.0;
	destMat[1][0] = t * x * y + z * s;
	destMat[1][1] = t * y * y + c;
	destMat[1][2] = t * y * z - x * s;
	destMat[1][3] = 0.0;
	destMat[2][0] = t * x * z - y * s;
	destMat[2][1] = t * y * z + x * s;
	destMat[2][2] = t *z * z + c;
	destMat[2][3] = 0.0;
	destMat[3][0] = 0.0;
	destMat[3][1] = 0.0;
	destMat[3][2] = 0.0;
	destMat[3][3] = 1.0;*/

	destMat[0][0] = t * x * x + c;
	destMat[1][0] = t * x * y - z * s;
	destMat[2][0] = t * x * z + y * s;
	destMat[3][0] = 0.0;
	destMat[0][1] = t * x * y + z * s;
	destMat[1][1] = t * y * y + c;
	destMat[2][1] = t * y * z - x * s;
	destMat[3][1] = 0.0;
	destMat[0][2] = t * x * z - y * s;
	destMat[1][2] = t * y * z + x * s;
	destMat[2][2] = t *z * z + c;
	destMat[3][2] = 0.0;
	destMat[0][3] = 0.0;
	destMat[1][3] = 0.0;
	destMat[2][3] = 0.0;
	destMat[3][3] = 1.0;

}

void MatrixToEuler(glm::mat4 rotMatrix, glm::vec3 &eulerAngles)
{
	eulerAngles.x = atan2(-rotMatrix[0][2], rotMatrix[0][0]);
	eulerAngles.y = asin(rotMatrix[0][1]);
	eulerAngles.z = atan2(rotMatrix[2][1], rotMatrix[1][1]);
}
