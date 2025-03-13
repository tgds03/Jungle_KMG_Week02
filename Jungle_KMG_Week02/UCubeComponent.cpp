#include "stdafx.h"
#include "UCubeComponent.h"

UCubeComponent::UCubeComponent() {
	static CMesh<FVertexColor>* _mesh = new CMesh<FVertexColor>();
	if (_mesh->IsEmpty()) {
		_mesh->SetVertices({
		{1.f, 1.f, -1.f,	1.f, 0.f, 0.f, 1.f},   // Vertex 0.
		{ -1.f, 1.f, -1.f,	0.f, 1.f, 0.f, 1.f },  // Vertex 1.
		{-1.f, 1.f, 1.f,	0.f, 0.f, 1.f, 1.f },    // And so on.
		{1.f, 1.f, 1.f,		1.f, 1.f, 0.f, 1.f},
		{1.f, -1.f, -1.f,	1.f, 0.f, 1.f, 1.f},
		{-1.f, -1.f, -1.f,	0.f, 1.f, 1.f, 1.f},
		{-1.f, -1.f, 1.f,	0.f, 0.f, 0.f, 1.f},
		{1.f, -1.f, 1.f,	1.f, 1.f, 1.f, 1.f},
		})->SetIndices({
			0,1,2,               // Face 0 has three vertices.
			0,2,3,                // And so on.
			0,4,5,
			0,5,1,
			1,5,6,
			1,6,2,
			2,6,7,
			2,7,3,
			3,7,4,
			3,4,0,
			4,7,6,
			4,6,5,
			});
		CRenderer::AddMesh("Cube", _mesh);
	}
}

void UCubeComponent::Update() {
	SetRelativeRotation(FVector(M_PI / 4, 0, 0));
}

void UCubeComponent::Render() {
	CRenderer::SetMesh("Cube");
	CRenderer::SetTansformToConstantBuffer(Transformation());
	CRenderer::Render();

}

void UCubeComponent::Start() {}

void UCubeComponent::Remove() {}
