#include "stdafx.h"
#include "CMesh.h"

void CBatchLineMesh::AddLine(TPair<FVertexColor, FVertexColor> pair) {
	_lines.push_back(pair);
}

void CBatchLineMesh::AddLine(FVertexColor p1, FVertexColor p2) {
	AddLine(TPair<FVertexColor, FVertexColor>(p1, p2));
}

void CBatchLineMesh::Clear() {
	_lines.clear();
	SetVertices({});
	SetIndices({});
}

void CBatchLineMesh::Set() {
	TArray<FVertexColor> vertices = {};
	vertices.reserve(_lines.size() * 2);
	TArray<uint32> indices = {};
	indices.reserve(_lines.size() * 2);
	uint32 i = 0;
	for (auto& it: _lines) {
		vertices.push_back(it.first);
		vertices.push_back(it.second);
		indices.push_back(i++);
		indices.push_back(i++);
	}
	SetVertices(vertices);
	SetIndices(indices);
}
