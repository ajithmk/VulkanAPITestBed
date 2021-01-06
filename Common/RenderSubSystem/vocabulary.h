#pragma once

#include <glm/glm.hpp>

using namespace std;

struct Vertex {
    glm::vec4 pos;
    glm::vec4 tangent;
    glm::vec3 normal;
    glm::vec2 uv;
};
