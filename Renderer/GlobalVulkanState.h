#pragma once

#include <map>
#include <string>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <GLFW\glfw3.h>
#include <stdexcept>
#include <optional>

using namespace std;

class RACK {
public:
	enum class ResourceType {
		RENDER_PASS = 0,
		DESCRIPTOR_SET_LAYOUT = 1,
		PIPELINE_LAYOUT = 2,
		PIPELINE = 3,
		COMMAND_POOL = 4,
		BUFFER = 5,
		DEVICE_MEMORY = 6,
		DESCRIPTOR_POOL = 7,
		COMMAND_BUFFER = 8,
		DESCRIPTOR_SET = 9
	};
	static bool framebufferResized;

private:
	static VkInstance _vulkanInstance;
	static VkDevice _vulkanDevice;
	static VkPhysicalDevice _physicalDevice;
	static GLFWwindow* _window;
	static VkSurfaceKHR _surface;

	static VkSwapchainKHR swapChain;
	static std::vector<VkImage> swapChainImages;
	static VkFormat swapChainImageFormat;
	static VkExtent2D swapChainExtent;
	static std::vector<VkImageView> swapChainImageViews;
	static std::vector<VkFramebuffer> swapChainFramebuffers;

	static map<string, VkDescriptorSetLayout> descriptorSetLayouts;
	static map<string, VkCommandPool> commandPools;
	static map<string, VkBuffer> buffers;
	static map<string, VkDeviceMemory> deviceMemories;
	static map<string, VkDescriptorPool> descriptorPools;
	static map<string, VkCommandBuffer> commandBuffers;
	static map<string, VkDescriptorSet>descriptorSets;

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	static VkQueue graphicsQueue;
	static VkQueue presentQueue;


	const static std::vector<const char*> deviceExtensions;
	const static std::vector<const char*> validationLayers;

	const static bool enableValidationLayers = true;



public:
	void static insertResource(ResourceType type, string s, VkDescriptorSetLayout item)
	{
		descriptorSetLayouts[s] = item;
	}
	void static insertResource(ResourceType type, string s, VkCommandPool item)
	{
		commandPools[s] = item;
	}
	void static insertResource(ResourceType type, string s, VkBuffer item)
	{
		buffers[s] = item;
	}
	void static insertResource(ResourceType type, string s, VkDeviceMemory item)
	{
		deviceMemories[s] = item;
	}
	void static insertResource(ResourceType type, string s, VkDescriptorPool item)
	{
		descriptorPools[s] = item;
	}
	void static insertResource(ResourceType type, string s, VkCommandBuffer item)
	{
		commandBuffers[s] = item;
	}
	void static insertResource(ResourceType type, string s, VkDescriptorSet item)
	{
		descriptorSets[s] = item;
	}

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		framebufferResized = true;
	}

	using ReCreateSwapChainRelatedResources = void (*)();

	static ReCreateSwapChainRelatedResources reCreateSwapChainRelatedResources;

	RACK(VkInstance instance, GLFWwindow* window, VkSurfaceKHR surface);

	~RACK();
	static void* getResource(ResourceType, string);

	static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	static void createSwapChain();
	static void createImageViews();
	static void createFramebuffers(VkRenderPass);
	static void cleanupSwapChain();
	static void recreateSwapChain();

	static bool isDeviceSuitable(VkPhysicalDevice device);
	static void pickPhysicalDevice();
	static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice);
	static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice);
	static void createLogicalDevice();


};
