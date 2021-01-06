#ifdef RENDER_EXPORT
#define RENDER_API __declspec(dllexport)
#else
#define RENDER_API __declspec(dllimport)
#endif

#include <GLFW/glfw3.h>

RENDER_API void InitRenderSubSystem(GLFWwindow *const window);
RENDER_API void ShutdownRenderSubsystem();
RENDER_API void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
RENDER_API void framebufferResizeCallback(GLFWwindow* window, int width, int height);
RENDER_API void RenderLoop();
RENDER_API void SetGeometryData(void* verex_data, uint64_t vertices_number, void* index_data, uint64_t indices_number);