#include <chrono>

#include "Input.h"
#include "Camera.h"

double LowLevelUpdate::MousePosX = 0.0;
double LowLevelUpdate::MousePosY = 0.0;
double LowLevelUpdate::PreviousMouseX = 0.0;
double LowLevelUpdate::PreviousMouseY = 0.0;
float LowLevelUpdate::Delta = 0.0;
float LowLevelUpdate::NormalizedDelta = 0.0;
std::chrono::milliseconds LowLevelUpdate::Previous_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
std::chrono::milliseconds LowLevelUpdate::Current_time =  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
float LowLevelUpdate::DeltaMouseX = 0.0;
float LowLevelUpdate::DeltaMouseY = 0.0;
float LowLevelUpdate::NormalizedDeltaMouseX = 0.0;
float LowLevelUpdate::NormalizedDeltaMouseY = 0.0;
bool LowLevelUpdate::one_time_guard = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		camera.TranslateCamera(LowLevelUpdate::NormalizedDelta, 0.0);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		camera.TranslateCamera(-LowLevelUpdate::NormalizedDelta, 0.0);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		camera.TranslateCamera(0.0, LowLevelUpdate::NormalizedDelta);
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		camera.TranslateCamera(0.0, -LowLevelUpdate::NormalizedDelta);
}

void SetKeyboardEventsCallback()
{
	glfwSetKeyCallback(window, key_callback);
}