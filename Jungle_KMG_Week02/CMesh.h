#pragma once
#include "CBuffer.h"
#include "CRenderer.h"
#include "CGraphics.h"

template <typename T>
class CMesh {
	TArray<T> _vertices;
	TArray<uint32> _indices;

	CVertexBuffer<T>* _vertexBuffer;
	CIndexBuffer* _indexBuffer;

protected:
	D3D11_PRIMITIVE_TOPOLOGY _primitiveMode;
	inline CMesh(D3D11_PRIMITIVE_TOPOLOGY primitiveMode) : _primitiveMode(primitiveMode) {};
public:
	inline CMesh(): _primitiveMode(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {};
	virtual ~CMesh();

	CMesh<T>* SetVertices(const std::initializer_list<T>& list);
	CMesh<T>* SetIndices(const std::initializer_list<uint32>& list);
	CMesh<T>* SetVertices(const TArray<T>& list);
	CMesh<T>* SetIndices(const TArray<uint32>& list);
	void Reset();


	ID3D11Buffer* GetVerticesBuffer();
	uint32 GetVerticesCount();
	uint32 GetVerticesStride();
	uint32 GetVerticesOffset();
	ID3D11Buffer* GetIndicesBuffer();
	uint32 GetIndicesCount();
	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveMode();
	inline bool IsEmpty();
};

template<typename T>
inline CMesh<T>::~CMesh() {
	Reset();
}

template<typename T>
inline CMesh<T>* CMesh<T>::SetVertices(const std::initializer_list<T>& list) {
	_vertices = TArray<T>(list);
	if ( _vertexBuffer )
		SafeDelete(_vertexBuffer);
	_vertexBuffer = new CVertexBuffer<T>(CRenderer::GetGraphics()->GetDevice());
	_vertexBuffer->Create(_vertices);
	return this;
}

template<typename T>
inline CMesh<T>* CMesh<T>::SetIndices(const std::initializer_list<uint32>& list) {
	_indices = TArray<uint32>(list);
	if ( _indexBuffer )
		SafeDelete(_indexBuffer);
	_indexBuffer = new CIndexBuffer(CRenderer::GetGraphics()->GetDevice());
	_indexBuffer->Create(_indices);
	return this;
}

template<typename T>
inline CMesh<T>* CMesh<T>::SetVertices(const TArray<T>& list) {
	_vertices.clear();
	_vertices = list;
	if ( _vertexBuffer )
		SafeDelete(_vertexBuffer);
	_vertexBuffer = new CVertexBuffer<T>(CRenderer::GetGraphics()->GetDevice());
	_vertexBuffer->Create(_vertices);
	return this;
}

template<typename T>
inline CMesh<T>* CMesh<T>::SetIndices(const TArray<uint32>& list) {
	_indices.clear();
	_indices = list;
	if ( _indexBuffer )
		SafeDelete(_indexBuffer);
	_indexBuffer = new CIndexBuffer(CRenderer::GetGraphics()->GetDevice());
	_indexBuffer->Create(_indices);
	return this;
}

template<typename T>
inline void CMesh<T>::Reset() {
	_vertices.clear();
	_indices.clear();
	delete _vertexBuffer;
	delete _indexBuffer;
}

template<typename T>
inline ID3D11Buffer* CMesh<T>::GetVerticesBuffer() {
	return _vertexBuffer->Get();
}

template<typename T>
inline uint32 CMesh<T>::GetVerticesCount() {
	return _vertexBuffer->GetCount();
}

template<typename T>
inline uint32 CMesh<T>::GetVerticesStride() {
	return _vertexBuffer->GetStride();
}

template<typename T>
inline uint32 CMesh<T>::GetVerticesOffset() {
	return _vertexBuffer->GetOffset();
}

template<typename T>
inline ID3D11Buffer* CMesh<T>::GetIndicesBuffer() {
	return _indexBuffer->Get();
}

template<typename T>
inline uint32 CMesh<T>::GetIndicesCount() {
	return _indexBuffer->GetCount();
}

template<typename T>
inline D3D11_PRIMITIVE_TOPOLOGY CMesh<T>::GetPrimitiveMode() {
	return _primitiveMode;
}

template<typename T>
inline bool CMesh<T>::IsEmpty() {
	return _vertices.empty() || _indices.empty();
}

class CBatchLineMesh: public CMesh<FVertexColor> {
	TArray<TPair<FVertexColor, FVertexColor>> _lines;
public:
	CBatchLineMesh(): CMesh(D3D11_PRIMITIVE_TOPOLOGY_LINELIST) {};
	~CBatchLineMesh() {};

	void AddLine(TPair<FVertexColor, FVertexColor> pair);
	void AddLine(FVertexColor p1, FVertexColor p2);
	void Clear();
	void Set();
};