#pragma once

void objreader(string obj, vector<Vertex>& V, vector<int32_t>& I);
void objreaderInLispFormatCompressed(string obj, vector<Vertex>& V, vector<int32_t>& I);
void objreaderCompressed(string obj, vector<Vertex>& V, vector<int32_t>& I);
void vertexTangentGen(vector<Vertex>& V, vector<int>& I);
void writeCompressedIndices(string filePath, const vector<Vertex> vertices, const vector<int32_t> I);
