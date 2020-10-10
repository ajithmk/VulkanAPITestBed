#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>

using namespace std;

struct Vertex {
    glm::vec4 pos;
    glm::vec4 tangent;
    glm::vec3 normal;
    glm::vec2 uv;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions();
};
