#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "vocabulary.h"


ofstream err("obj_issues.txt");
/*void objreader(string obj, vector<Vertex>& V, vector<int32_t>& I)
{
	char c;
	ifstream is;
	is.open(obj, ios_base::in);
	string temp;
	glm::vec4 v; glm::vec2 t;
	glm::vec3 no;
	struct index { int v_index, t_index, n_index; }ind;
	vector<index> indices1, indices2;
	vector<glm::vec4> vertices1, vertices;
	vector<glm::vec3> normals1, normals;
	vector<glm::vec2> uvs, uvs1;
	while (getline(is, temp))
	{
		istringstream s(temp);
		s >> temp;
		if (temp == "v") { s >> v.x >> v.y >> v.z; v.w = 1; vertices1.push_back(v); }
		if (temp == "vn") { s >> no.x >> no.y >> no.z; normals1.push_back(no); }
		if (temp == "vt") { s >> t.x >> t.y; uvs1.push_back(t); }
		if (temp == "f")
		{
			for (int i = 0; i < 3; i++)
			{
				s >> ind.v_index;
				s.ignore();
				c = s.get();
				if (isdigit(c)) { s.unget(); s >> ind.t_index; s.ignore(); }
				else ind.t_index = 1;
				s >> ind.n_index;
				indices1.push_back(ind);
			}
		}
	}
	int found = 0;
	int size1 = indices1.size();
	for (int i = 0; i < size1; i++)
	{
		found = 0;
		for (int j = i - 1; j >= 0; j--)
		{
			if ((indices1[i].n_index == indices1[j].n_index) && (indices1[i].v_index == indices1[j].v_index) && (indices1[i].t_index == indices1[j].t_index))
			{
				found = 1; break;
			}
		}
		if (found == 0) { indices2.push_back(indices1[i]); }
	}
	int size2 = indices2.size();
	for (int i = 0; i < size2; i++)
	{
		vertices.push_back(vertices1[indices2[i].v_index - 1]);
		normals.push_back(normals1[indices2[i].n_index - 1]);
		if (indices1[i].t_index)uvs.push_back(uvs1[indices2[i].t_index - 1]);
		else uvs.push_back(uvs1[indices2[i].t_index]);
	}
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < indices2.size(); j++)
		{
			if ((indices1[i].n_index != indices2[j].n_index) || ((indices1[i].v_index != indices2[j].v_index) || ((indices1[i].t_index != indices2[j].t_index))))
				continue;
			else
				I.push_back(j);
		}
	}
	Vertex ajith;
	for (int i = 0; i < size2; i++)
	{
		ajith.pos = vertices[i]; ajith.normal = normals[i]; ajith.uv = uvs[i];
		V.push_back(ajith);
	}
}
void vertexTangentGen(vector<Vertex>& V, vector<int>& I)
{

	unsigned int vertexCount = V.size();
	unsigned int indexCount = I.size();
	glm::vec3* tan1 = new glm::vec3[vertexCount * 2];
	glm::vec3* tan2 = tan1 + vertexCount;
	for (int i = 0; i < indexCount; i = i + 3)
	{
		int i1 = I[i];
		int i2 = I[i + 1];
		int i3 = I[i + 2];

		glm::vec4 vertex1 = V[i1].pos;
		glm::vec4 vertex2 = V[i2].pos;
		glm::vec4 vertex3 = V[i3].pos;
		glm::vec2 texcoord1 = V[i1].uv;
		glm::vec2 texcoord2 = V[i2].uv;
		glm::vec2 texcoord3 = V[i3].uv;

		float x1 = vertex2.x - vertex1.x;
		float x2 = vertex3.x - vertex1.x;
		float y1 = vertex2.y - vertex1.y;
		float y2 = vertex3.y - vertex1.y;
		float z1 = vertex2.z - vertex1.z;
		float z2 = vertex3.z - vertex1.z;

		float s1 = texcoord2.x - texcoord1.x;
		float s2 = texcoord3.x - texcoord1.x;
		float t1 = texcoord2.y - texcoord1.y;
		float t2 = texcoord3.y - texcoord1.y;

		float r = 1.0f / (s1 * t2 - s2 * t1);
		glm::vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
		glm::vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);

		tan1[i1].x = tan1[i1].x + sdir.x; tan1[i1].y = tan1[i1].y + sdir.y; tan1[i1].z = tan1[i1].z + sdir.z;
		tan1[i2].x = tan1[i2].x + sdir.x; tan1[i2].y = tan1[i2].y + sdir.y; tan1[i2].z = tan1[i2].z + sdir.z;
		tan1[i3].x = tan1[i3].x + sdir.x; tan1[i3].y = tan1[i3].y + sdir.y; tan1[i3].z = tan1[i3].z + sdir.z;
		tan2[i1].x = tan2[i1].x + tdir.x; tan2[i1].y = tan2[i1].y + tdir.y; tan2[i1].z = tan2[i1].z + tdir.z;
		tan2[i2].x = tan2[i2].x + tdir.x; tan2[i2].y = tan2[i2].y + tdir.y; tan2[i2].z = tan2[i2].z + tdir.z;
		tan2[i3].x = tan2[i3].x + tdir.x; tan2[i3].y = tan2[i3].y + tdir.y; tan2[i3].z = tan2[i3].z + tdir.z;
	}
	for (int i = 0; i < vertexCount; i++)
	{
		glm::vec3 n = V[i].normal;
		glm::vec3 t = tan1[i];
		glm::vec3 temp = glm::normalize(t - n * glm::dot(n, t));
		float s = glm::dot(glm::cross(n, t), tan2[i]);
		V[i].tangent.x = temp.x; V[i].tangent.y = temp.y; V[i].tangent.z = temp.z;
		V[i].tangent.w = (s > 0.0f) ? -1.0f : 1.0f;
	}
	delete[] tan1;
}*/