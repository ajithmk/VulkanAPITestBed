// 3DEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <GLFW\glfw3.h>
#include "RenderSubSystem/Render.h"
#include "StaticGeometry.h"

GLFWwindow* window;
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

void initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	glfwSetKeyCallback(window, key_callback);
}

void initEngine()
{
	initWindow();
	InitRenderSubSystem(window);
}

void shutdownEngine()
{
	ShutdownRenderSubsystem();
}

void run() {
	RenderLoop();
}


int main() {
	initEngine();
	StaticGeometry geom("F:\\models\\obj-models\\sampleFort.obj", false, false);
	SetGeometryData(geom.Vertices.data(), geom.Vertices.size(), geom.Indices.data(), geom.Indices.size());
	run();
	shutdownEngine();
	return EXIT_SUCCESS;
}
