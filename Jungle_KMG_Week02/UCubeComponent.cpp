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
	aabb = BoundingBox();
	aabb.min = FVector(-1.f, -1.f, -1.f);
	aabb.max = FVector(1.f, 1.f, 1.f);
}

bool UCubeComponent::IsRayIntersect(Ray ray) {
	FMatrix transformation = Transformation().Inverse();
	Ray transformedRay = Ray(transformation.TransformCoord(ray.start), transformation.TransformCoord(ray.end));

	// reference: https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
	BoundingBox aabb = GetAABB();
	FVector rayDirection = ray.GetDirection();
	FVector dirfrac = FVector(1 / rayDirection.x, 1 / rayDirection.y, 1 / rayDirection.z);

	float t1 = (aabb.min.x - transformedRay.start.x) * dirfrac.x;
	float t2 = (aabb.max.x - transformedRay.start.x) * dirfrac.x;
	float t3 = (aabb.min.y - transformedRay.start.y) * dirfrac.y;
	float t4 = (aabb.max.y - transformedRay.start.y) * dirfrac.y;
	float t5 = (aabb.min.z - transformedRay.start.z) * dirfrac.z;
	float t6 = (aabb.max.z - transformedRay.start.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if ( tmax < 0 ) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if ( tmin > tmax ) {
		return false;
	}

	return true;
}

void UCubeComponent::Update() {}

void UCubeComponent::Render() {
	CRenderer::SetMesh("Cube");
	CRenderer::SetTansformToConstantBuffer(Transformation());
	CRenderer::Render();

}

void UCubeComponent::Start() {}

void UCubeComponent::Remove() {}
