#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 texCord;

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inTangent;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUv;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition.xyz, 1.0);
gl_Position.z = (gl_Position.z + gl_Position.w) / 2.0;
	texCord = inUv;
    fragColor = vec3(inUv.x, inUv.y, 1.0);
}
