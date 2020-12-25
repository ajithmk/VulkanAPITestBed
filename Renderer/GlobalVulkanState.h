#pragma once

#include <map>
#include <string>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <GLFW\glfw3.h>
#include <stdexcept>
#include <optional>

#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" << "not success" << "\" in " << __FILE__ << " at line " << __LINE__ << std::endl; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}

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
	bool FramebufferResized;
	VkInstance VulkanInstance;
	VkDevice VulkanDevice;
	VkPhysicalDevice PhysicalDevice;
	VkFormat SwapChainImageFormat;
	VkExtent2D SwapChainExtent;
	VkSwapchainKHR SwapChain;
	std::vector<VkFramebuffer> SwapChainFramebuffers;

	VkQueue GraphicsQueue;
	VkQueue PresentQueue;

private:
	GLFWwindow* _window;
	VkSurfaceKHR _surface;

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

	map<string, VkDescriptorSetLayout> descriptorSetLayouts;
	map<string, VkCommandPool> commandPools;
	map<string, VkBuffer> buffers;
	map<string, VkDeviceMemory> deviceMemories;
	map<string, VkDescriptorPool> descriptorPools;
	map<string, VkCommandBuffer> commandBuffers;
	map<string, VkDescriptorSet>descriptorSets;
	
	using SwapChainCallbacks = void (*)();

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


const  std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};


const bool enableValidationLayers = true;

public:
	void insertResource(ResourceType type, string s, VkDescriptorSetLayout item)
	{
		descriptorSetLayouts[s] = item;
	}
	void insertResource(ResourceType type, string s, VkCommandPool item)
	{
		commandPools[s] = item;
	}
	void insertResource(ResourceType type, string s, VkBuffer item)
	{
		buffers[s] = item;
	}
	void insertResource(ResourceType type, string s, VkDeviceMemory item)
	{
		deviceMemories[s] = item;
	}
	void insertResource(ResourceType type, string s, VkDescriptorPool item)
	{
		descriptorPools[s] = item;
	}
	void insertResource(ResourceType type, string s, VkCommandBuffer item)
	{
		commandBuffers[s] = item;
	}
	void insertResource(ResourceType type, string s, VkDescriptorSet item)
	{
		descriptorSets[s] = item;
	}

	void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		FramebufferResized = true;
	}

	size_t numOfSwapChains()
	{
		return swapChainImages.size();
	}


	SwapChainCallbacks reCreateSwapChainRelatedResources;
	SwapChainCallbacks destroySwapCHainRelatedResources;

	RACK(VkInstance instance, GLFWwindow* window, VkSurfaceKHR surface, SwapChainCallbacks recreate, SwapChainCallbacks destroy);

	~RACK();
	void* getResource(ResourceType, string);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
	void createImageViews();
	void createFramebuffers(VkRenderPass);
	void cleanupSwapChain();
	void recreateSwapChain();

	bool isDeviceSuitable(VkPhysicalDevice device);
	void pickPhysicalDevice();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice);
	void createLogicalDevice();
	void createDescriptorSetLayout();
};

extern RACK* rack;
