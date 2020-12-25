#pragma once

#include <GLFW/glfw3.h>
#include <chrono>
#include "GlobalVulkanState.h"


extern GLFWwindow* window;

void SetKeyboardEventsCallback();

class LowLevelUpdate {
public:
	static double MousePosX;
	static double MousePosY;
	static double PreviousMouseX;
	static double PreviousMouseY;
	static float Delta;
	static float NormalizedDelta;
	static std::chrono::milliseconds Current_time;
	static std::chrono::milliseconds Previous_time;
	static float DeltaMouseX;
	static float DeltaMouseY;
	static float NormalizedDeltaMouseX;
	static float NormalizedDeltaMouseY;
	static bool w_pressed;
	static bool s_pressed;
	static bool a_pressed;
	static bool d_pressed;
private:
	static bool one_time_guard;
public:
	static void BasicUpdate()
	{
		if (one_time_guard)
		{
			Current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			Previous_time = Current_time;
			one_time_guard = false;
		}
		Current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		Delta = (Current_time - Previous_time).count();
		NormalizedDelta = Delta / 16;
		Previous_time = Current_time;

		glfwGetCursorPos(window, &MousePosX, &MousePosY);
		MousePosX /= rack->SwapChainExtent.width;
		MousePosY /= rack->SwapChainExtent.height;
		DeltaMouseX = static_cast<float>( MousePosX - PreviousMouseX);
		DeltaMouseY = static_cast<float>( MousePosY - PreviousMouseY);
		PreviousMouseX = MousePosX;
		PreviousMouseY = MousePosY;
		NormalizedDeltaMouseX = DeltaMouseX * NormalizedDelta;
		NormalizedDeltaMouseY = DeltaMouseY * NormalizedDelta;

		w_pressed = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
		a_pressed = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
		s_pressed = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
		d_pressed = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	}

};
