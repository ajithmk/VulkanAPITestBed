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
private:
	static bool one_time_guard;
public:
	static void BasicUpdate()
	{
		Current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		Delta = (Current_time - Previous_time).count();
		NormalizedDelta = Delta / 16;
		Previous_time = Current_time;

		glfwGetCursorPos(window, &MousePosX, &MousePosY);
		MousePosX /= rack->SwapChainExtent.width;
		MousePosY /= rack->SwapChainExtent.height;
		DeltaMouseX = MousePosX - PreviousMouseX;
		DeltaMouseY = MousePosY - PreviousMouseY;
		PreviousMouseX = MousePosX;
		PreviousMouseY = MousePosY;
		NormalizedDeltaMouseX = DeltaMouseX * NormalizedDelta;
		NormalizedDeltaMouseY = DeltaMouseY * NormalizedDelta;
	}

};
