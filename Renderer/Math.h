#pragma once
#include <glm/matrix.hpp>

void EulerToMatrix(glm::vec3 eulerAngles, glm::mat4 &destMat);
void AxisAngleToMatrix(glm::vec3 axis, float angle, glm::mat4 &destMat);
void MatrixToEuler(glm::mat4 rotMatrix, glm::vec3 &eulerAngles);
