#pragma once
#include "CBuffer.h"
#include "CRenderer.h"
#include "CGraphics.h"

template <typename T>
class CMesh {
	TArray<T> vertices;
	TArray<uint32> indices;

	CVertexBuffer<T>* vertexBuffer;
	CIndexBuffer* indexBuffer;

public:
	CMesh(){};
	~CMesh();

	CMesh<T>* SetVertices(const std::initializer_list<T>& list);
	CMesh<T>* SetIndices(const std::initializer_list<uint32>& list);
	void Reset();


	ID3D11Buffer* GetVerticesBuffer();
	uint32 GetVerticesCount();
	uint32 GetVerticesStride();
	uint32 GetVerticesOffset();
	ID3D11Buffer* GetIndicesBuffer();
	uint32 GetIndicesCount();
	inline bool IsEmpty();
};

template<typename T>
inline CMesh<T>::~CMesh() {
	Reset();
}

template<typename T>
inline CMesh<T>* CMesh<T>::SetVertices(const std::initializer_list<T>& list) {
	vertices = TArray<T>(list);
	vertexBuffer = new CVertexBuffer<T>(CRenderer::GetGraphics()->GetDevice());
	vertexBuffer->Create(vertices);
	return this;
}

template<typename T>
inline CMesh<T>* CMesh<T>::SetIndices(const std::initializer_list<uint32>& list) {
	indices = TArray<uint32>(list);
	indexBuffer = new CIndexBuffer(CRenderer::GetGraphics()->GetDevice());
	indexBuffer->Create(indices);
	return this;
}

template<typename T>
inline void CMesh<T>::Reset() {
	vertices.clear();
	indices.clear();
	delete vertexBuffer;
	delete indexBuffer;
}

template<typename T>
inline ID3D11Buffer* CMesh<T>::GetVerticesBuffer() {
	return vertexBuffer->Get();
}

template<typename T>
inline uint32 CMesh<T>::GetVerticesCount() {
	return vertexBuffer->GetCount();
}

template<typename T>
inline uint32 CMesh<T>::GetVerticesStride() {
	return vertexBuffer->GetStride();
}

template<typename T>
inline uint32 CMesh<T>::GetVerticesOffset() {
	return vertexBuffer->GetOffset();
}

template<typename T>
inline ID3D11Buffer* CMesh<T>::GetIndicesBuffer() {
	return indexBuffer->Get();
}

template<typename T>
inline uint32 CMesh<T>::GetIndicesCount() {
	return indexBuffer->GetCount();
}

template<typename T>
inline bool CMesh<T>::IsEmpty() {
	return vertices.empty() || indices.empty();
}
