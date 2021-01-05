#pragma once
#include <string>
#include "ObjReader.h"

class StaticGeometry {
public:
	vector<Vertex> Vertices;
	vector<glm::vec4> Tangents;
	vector<int32_t> Indices;

	glm::mat4 ModelMatrix = glm::mat4(1.0);
	StaticGeometry(string filePath, bool isLispFormat = false, bool isCompressed = true)
	{
		if (isLispFormat)
		{
			objreaderInLispFormatCompressed(filePath, Vertices, Indices);
		}
		else
		{
			if (isCompressed)
			objreaderCompressed(filePath, Vertices, Indices);
			objreader(filePath, Vertices, Indices);
		}
	}
};
